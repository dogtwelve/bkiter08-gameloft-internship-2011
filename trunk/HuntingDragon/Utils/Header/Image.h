#pragma once
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdio.h>
#include "esUtil.h"
#include "pcx.h"
#include <fstream>

using namespace std;

enum { 
	TGA_ERROR_FILE_OPEN,
	TGA_ERROR_READING_FILE,
	TGA_ERROR_INDEXED_COLOR,
	TGA_ERROR_MEMORY,
	TGA_ERROR_COMPRESSED_FILE,
	TGA_OK 
};

typedef struct _TgaInfo
{
	GLenum mode;
	int status;
	unsigned char type, pixelDepth;
	short int width, height;
	unsigned char *imageData;
} TgaInfo;

typedef struct
{
	unsigned char	Identifier;        /* PCX Id Number (Always 0x0A) */
	unsigned char	Version;           /* Version Number */
	unsigned char	Encoding;          /* Encoding Format */
	unsigned char	BitsPerPixel;      /* Bits per Pixel */
	unsigned short	XStart;            /* Left of image */
	unsigned short	YStart;            /* Top of Image */
	unsigned short	XEnd;              /* Right of Image */
	unsigned short	YEnd;              /* Bottom of image */
	unsigned short	HorzRes;           /* Horizontal Resolution */
	unsigned short	VertRes;           /* Vertical Resolution */
	unsigned char	Palette[48];       /* 16-Color EGA Palette */
	unsigned char	Reserved1;         /* Reserved (Always 0) */
	unsigned char	NumBitPlanes;      /* Number of Bit Planes */
	unsigned short	unsigned charsPerLine;      /* unsigned chars per Scan-line */
	unsigned short	PaletteType;       /* Palette Type */
	unsigned short	HorzScreenSize;    /* Horizontal Screen Size */
	unsigned short	VertScreenSize;    /* Vertical Screen Size */
	unsigned char	Reserved2[54];     /* Reserved (Always 0) */
} PcxHeader;

class Image
{
public:
	Image(void);
	virtual ~Image(void);

	static unsigned char* LoadTgaImage(const char* strImageName, int *width, int *height, int *mode);
	static unsigned char* LoadPcxImage(const char* strImageName, int *width, int *height, int* mode);
private:
	static void LoadTgaImageData(FILE *file, TgaInfo *info);
	static void LoadTgaHeader(FILE* file, TgaInfo* tgainfo);
};

#endif