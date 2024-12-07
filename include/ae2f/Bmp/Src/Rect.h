#ifndef ae2f_Bmp_Src_Rect_h
#define ae2f_Bmp_Src_Rect_h

#include "../Src.h"

/// @brief 
/// A global parameter for @ref ae2f_cBmpSrcRectCpy.
struct ae2f_cBmpSrcRectCpyPrm {
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
/// @ref ae2f_cBmpSrcRectCpyPrm::ReverseIdx
#define ae2f_eBmpSrcRectCpyPrm_RVSE_I_X 0b01

/// @brief
/// @ref ae2f_cBmpSrcRectCpyPrm::ReverseIdx
#define ae2f_eBmpSrcRectCpyPrm_RVSE_I_Y 0b10

/// @brief
/// Contains additional the colour values for indexed bmp.
/// @param len Length of the colour index.
/// @see ae2f_cBmpSrcRectCpyPrm
#define ae2f_cBmpSrcRectCpyPrmDef(len) struct ae2f_cBmpSrcRectCpyPrmDef_i##len { ae2f_struct ae2f_cBmpSrcRectCpyPrm global; uint32_t ColourIdx[len]; }

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
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_cBmpSrcRectCpy(
	ae2f_struct ae2f_cBmpSrc* dest,
	const ae2f_struct ae2f_cBmpSrc* src,
	const ae2f_struct ae2f_cBmpSrcRectCpyPrm* srcprm
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
ae2f_extern ae2f_SHAREDCALL ae2f_err_t ae2f_cBmpSrcRectCpyPartial(
	ae2f_struct ae2f_cBmpSrc* dest,
	const ae2f_struct ae2f_cBmpSrc* src,
	const ae2f_struct ae2f_cBmpSrcRectCpyPrm* srcprm,
	uint32_t partial_min_x,
	uint32_t partial_min_y,
	uint32_t partial_max_x,
	uint32_t partial_max_y
);


#endif 