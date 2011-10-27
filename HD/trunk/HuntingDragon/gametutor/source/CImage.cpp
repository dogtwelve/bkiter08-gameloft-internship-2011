#include "CImage.h"
#include "CGLPipelineDriver.h"

namespace GameTutor
{
	CImage::CImage(int width, int height, EImagePixelFormat format ):m_iWidth(width), m_iHeight(height), m_eFormat(format), m_pData(0), m_iTextureID(0)
	{
		int dataSize = GetDataSize();
		m_pData = new __UINT8[dataSize];
	}	

	CImage::~CImage()
	{
		SAFE_DEL(m_pData);
	}

	void CImage::GetPixel(__UINT32 row, __UINT32 col, SColor<__UINT8> &c)
	{
		int offset = 0;
		if (row >= 0 && row < m_iHeight && col >= 0 && col <m_iWidth)
		{
			switch (m_eFormat)
			{
			case EIMAGE_FORMAT_R8G8B8:
				offset = (row*m_iWidth + col)*3; //3 bytes per pixels
				memcpy(&c, m_pData + offset, 3);
				c.Alpha = 255;
				break;
			case EIMAGE_FORMAT_R8G8B8A8:
				offset = (row*m_iWidth + col)*4; //3 bytes per pixels
				memcpy(&c, m_pData + offset, 4);
				break;
			}
		}
	}

	void CImage::SetPixel(__UINT32 row, __UINT32 col, SColor<__UINT8> c)
	{
		int offset = 0;
		if (row >= 0 && row < m_iHeight && col >= 0 && col <m_iWidth)
		{
			switch (m_eFormat)
			{
			case EIMAGE_FORMAT_R8G8B8:
				offset = (row*m_iWidth + col)*3; //3 bytes per pixels
				memcpy(m_pData + offset, &c, 3);
				break;
			case EIMAGE_FORMAT_R8G8B8A8:
				offset = (row*m_iWidth + col)*4; //3 bytes per pixels
				memcpy(m_pData + offset, &c, 4);
				break;
			}
		}
	}

	void CImage::ClearColor(SColor<__UINT8> c)
	{
		int dataSize = GetDataSize();
		switch (m_eFormat)
		{
		case EIMAGE_FORMAT_R8G8B8:
			for (int i = 0; i < dataSize; i+=3)
			{
				memcpy(m_pData + i, &c, 3);
			}
			break;
		case EIMAGE_FORMAT_R8G8B8A8:
			for (int i = 0; i < dataSize; i+=4)
			{
				memcpy(m_pData + i, &c, 4);
			}
			break;
		}
	}

	void CImage::BindGPU(CGLPipelineDriver *driver)
	{
		if (m_iTextureID > 0)
		{
			this->UnbindGPU(driver);
		}
		switch (m_eFormat)
		{
		case EIMAGE_FORMAT_R8G8B8:
			this->m_iTextureID = driver->AddTexure2D(0, EGLPD_PIXFMT_R8G8B8, this->m_iWidth, this->m_iHeight, 0, this->m_pData);
			break;
		case EIMAGE_FORMAT_R8G8B8A8:
			this->m_iTextureID = driver->AddTexure2D(0, EGLPD_PIXFMT_R8G8B8A8, this->m_iWidth, this->m_iHeight, 0, this->m_pData);
			break;
		default:
			break;
		}

	}

	void CImage::UnbindGPU(CGLPipelineDriver *driver)
	{

		if (m_iTextureID > 0)
		{
			driver->FreeTexture2D(this->m_iTextureID);
		}
	}


	CImage* CImage::LoadTGA(IReadableStream* stream)
	{
		TGA_Header header;
		stream->Read((__UINT8*)(&header), 0, sizeof(header));
		CImage *img = 0;

		// TGA black and white [TODO] need to check
		if(header.datatypecode == 3 && header.bitsperpixel == 8)
		{
			img = new CImage(header.width, header.height, EIMAGE_FORMAT_R8G8B8);
			stream->Skip(header.idlength + header.colourmaptype * header.colourmaplength);

			__UINT8 tmp;
			__UINT8* ptr = img->m_pData;
			for(int i = 0; i < header.width * header.height; i++) 
			{
				stream->ReadUInt8(tmp);
				memset(ptr, tmp, 3);
				ptr += 3;
			}		
		}
		else if (header.datatypecode != 2)
		{
			LogError("[CImage::LoadTGA] Unsupported TGA Format. Use non-compress only");
		}
		// TGA non-compress
		else if ((header.bitsperpixel != 24) && (header.bitsperpixel != 32))
		{
			LogError("[CImage::LoadTGA] Unsupported TGA Pixel Format. Use 24-, or 32-bpp only");
		}
		else
		{
			img = new CImage(header.width, header.height, (header.bitsperpixel == 24)?EIMAGE_FORMAT_R8G8B8:EIMAGE_FORMAT_R8G8B8A8);
			stream->Skip(header.idlength + header.colourmaptype * header.colourmaplength);
			stream->Read(img->m_pData, 0, header.width*header.height*header.bitsperpixel/8);

			if ((header.imagedescriptor & 0x08) != 0)
			{
				img->VerticalFlip();
			}
		}

		return img;
	}

