#if !defined(ae2f_Bmp_Idxer_h)
#define ae2f_Bmp_Idxer_h

#include <ae2f/errGlob.h>
#include <ae2f/Cmp.h>
#include <ae2f/Cast.h>

#include <ae2f/Pack/Beg.h>

/// @brief
/// Suggest array as matrix.
/// @warning 
/// Certain structure has no responsibility for considering size of each elements. 
struct ae2f_rBmpIdx {
	uint32_t 
		/// @brief Actually considered width [Global width]
		Width, 

		/// @brief The actual element count [Local Count]
		Count,

		/// @brief Describe the current position as X where an address points. [Local X start]
		CurrX,

		/// @brief Suggested width [Local Width]
		IdxXJump;
};

#include <ae2f/Pack/End.h>

/// @brief An actual Width of the @ref ae2f_rBmpIdx.
#define ae2f_BmpIdxW(rIdxer) ((rIdxer).IdxXJump - (rIdxer).CurrX)

/// @brief An actual Height of the @ref ae2f_rBmpIdx.
#define ae2f_BmpIdxH(rIdxer) ((rIdxer).Count / (rIdxer).Width)

/// @warning
/// Direct use of this macro is not recommended.
/// @see ae2f_BmpIdxDrive
#define ae2f_BmpIdxDriveX_imp(rIdxer, dx) ae2f_static_cast(uint32_t, (dx) < ae2f_BmpIdxW(rIdxer) ? (dx) : -1)

/// @warning
/// Direct use of this macro is not recommended.
/// @see ae2f_BmpIdxDrive
#define ae2f_BmpIdxDriveY_imp(rIdxer, dy) ae2f_static_cast(uint32_t, (dy) < ae2f_BmpIdxH(rIdxer) ? (dy) : -1)

/// @brief
/// The result index is not valid.
/// @see ae2f_BmpIdxDrive
#define ae2f_eBmpIdxDrive_BAD_IDX ae2f_static_cast(uint32_t, -1)

/// @brief
/// Calculates the linear index based on info from [rIdxer].
/// @param rIdxer { @ref ae2f_rBmpIdx }
/// @param dx { uint32_t } Distance as x
/// @param dy { uint32_t } Distance as y
/// @return {uint32_t} \n
/// The actual index for linear memory.
/// @exception \
/// @ref ae2f_eBmpIdxDrive_BAD_IDX
#define ae2f_BmpIdxDrive(rIdxer, dx, dy) ae2f_static_cast(uint32_t, ae2f_BmpIdxDriveX_imp(rIdxer, dx) == ae2f_static_cast(uint32_t, -1) ? -1 : ae2f_BmpIdxDriveY_imp(rIdxer, dy) == ae2f_static_cast(uint32_t, -1) ? -1 : ae2f_BmpIdxDriveX_imp(rIdxer, dx) + ae2f_BmpIdxDriveY_imp(rIdxer, dy) * (rIdxer).Width)

/// @warning
/// Certain macro is not certified.
/// @todo 
/// Add a test for it
/// @brief
/// Makes a new structure with original indexer.
/// @see ae2f_rBmpIdx
#define ae2f_BmpIdxCut(rIdxer, mX, MX, mY, MY) (((ae2f_BmpIdxDrive(rIdxer, mX, mY) == -1 || ae2f_BmpIdxDrive(rIdxer, MX, MY)) == -1) ? ae2f_record_make(ae2f_struct ae2f_rBmpIdx, 0, 0, 0, 0) : ae2f_record_make(ae2f_struct ae2f_rBmpIdx, (rIdxer).Width, ae2f_BmpIdxDrive(rIdxer, MX, MY), (rIdxer).CurrX + mX, (rIdxer).CurrX + MX))

#endif