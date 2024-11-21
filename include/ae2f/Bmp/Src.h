#if !defined(ae2f_Bmp_Src_h)
#define ae2f_Bmp_Src_h

#include "Idxer.h"
#include <ae2f/Call.h>
#include <ae2f/Float.h>
#include <ae2f/Pack/Beg.h>

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
	ae2f_float_t RotateXYCounterClockWise;

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

/// @brief 
/// Represents the source of the bitmap. \n 
/// This structure has no responsibility for a memory.
struct ae2f_Bmp_cSrc {
	/// @brief
	/// Indexing suporter
	/// Abstraction
	ae2f_struct ae2f_rBmpIdx rIdxer;

	/// @brief
	/// size of each element[pixel] as bit
	/// bit cound [Element Size]
	ae2f_Bmp_Idxer_eBC_t ElSize;

	/// @brief
	/// Real element[pixel] vector [Global]
	uint8_t* Addr;
};

/// @brief 
/// Fills the colour for whole range in [dest].
/// @param dest 
/// The target memory.
/// @param colour
/// The colour value to fill. 
/// @return 
/// @ref ae2f_errGlob_OK
/// @exception \ 
/// @ref ae2f_errGlob_PTR_IS_NULL \n 
/// @ref ae2f_errGlob_IMP_NOT_FOUND
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_Bmp_cSrc_Fill(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	uint32_t colour
);

/// @brief 
/// Fills the colour for whole range in [dest].
/// @param dest 
/// The target memory.
/// @param colour
/// The colour value to fill. 
/// @param partial_min_x 
/// for Rect
/// @param partial_min_y 
/// for Rect
/// @param partial_max_x 
/// for Rect
/// @param partial_max_y
/// for Rect 
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_IMP_NOT_FOUND
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_Bmp_cSrc_Fill_Partial(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	uint32_t colour,

	uint32_t partial_min_x,
	uint32_t partial_min_y,
	uint32_t partial_max_x,
	uint32_t partial_max_y
);

/// @brief 
/// Gets the 3-channel or 4-channel value for given rect.
/// @param src 
/// @param retColour
/// Address where the value stored. 
/// @param _min_x 
/// for Rect
/// @param _min_y
/// for Rect
/// @param _max_x
/// for Rect
/// @param _max_y
/// for Rect
/// @param reverseIdx
/// To consider reversing index when iterating.
/// @return 
/// @ref ae2f_errGlob_OK
/// @exception \ 
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_PTR_IS_NULL
/// @see @ref ae2f_Bmp_cSrc_Copy_Global_Alpha_ReverseIdxOfX
/// @see @ref ae2f_Bmp_cSrc_Copy_Global_Alpha_ReverseIdxOfY
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_Bmp_cSrc_gDot(
	const ae2f_struct ae2f_Bmp_cSrc* src,
	uint32_t* retColour,
	ae2f_float_t _min_x,
	ae2f_float_t _min_y,
	ae2f_float_t _max_x,
	ae2f_float_t _max_y,

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
/// @return
/// @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n 
/// @ref ae2f_errGlob_IMP_NOT_FOUND 
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_Bmp_cSrc_Copy(
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
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n 
/// @ref ae2f_errGlob_IMP_NOT_FOUND
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_Bmp_cSrc_Copy_Partial(
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
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_Bmp_cSrc_Read(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	uint8_t* byte,
	size_t byteLength
);

/// @warning
/// Certain Macro is not certified.
#define ae2f_Bmp_Src_Cut(cSrc, mX, MX, mY, MY) ae2f_record_make(ae2f_struct ae2f_Bmp_cSrc, ae2f_BmpIdxCut((cSrc).rIdxer, mX, MX, mY, MX), (cSrc).ElSize, (cSrc).Addr + ae2f_BmpIdxDrive((cSrc).rIdxer, mX, mY) * (cSrc).ElSize)

#include <ae2f/Pack/End.h>

#endif