	CImage* CImage::LoadPCX(const char* strImageName)
	{		
		FILE*			file;			// file stream
		PcxHeader			*header;		// header PCX
		unsigned char		*data;			// uncompressed paletted image data
		unsigned char		*ptr;			// pointer to pixels data
		unsigned char		c;				// temporary variable
		char				*buffer;		// buffer storing the entire file
		int					idx = 0;		// temporary variable
		int					numRepeat;		// temporary variable
		int					i, j;			// temporary variables
		unsigned char*		pixels;
		int width, height;

	/////////////////////////////////////////////////////
	// read the entire file in the buffer
	file = fopen(strImageName, "rb");

	if( file == NULL )
		return NULL;

	fseek(file, 0, SEEK_END);
	long flen = ftell(file);
	
	fseek(file, 0, SEEK_SET);

	buffer = new char[ flen + 1 ];
	fread( buffer, sizeof(char), flen, file );
	char *pBuff = buffer;

	fclose(file);

	/////////////////////////////////////////////////////

	header = (PcxHeader *)pBuff;

	if( (header->Identifier	!= 10)	||
		(header->Version		!= 5)	||
		(header->Encoding		!= 1)	||
		(header->BitsPerPixel	!= 8) )
	{
		return NULL;
	}


	width = header->XEnd - header->XStart + 1;
	height = header->YEnd - header->YStart + 1;	

	// allocate memory for image data
	data = new unsigned char[ width * height ];

	pBuff = (char *)&buffer[ 128 ];

	// uncode compressed image (RLE)
	while( idx < (width * height) )
	{
		if( (c = *(pBuff++)) > 0xbf )
		{
			numRepeat = 0x3f & c;
			c = *(pBuff++);

			for( i = 0; i < numRepeat; i++ )
				data[ idx++ ] = c;
		}
		else
			data[ idx++ ] = c;
	}


	// the palette is located at the 769th last byte of the file
	pBuff = &buffer[ flen - 769 ];

	// verify the palette; first char must be equal to 12
	if( *(pBuff++) != 12 )
	{
		delete [] buffer;
		delete [] data;
		return NULL;
	}

	// read the palette
	header->palette = (unsigned char *)pBuff;


	// allocate memory for 32 bits pixel data
	CImage* img = new CImage(width, height, EIMAGE_FORMAT_R8G8B8A8);

	ptr = img->m_pData;

	// convert from paletted to 32 bits rgba pixels
	for( j = height - 1; j > 0; j-- )
	{
		/*if( flipvert )
			ptr = &pixels[ j * header->width * 4 ];*/

		for( i = 0; i < width; i++, ptr += 4 )
		{
			int color = 3 * data[ j * width + i ];

			ptr[0] = (unsigned char)header->palette[ color + 0 ];
			ptr[1] = (unsigned char)header->palette[ color + 1 ];
			ptr[2] = (unsigned char)header->palette[ color + 2 ];
			ptr[3] = (unsigned char)255;
		}
	}

	// free memory
	delete [] data;
	delete [] buffer;
		
	return img;
	}

	void CImage::VerticalFlip()
	{
		__UINT32 runlen = GetPixelSize()*m_iWidth;
		__UINT8* buff = new __UINT8[runlen];
		__UINT8* top = m_pData;
		__UINT8* bottom = m_pData + ((m_iHeight - 1)*runlen);
		for (int i = 0; i < m_iHeight>>1; i++)
		{
			memcpy(buff, top, runlen);
			memcpy(top, bottom, runlen);
			memcpy(bottom, buff, runlen);
			top += runlen;
			bottom -= runlen;
		}
	}
}