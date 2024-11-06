#if !defined(ae2f_Bmp_Idxer_h)

#pragma region Header_def

#define ae2f_Bmp_Idxer_h

#pragma endregion

#include <ae2f/Macro/errGlob.h>
#include <ae2f/Macro/Cmp.h>
#include <ae2f/Macro/Cast.h>

#pragma pack(push, 1)

/// @brief
/// Suggest array as matrix.
/// @warning 
/// Certain structure has no responsibility for considering size of each elements. 
struct ae2f_Bmp_rIdxer {
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

#pragma pack(pop)

/// @brief An actual Width of the @ref ae2f_Bmp_rIdxer.
#define ae2f_Bmp_Idx_XLeft(rIdxer) ((rIdxer).IdxXJump - (rIdxer).CurrX)

/// @brief An actual Height of the @ref ae2f_Bmp_rIdxer.
#define ae2f_Bmp_Idx_YLeft(rIdxer) ((rIdxer).Count / (rIdxer).Width)

/// @warning
/// Direct use of this macro is not recommended.
/// @see ae2f_Bmp_Idx_Drive
#define __ae2f_Bmp_Idx_DriveX(rIdxer, dx) ae2f_static_cast(uint32_t, (dx) < ae2f_Bmp_Idx_XLeft(rIdxer) ? (dx) : -1)

/// @warning
/// Direct use of this macro is not recommended.
/// @see ae2f_Bmp_Idx_Drive
#define __ae2f_Bmp_Idx_DriveY(rIdxer, dy) ae2f_static_cast(uint32_t, (dy) < ae2f_Bmp_Idx_YLeft(rIdxer) ? (dy) : -1)

/// @brief
/// The result index is not valid.
/// @see ae2f_Bmp_Idx_Drive
#define ae2f_Bmp_Idx_Drive_BAD_IDX ae2f_static_cast(uint32_t, -1)

/// @brief
/// Calculates the linear index based on info from [rIdxer].
/// @param rIdxer { @ref ae2f_Bmp_rIdxer }
/// @param dx { uint32_t } Distance as x
/// @param dy { uint32_t } Distance as y
/// @return {uint32_t} \n
/// The actual index for linear memory.
/// @exception \
/// @ref ae2f_Bmp_Idx_Drive_BAD_IDX
#define ae2f_Bmp_Idx_Drive(rIdxer, dx, dy) ae2f_static_cast(uint32_t, __ae2f_Bmp_Idx_DriveX(rIdxer, dx) == ae2f_static_cast(uint32_t, -1) ? -1 : __ae2f_Bmp_Idx_DriveY(rIdxer, dy) == ae2f_static_cast(uint32_t, -1) ? -1 : __ae2f_Bmp_Idx_DriveX(rIdxer, dx) + __ae2f_Bmp_Idx_DriveY(rIdxer, dy) * (rIdxer).Width)

/// @warning
/// Certain macro is not certified.
/// @todo 
/// Add a test for it
/// @brief
/// Makes a new structure with original indexer.
/// @see ae2f_Bmp_rIdxer
#define ae2f_Bmp_Idx_Cut(rIdxer, mX, MX, mY, MY) (((ae2f_Bmp_Idx_Drive(rIdxer, mX, mY) == -1 || ae2f_Bmp_Idx_Drive(rIdxer, MX, MY)) == -1) ? ae2f_record_make(ae2f_struct ae2f_Bmp_rIdxer, 0, 0, 0, 0) : ae2f_record_make(ae2f_struct ae2f_Bmp_rIdxer, (rIdxer).Width, ae2f_Bmp_Idx_Drive(rIdxer, MX, MY), (rIdxer).CurrX + mX, (rIdxer).CurrX + MX))

#endif