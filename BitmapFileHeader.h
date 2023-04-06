#pragma once

#include <cstdint>
using namespace std;

#pragma pack(2)

namespace deastisconsulting
{

	struct BitmapFileHeader {
		char header[2]{ 'B', 'M' };
		uint32_t fileSize;
		int32_t reserved{ 0 };
		int32_t dataOffset;
	};

}