#include <float.h>

#if !defined(ae2f_Bmp_Src_h)
#define ae2f_Bmp_Src_h

#include "Idxer.h"
#include <ae2f/Macro/Call.h>

// Enum about Bit Count per Pixel
enum ae2f_Bmp_Idxer_eBC {
	ae2f_Bmp_Idxer_eBC_BIT = 1,
	ae2f_Bmp_Idxer_eBC_HALF = 4, // 0 ~ 15
	ae2f_Bmp_Idxer_eBC_BYTE = 8, // 0 ~ 255
	ae2f_Bmp_Idxer_eBC_RGB = 24, // not indexing, rgb
	ae2f_Bmp_Idxer_eBC_RGBA = 32, // not indexing, rgba
	ae2f_Bmp_Idxer_eBC_REMINDER_OWNER = 64
};

typedef uint8_t ae2f_Bmp_Idxer_eBC_t;

struct ae2f_Bmp_cSrc_Copy_Global {
	uint8_t 
		Alpha, // Global Fucking Alpha
		ReverseIdx; // Reverse Idx?
	uint32_t 
		WidthAsResized, 	// want to resize?
		HeightAsResized, 	// want to resize?
		AddrXForDest, 		// where to copy
		AddrYForDest, 		// where to copy
		DataToIgnore;

	double RotateXYClockWise;

	int32_t 
		AxisX, AxisY;
};

#define ae2f_Bmp_cSrc_Copy_Global_Alpha_ReverseIdxOfX ae2f_static_cast(uint8_t, 	0b01)
#define ae2f_Bmp_cSrc_Copy_Global_Alpha_ReverseIdxOfY ae2f_static_cast(uint8_t, 	0b10)

#define ae2f_Bmp_cSrc_Copy_ColourIdx(len) struct { ae2f_struct ae2f_Bmp_cSrc_Copy_Global global; uint32_t ColourIdx[len]; }

struct ae2f_Bmp_cSrc {
	// Indexing suporter
	// Abstraction
	ae2f_struct ae2f_Bmp_rIdxer rIdxer;

	// size of each element[pixel] as bit
	// bit cound [Element Size]
	ae2f_Bmp_Idxer_eBC_t ElSize;

	// Real element[pixel] vector [Global]
	uint8_t* Addr;
};

ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_Fill(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	uint32_t colour
);

ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_gDot(
	const ae2f_struct ae2f_Bmp_cSrc* src,
	uint32_t* retColour,
	double _min_x,
	double _min_y,
	double _max_x,
	double _max_y,

	uint8_t reverseIdx
);

/// @brief 
/// Copies the data of `src` to `dest`.
///
/// `src` will be considered that is has only 3 channels in use, aka RGB.
/// @param dest 
/// Destination where the `src` would be copied.
/// 
/// Allocating will not be automatically done.
/// @param src 
/// Source which has the actual data.
/// @param srcprm 
/// Additional operator attribute for `src`.
ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_Copy(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	const ae2f_struct ae2f_Bmp_cSrc* src,
	const ae2f_struct ae2f_Bmp_cSrc_Copy_Global* srcprm
);

/// @brief 
/// Copies the data of `src` to `dest`.
/// 
/// `src` will be considered that is has only 3 channels in use, aka RGB.
/// @param dest 
/// Destination where the `src` would be copied.
/// 
/// Allocating will not be automatically done.
/// @param src 
/// Source which has the actual data.
/// @param srcprm 
/// Additional operator attribute for `src`.
ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_Copy_Partial(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	const ae2f_struct ae2f_Bmp_cSrc* src,
	const ae2f_struct ae2f_Bmp_cSrc_Copy_Global* srcprm,
	uint32_t partial_min_x,
	uint32_t partial_min_y,
	uint32_t partial_max_x,
	uint32_t partial_max_y
);

/// @brief 
/// `byte` is not long enough to parse.
#define ae2f_Bmp_cSrc_Read_BYTEARR_TOO_SHORT ae2f_errGlobal_LMT

/// @brief 
/// # After this operation `dest` will still not own the memory, but `byte` will.
/// @param dest 
/// Destination where the `byte` 
/// @param byte 
/// The data of bmp structure with header.
/// @param byteLength 
/// size of the `byte`.
/// @return 
ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_Read(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	uint8_t* byte,
	size_t byteLength
);

#define ae2f_Bmp_Src_Cut(cSrc, mX, MX, mY, MY) ae2f_record_make(ae2f_struct ae2f_Bmp_cSrc, ae2f_Bmp_Idx_Cut((cSrc).rIdxer, mX, MX, mY, MX), (cSrc).ElSize, (cSrc).Addr + ae2f_Bmp_Idx_Drive((cSrc).rIdxer, mX, mY) * (cSrc).ElSize)

#endif // !defined(ae2f_Bmp_Src_h)
