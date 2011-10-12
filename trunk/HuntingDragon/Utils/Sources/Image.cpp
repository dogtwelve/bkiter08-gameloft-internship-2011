#include "Image.h"

Image::Image(void)
{
}

Image::~Image(void)
{
}

unsigned char* Image::LoadTgaImage(const char *strImageName, int* width, int* height, int* imgMode)
{
	FILE *file;
	TgaInfo *info;
	int mode,total;

	// allocate memory for the info struct and check!
	info = new TgaInfo;
	if (info == NULL)
		return(NULL);

	// open the file for reading (binary mode)
	file = fopen(strImageName, "rb");
	if (file == NULL) {
		info->status = TGA_ERROR_FILE_OPEN;
		return NULL;
	}

	// load the header
	LoadTgaHeader(file,info);

	// check for errors when loading the header
	if (ferror(file)) {
		info->status = TGA_ERROR_READING_FILE;
		fclose(file);
		return NULL;
	}

	// check if the image is color indexed
	if (info->type == 1) {
		info->status = TGA_ERROR_INDEXED_COLOR;
		fclose(file);
		return NULL;
	}
	// check for other types (compressed images)
	if ((info->type != 2) && (info->type !=3)) {
		info->status = TGA_ERROR_COMPRESSED_FILE;
		fclose(file);
		return NULL;
	}

	// mode equals the number of image components
	mode = info->pixelDepth / 8;
	info->mode = (mode == 3)?(GL_RGB):(GL_RGBA);	
	// total is the number of bytes to read
	total = info->height * info->width * mode;
	// allocate memory for image pixels
	info->imageData = new unsigned char[total];

	// check to make sure we have the memory required
	if (info->imageData == NULL) {
		info->status = TGA_ERROR_MEMORY;
		fclose(file);
		return NULL;
	}

	// finally load the image pixels
	LoadTgaImageData(file,info);

	// check for errors when reading the pixels
	if (ferror(file)) {
		info->status = TGA_ERROR_READING_FILE;
		fclose(file);
		return NULL;
	}
	fclose(file);
	info->status = TGA_OK;

	// OUT
	*imgMode = info->mode;
	*width = info->width;
	*height = info->height;
	return info->imageData;
}

void Image::LoadTgaHeader(FILE* file, TgaInfo* info)
{
	unsigned char cGarbage;
	short int iGarbage;

	fread(&cGarbage, sizeof(unsigned char), 1, file);
	fread(&cGarbage, sizeof(unsigned char), 1, file);

	// type must be 2 or 3
	fread(&info->type, sizeof(unsigned char), 1, file);

	fread(&iGarbage, sizeof(short int), 1, file);
	fread(&iGarbage, sizeof(short int), 1, file);
	fread(&cGarbage, sizeof(unsigned char), 1, file);
	fread(&iGarbage, sizeof(short int), 1, file);
	fread(&iGarbage, sizeof(short int), 1, file);

	fread(&info->width, sizeof(short int), 1, file);
	fread(&info->height, sizeof(short int), 1, file);
	fread(&info->pixelDepth, sizeof(unsigned char), 1, file);

	fread(&cGarbage, sizeof(unsigned char), 1, file);
}

void Image::LoadTgaImageData(FILE *file, TgaInfo *info) {

	int mode,total,i;
	unsigned char aux;

// mode equal the number of components for each pixel
	mode = info->pixelDepth / 8;
// total is the number of bytes we'll have to read
	total = info->height * info->width * mode;
	
	fread(info->imageData,sizeof(unsigned char),total,file);

// mode=3 or 4 implies that the image is RGB(A). However TGA
// stores it as BGR(A) so we'll have to swap R and B.
	if (mode >= 3)
		for (i=0; i < total; i+= mode) {
			aux = info->imageData[i];
			info->imageData[i] = info->imageData[i+2];
			info->imageData[i+2] = aux;
		}
}	

unsigned char* Image::LoadPcxImage(const char* strImageName, int *width, int *height, int* mode)
{
	ifstream			file;			// file stream
	PCXHEADER			*header;		// header PCX
	unsigned char		*data;			// uncompressed paletted image data
	unsigned char		*ptr;			// pointer to pixels data
	unsigned char		c;				// temporary variable
	char				*buffer;		// buffer storing the entire file
	int					idx = 0;		// temporary variable
	int					numRepeat;		// temporary variable
	int					i, j;			// temporary variables
	unsigned char*		pixels;


	/////////////////////////////////////////////////////
	// read the entire file in the buffer

	file.open( strImageName, std::ios::in | std::ios::binary );

	if( file.fail() )
		return NULL;

	file.seekg( 0, std::ios::end );
	long flen = file.tellg();
	file.seekg( 0, std::ios::beg );

	buffer = new char[ flen + 1 ];
	file.read( buffer, flen );
	char *pBuff = buffer;

	file.close();

	/////////////////////////////////////////////////////

	header = (PCXHEADER *)pBuff;

	if( (header->manufacturer	!= 10)	||
		(header->version		!= 5)	||
		(header->encoding		!= 1)	||
		(header->bitsPerPixel	!= 8) )
	{
		return NULL;
	}


	header->width	= header->width	 - header->x + 1;
	header->height	= header->height - header->y + 1;


	if( width )
		*width = header->width;

	if( height )
		*height = header->height;

	// allocate memory for image data
	data = new unsigned char[ header->width * header->height ];

	pBuff = (char *)&buffer[ 128 ];

	// uncode compressed image (RLE)
	while( idx < (header->width * header->height) )
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
	pixels = new unsigned char[ header->width * header->height * 4 ];

	ptr = &pixels[0];

	// convert from paletted to 32 bits rgba pixels
	for( j = header->height - 1; j > 0; j-- )
	{
		/*if( flipvert )
			ptr = &pixels[ j * header->width * 4 ];*/

		for( i = 0; i < header->width; i++, ptr += 4 )
		{
			int color = 3 * data[ j * header->width + i ];

			ptr[0] = (unsigned char)header->palette[ color + 0 ];
			ptr[1] = (unsigned char)header->palette[ color + 1 ];
			ptr[2] = (unsigned char)header->palette[ color + 2 ];
			ptr[3] = (unsigned char)255;
		}
	}

	// free memory
	delete [] data;
	delete [] buffer;

	// OUT
	*mode = GL_RGBA;
	return pixels;
}