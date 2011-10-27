class CFileWin32Driver: public CSingleton<CFileWin32Driver>
{
	friend class CSingleton<CFileWin32Driver>;
protected:
	CFileWin32Driver() {}
public:
	void Read(FILE*F, __UINT8* buffer, int offset, int length)
	{
		fread(buffer + offset, 1, length, F);
	}
	void Write(FILE*F, __UINT8* buffer, int offset, int length)
	{
		fwrite(buffer + offset, 1, length, F);
	}
	void Seek(FILE*F, int offset)
	{
		fseek(F, offset, SEEK_CUR);
	}
	void Goto(FILE*F, int offsetFromTop)
	{
		if (offsetFromTop==-1)
		{
			fseek(F, 0, SEEK_END);
		}
		else
		{
			fseek(F, offsetFromTop, SEEK_SET);
		}
	}
	void Rewind(FILE*F)
	{
		rewind(F);
	}
	void Open(FILE*& f, const char* filename, const char* mode)
	{
		fopen_s(&f, filename, mode);
	}
	void Close(FILE*& f)
	{
		fclose(f);
	}
	__UINT32 GetLength(FILE*& f)
	{
		fpos_t curpos;
		fgetpos(f, &curpos);
		fseek (f, 0, SEEK_END);
		__UINT32 size = ftell (f);
		fseek(f, __UINT32(curpos), SEEK_SET);
		return size;
	}
	bool TestError()
	{
		if (errno)
		{
			char buf[1024];
			strerror_s(buf, errno);
			LogError("[CFileWin32Driver] %s", buf);
			return true;
		}
		return false;
	}
};

enum EFileWin32Mode
{
	EFILEWIN32_READ,
	EFILEWIN32_WRITE
};

class CFileWin32Base: public IStreamBuffer
{
public:
	CFileWin32Base(const char* name, EFileWin32Mode mode): IStreamBuffer(name) , m_pFile(0), m_iLength(0), e_Mode(mode)
	{
		m_pDriver = CFileWin32Driver::GetInstance();
		Open();
	}

	virtual ~CFileWin32Base()
	{
		Close();
	}

	void Open() 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			return;
		}
		m_pDriver->Open(m_pFile, this->GetName(), (e_Mode == EFILEWIN32_READ)?"rb":"wb");
		m_pDriver->TestError();

		IStreamBuffer::Open();
		if (!m_pFile)
		{
			m_eStreamStatus = ESTREAM_ERROR;
			LogError("Fail to open file %s", (this->GetName()==0)?"":this->GetName());
		}
		else
		{
			m_iLength = m_pDriver->GetLength(m_pFile);
		}
	}

	void Close() 
	{
		if ((m_eStreamStatus != ESTREAM_CLOSE) && m_pFile)
		{
			m_pDriver->Close(m_pFile);	
			if (m_pDriver->TestError())
			{
				LogError("Fail to close file %s", (this->GetName()==0)?"":this->GetName());
			}
			m_pFile = 0;
		}
		IStreamBuffer::Close();	
	}

	__UINT32 GetLength() 
	{
		return m_iLength;
	}
protected:
	FILE* m_pFile;
	CFileWin32Driver* m_pDriver;
	__UINT32 m_iLength;
	EFileWin32Mode e_Mode;
};

template <>
class CReaderStream<CFileWin32Driver>: public IReadableStream, public CFileWin32Base
{
public:
	CReaderStream(const char* name): CFileWin32Base(name, EFILEWIN32_READ)
	{}

	virtual ~CReaderStream()
	{}

