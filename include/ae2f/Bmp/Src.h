#if !defined(ae2f_Bmp_Src_h)
#define ae2f_Bmp_Src_h

#include "Idx.h"
#include <ae2f/Call.h>
#include <ae2f/Float.h>
#include "./BitCount.h"
#include <ae2f/Pack/Beg.h>
#include <ae2f/mov2/Scalar.h>
#include <ae2f/mov2/Vec.h>


/// @brief 
/// Represents the source of the bitmap. \n 
/// This structure has no responsibility for a memory.
struct ae2f_cBmpSrc {
	/// @brief
	/// Indexing suporter
	/// Abstraction
	ae2f_struct ae2f_rBmpIdx rIdxer;

	/// @brief
	/// size of each element[pixel] as bit
	/// bit cound [Element Size]
	ae2f_eBmpBitCount_t ElSize;

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
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_cBmpSrcFill(
	ae2f_struct ae2f_cBmpSrc* dest,
	uint32_t colour
) noexcept;

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
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_cBmpSrcFillPartial(
	ae2f_struct ae2f_cBmpSrc* dest,
	uint32_t colour,

	uint32_t partial_min_x,
	uint32_t partial_min_y,
	uint32_t partial_max_x,
	uint32_t partial_max_y
) noexcept;

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
/// @see @ref ae2f_eBmpSrcRectCpyPrm_RVSE_I_X
/// @see @ref ae2f_eBmpSrcRectCpyPrm_RVSE_I_Y
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_cBmpSrcRectGDot(
	const ae2f_struct ae2f_cBmpSrc* src,
	uint32_t* retColour,
	ae2f_float_t _min_x,
	ae2f_float_t _min_y,
	ae2f_float_t _max_x,
	ae2f_float_t _max_y,

	uint8_t reverseIdx
) noexcept;

/// @brief 
/// `byte` is not long enough to parse.
#define ae2f_errBmpSrcRef_ARR_TOO_SHORT ae2f_errGlob_WRONG_OPERATION

#ifndef ae2f_cBmpSrcRef
/// @brief 
/// # After this operation [dest] will still not own the memory, but [byte] will.
/// @param dest 
/// Destination where the [byte] 
/// @param byte 
/// The data of bmp structure with header.
/// @param byteLength 
/// size of the [byte].
/// @return 
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_cBmpSrcRef(
	ae2f_struct ae2f_cBmpSrc* dest,
	uint8_t* byte,
	size_t byteLength
) noexcept;
#endif

/// @warning
/// Certain Macro is not certified.
#define ae2f_cBmpSrcCut(cSrc, mX, MX, mY, MY) ae2f_RecordMk(ae2f_struct ae2f_cBmpSrc, ae2f_BmpIdxCut((cSrc).rIdxer, mX, MX, mY, MX), (cSrc).ElSize, (cSrc).Addr + ae2f_BmpIdxDrive((cSrc).rIdxer, mX, mY) * (cSrc).ElSize)

#include <ae2f/Pack/End.h>

#endif
