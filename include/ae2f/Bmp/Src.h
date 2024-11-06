#include <float.h>

#if !defined(ae2f_Bmp_Src_h)
#define ae2f_Bmp_Src_h

#include "Idxer.h"
#include <ae2f/Macro/Call.h>

/// @brief
/// Enum about Bit Count per Pixel
enum ae2f_Bmp_Idxer_eBC {
	/// @brief 0 | 1
	ae2f_Bmp_Idxer_eBC_BIT = 1,

	/// @brief 0 ~ 15
	ae2f_Bmp_Idxer_eBC_HALF = 4,

	/// @brief 0 ~ 255 
	ae2f_Bmp_Idxer_eBC_BYTE = 8,

	/// @brief not indexing, rgb
	ae2f_Bmp_Idxer_eBC_RGB = 24, 

	/// @brief not indexing, rgba
	ae2f_Bmp_Idxer_eBC_RGBA = 32,

	/// @brief Something is wrong
	ae2f_Bmp_Idxer_eBC_REMINDER_OWNER = 64
};

/// @brief 
typedef uint8_t ae2f_Bmp_Idxer_eBC_t;

/// @brief 
/// A global parameter for @ref ae2f_Bmp_cSrc_Copy.
struct ae2f_Bmp_cSrc_Copy_Global {
	uint8_t 
		/// @brief
		/// Global Alpha for RGB architect.
		Alpha,
		/// @brief
		/// For reversed copy.
		ReverseIdx;
	uint32_t 
		/// @brief want to resize?
		WidthAsResized, 
		/// @brief want to resize?
		HeightAsResized, 	
		/// @brief where to copy [X]
		AddrXForDest, 		
		/// @brief where to copy [Y]
		AddrYForDest, 		
		DataToIgnore;

	
	/// @brief Rotation in a unit of radian
	double RotateXYCounterClockWise;

	int32_t 
		/// @brief
		/// The position of rotation Axis [X]
		AxisX, 
		/// @brief
		/// The position of rotation Axis [Y]
		AxisY;
};

/// @brief
/// @ref ae2f_Bmp_cSrc_Copy_Global::ReverseIdx
#define ae2f_Bmp_cSrc_Copy_Global_Alpha_ReverseIdxOfX ae2f_static_cast(uint8_t, 	0b01)

/// @brief
/// @ref ae2f_Bmp_cSrc_Copy_Global::ReverseIdx
#define ae2f_Bmp_cSrc_Copy_Global_Alpha_ReverseIdxOfY ae2f_static_cast(uint8_t, 	0b10)

/// @brief
/// Contains additional the colour values for indexed bmp.
/// @see ae2f_Bmp_cSrc_Copy_Global
#define ae2f_Bmp_cSrc_Copy_ColourIdx(len) struct { ae2f_struct ae2f_Bmp_cSrc_Copy_Global global; uint32_t ColourIdx[len]; }

#pragma pack(push, 1)

/// @brief 
/// 
struct ae2f_Bmp_cSrc {
	/// @brief
	/// Indexing suporter
	/// Abstraction
	ae2f_struct ae2f_Bmp_rIdxer rIdxer;

	/// @brief
	/// size of each element[pixel] as bit
	/// bit cound [Element Size]
	ae2f_Bmp_Idxer_eBC_t ElSize;

	/// @brief
	/// Real element[pixel] vector [Global]
	uint8_t* Addr;
};
#pragma pack(pop)

ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_Fill(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	uint32_t colour
);

ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_Fill_Partial(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	uint32_t colour,

	uint32_t partial_min_x,
	uint32_t partial_min_y,
	uint32_t partial_max_x,
	uint32_t partial_max_y
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
/// Copies the data of [src] to [dest]. \n
/// [src] will be considered that is has only 3 channels in use, aka RGB.
/// @param dest 
/// Destination where the [src] would be copied. \n
/// Allocating will not be automatically done.
/// @param src 
/// Source which has the actual data.
/// @param srcprm 
/// Additional operator attribute for [src].
ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_Copy(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	const ae2f_struct ae2f_Bmp_cSrc* src,
	const ae2f_struct ae2f_Bmp_cSrc_Copy_Global* srcprm
);

/// @brief 
/// Copies the data of [src] to [dest]. \n
/// [src] will be considered that is has only 3 channels in use, aka RGB.
/// @param dest 
/// Destination where the [src] would be copied. \n
/// Allocating will not be automatically done.
/// @param src 
/// Source which has the actual data.
/// @param srcprm 
/// Additional operator attribute for [src].
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
#define ae2f_Bmp_cSrc_Read_BYTEARR_TOO_SHORT ae2f_errGlob_WRONG_OPERATION

/// @brief 
/// # After this operation [dest] will still not own the memory, but [byte] will.
/// @param dest 
/// Destination where the [byte] 
/// @param byte 
/// The data of bmp structure with header.
/// @param byteLength 
/// size of the [byte].
/// @return 
ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_Read(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	uint8_t* byte,
	size_t byteLength
);

#define ae2f_Bmp_Src_Cut(cSrc, mX, MX, mY, MY) ae2f_record_make(ae2f_struct ae2f_Bmp_cSrc, ae2f_Bmp_Idx_Cut((cSrc).rIdxer, mX, MX, mY, MX), (cSrc).ElSize, (cSrc).Addr + ae2f_Bmp_Idx_Drive((cSrc).rIdxer, mX, mY) * (cSrc).ElSize)

#endif
