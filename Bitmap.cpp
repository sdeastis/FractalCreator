#include "Bitmap.h"
#include "BitmapInfoHeader.h"
#include "BitmapFileHeader.h"

#include <fstream>

using namespace deastisconsulting;
using namespace std;

namespace deastisconsulting
{
	Bitmap::Bitmap(int width, int height): 
		_width(width), 
		_height(height),
		_pPixels(new uint8_t[width * height * 3]{}) //allocate and initialize to zero
	{
	}

	Bitmap::~Bitmap()
	{
	}
	
	bool Bitmap::write(string filename)
	{
		BitmapFileHeader bmFileH;
		BitmapInfoHeader bmInfoH;
		
		bmFileH.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + _width * _height * 3;
		bmFileH.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
		
		bmInfoH.width = _width;
		bmInfoH.height = _height;

		ofstream outBitMap;
		outBitMap.open(filename, ios::out | ios::binary);
		if (!outBitMap)
		{
			return false;
		}

		outBitMap.write((char*)(&bmFileH), sizeof(bmFileH));
		outBitMap.write((char*)(&bmInfoH), sizeof(bmInfoH));
		outBitMap.write((char*)_pPixels.get(), _width*_height*3);

		outBitMap.close();

		if (!outBitMap)
		{
			return false;
		}
		

		return true;
	}
	
	void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
	{
		uint8_t* pPixel = _pPixels.get();

		pPixel += (y * 3) * _width + (x * 3);

		pPixel[0] = blue;
		pPixel[1] = green;
		pPixel[2] = red;
	}
}

