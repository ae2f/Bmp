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
/// A global parameter for @ref ae2f_cBmpSrcCpy.
struct ae2f_cBmpSrcCpyPrm {
	uint8_t 
		/// @brief
		/// Global Alpha for RGB architect.
		Alpha,
		/// @brief
		/// For reversed copy.
		ReverseIdx;


	ae2f_Mov2Scalar_t 
		/// @brief Resizers
		Resz, 
		/// @brief Address for destination
		AddrDest;

	uint32_t  
		/// @brief Data to ignore
		DataToIgnore;

	
	/// @brief Rotation in a unit of radian
	ae2f_float_t RotateXYCounterClockWise;

	/// @brief
	/// The position of rotation Axis
	ae2f_Mov2Vec_t Axis;
};

/// @brief
/// @ref ae2f_cBmpSrcCpyPrm::ReverseIdx
#define ae2f_eBmpSrcCpyPrm_RVSE_I_X 0b01

/// @brief
/// @ref ae2f_cBmpSrcCpyPrm::ReverseIdx
#define ae2f_eBmpSrcCpyPrm_RVSE_I_Y 0b10

/// @brief
/// Contains additional the colour values for indexed bmp.
/// @param len Length of the colour index.
/// @see ae2f_cBmpSrcCpyPrm
#define ae2f_cBmpSrcCpyPrmDef(len) struct ae2f_cBmpSrcCpyPrmDef_i##len { ae2f_struct ae2f_cBmpSrcCpyPrm global; uint32_t ColourIdx[len]; }

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
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_cBmpSrcFillPartial(
	ae2f_struct ae2f_cBmpSrc* dest,
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
/// @see @ref ae2f_eBmpSrcCpyPrm_RVSE_I_X
/// @see @ref ae2f_eBmpSrcCpyPrm_RVSE_I_Y
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_cBmpSrcGDot(
	const ae2f_struct ae2f_cBmpSrc* src,
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
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_cBmpSrcCpy(
	ae2f_struct ae2f_cBmpSrc* dest,
	const ae2f_struct ae2f_cBmpSrc* src,
	const ae2f_struct ae2f_cBmpSrcCpyPrm* srcprm
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
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_cBmpSrcCpyPartial(
	ae2f_struct ae2f_cBmpSrc* dest,
	const ae2f_struct ae2f_cBmpSrc* src,
	const ae2f_struct ae2f_cBmpSrcCpyPrm* srcprm,
	uint32_t partial_min_x,
	uint32_t partial_min_y,
	uint32_t partial_max_x,
	uint32_t partial_max_y
);

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
);
#endif

/// @warning
/// Certain Macro is not certified.
#define ae2f_cBmpSrcCut(cSrc, mX, MX, mY, MY) ae2f_record_make(ae2f_struct ae2f_cBmpSrc, ae2f_BmpIdxCut((cSrc).rIdxer, mX, MX, mY, MX), (cSrc).ElSize, (cSrc).Addr + ae2f_BmpIdxDrive((cSrc).rIdxer, mX, mY) * (cSrc).ElSize)

#include <ae2f/Pack/End.h>

#endif
