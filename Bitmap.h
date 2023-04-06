#pragma once

#include <string>
#include <cstdint>
#include <memory>

using namespace std;

namespace deastisconsulting
{
	class Bitmap
	{
	public:
		Bitmap(int width, int height);
		virtual ~Bitmap();

		bool write(string filename);
		void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);

	private:
		int _width{ 0 };
		int _height{ 0 };
		unique_ptr<uint8_t[]> _pPixels{ nullptr };
	};
}