	void Read(__UINT8* buffer, int offset, int length) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			m_pDriver->Read(m_pFile, buffer, offset, length);
		}
	}

	void ReadInt8(__INT8 &val) 
	{
		val = 0;
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buf[1];
			m_pDriver->Read(m_pFile, buf, 0, 1);
			val = __INT8(buf[0]);
		}
	}

	void ReadUInt8(__UINT8 &val) 
	{
		val = 0;
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buf[1];
			m_pDriver->Read(m_pFile, buf, 0, 1);
			val = __UINT8(buf[0]);
		}
	}

	void ReadInt16(__INT16 &val) 
	{
		val = 0;
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buf[2];
			m_pDriver->Read(m_pFile, buf, 0, 2);
			val = __UINT16(buf[1]);
			val <<= 8;
			val |= __UINT16(buf[0]);
		}
	}

	void ReadUInt16(__UINT16 &val) 
	{
		val = 0;
		__INT16 tmp = 0;
		ReadInt16(tmp);
		val = __UINT16(tmp);
	}

	void ReadInt32(__INT32 &val) 
	{
		val = 0;
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buf[4];
			m_pDriver->Read(m_pFile, buf, 0, 4);
			val = __UINT16(buf[3]);
			val <<= 8;
			val |= __UINT16(buf[2]);
			val <<= 8;
			val |= __UINT16(buf[1]);
			val <<= 8;
			val |= __UINT16(buf[0]);
		}
	}

	void ReadUInt32(__UINT32 &val) 
	{
		val = 0;
		__INT32 tmp = 0;
		ReadInt32(tmp);
		val = __UINT32(tmp);
	}

	void ReadInt64(__INT64 &val) 
	{
		val = 0;
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buf[8];
			m_pDriver->Read(m_pFile, buf, 0, 8);
			val = __UINT16(buf[7]);
			val <<= 8;
			val |= __UINT16(buf[6]);
			val <<= 8;
			val |= __UINT16(buf[5]);
			val <<= 8;
			val |= __UINT16(buf[4]);
			val <<= 8;
			val |= __UINT16(buf[3]);
			val <<= 8;
			val |= __UINT16(buf[2]);
			val <<= 8;
			val |= __UINT16(buf[1]);
			val <<= 8;
			val |= __UINT16(buf[0]);
		}
	}
	
	void ReadUInt64(__UINT64 &val) 
	{
		val = 0;
		__INT64 tmp = 0;
		ReadInt64(tmp);
		val = __UINT64(tmp);
	}
	
	void Skip(__UINT32 n) 
	{
		m_pDriver->Seek(m_pFile, n);
	}
	
	void Goto(__UINT32 n) 
	{
		m_pDriver->Goto(m_pFile, n);
	}

};


template <>
class CWriteStream<CFileWin32Driver>: public IWriteableStream, public CFileWin32Base
{
public:
	CWriteStream(const char* name): CFileWin32Base(name, EFILEWIN32_WRITE) 
	{}

	virtual ~CWriteStream()
	{}

	void Write(__UINT8* buffer, int offset, int length) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			m_pDriver->Write(m_pFile, buffer , 0, length);
		}
	}
	void WriteInt8(__INT8 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val)};
			m_pDriver->Write(m_pFile, buffer , 0, 1);
		}
	}
	void WriteUInt8(__UINT8 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val)};
			m_pDriver->Write(m_pFile, buffer , 0, 1);
		}
	}
	void WriteInt16(__INT16 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val&0xFF), __UINT8(val>>8)};
			m_pDriver->Write(m_pFile, buffer , 0, 2);
		}
	}
	void WriteUInt16(__UINT16 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val&0xFF), __UINT8((val>>8)&0xFF)};
			m_pDriver->Write(m_pFile, buffer , 0, 2);
		}
	}
	void WriteInt32(__INT32 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val&0xFF), __UINT8((val>>8)&0xFF), 
				__UINT8((val>>16)&0xFF), __UINT8((val>>24)&0xFF)};
			m_pDriver->Write(m_pFile, buffer , 0, 4);
		}
	}
	void WriteUInt32(__UINT32 val) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 buffer[] = {__UINT8(val&0xFF), __UINT8((val>>8)&0xFF), 
				__UINT8((val>>16)&0xFF), __UINT8((val>>24)&0xFF)};
			m_pDriver->Write(m_pFile, buffer , 0, 4);
		}
	}
	void WriteInt64(__INT64 val) 
	{
		TODO("WriteInt64 is not implemented");
	}
	void WriteUInt64(__UINT64 val) 
	{
		TODO("WriteUInt64 is not implemented");
	}
	void WriteSeq(__UINT8 val, int length) 
	{
		if (m_eStreamStatus == ESTREAM_OPEN)
		{
			__UINT8 *buffer = new __UINT8[length];
			memset(buffer, 0, length);
			m_pDriver->Write(m_pFile, buffer , 0, length);
			SAFE_DEL(buffer);
		}
	}
};