#ifndef ae2f_Bmp_BitCount_h
#define ae2f_Bmp_BitCount_h

#include <stdint.h>

/// @brief
/// Enum about Bit Count per Pixel
enum ae2f_eBmpBitCount {
	/// @brief 0 | 1
	ae2f_eBmpBitCount_BIT = 1,

	/// @brief 0 ~ 15
	ae2f_eBmpBitCount_HALF = 4,

	/// @brief 0 ~ 255 
	ae2f_eBmpBitCount_BYTE = 8,

	/// @brief not indexing, rgb
	ae2f_eBmpBitCount_RGB = 24, 

	/// @brief not indexing, rgba
	ae2f_eBmpBitCount_RGBA = 32,

	/// @brief Something is wrong
	ae2f_eBmpBitCount_REMINDER_OWNER = 64
};

/// @brief 
typedef uint8_t ae2f_eBmpBitCount_t;

#endif