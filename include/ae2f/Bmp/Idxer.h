#if !defined(ae2f_Bmp_Idxer_h)

#pragma region Header_def

#define ae2f_Bmp_Idxer_h

#pragma endregion

#include <stdint.h>
#include <ae2f/Macro/errGlob.h>
#include <ae2f/Macro/Compare.h>
#include <ae2f/Macro/Cast.h>

#pragma pack(push, 1)
// Suggest array as matrix.
// as element count
// IMPORTANT: DO NOT THINK THAT THEY ARE CONSIDERED AS BYTE
struct ae2f_Bmp_rIdxer {
	uint32_t 
		// Actually considered width [Global width]
		Width, 

		// the actual element count [Local Count]
		Count,

		// Describe the current position as X where an address points. [Local X start]
		CurrX,

		// Suggested width [Local Width]
		IdxXJump;
};
#pragma pack(pop)

// Also actual Width of the [rIdxer].
#define ae2f_Bmp_Idx_XLeft(rIdxer) ((rIdxer).IdxXJump - (rIdxer).CurrX)

// Also actual Height of the [rIdxer].
#define ae2f_Bmp_Idx_YLeft(rIdxer) ((rIdxer).Count / (rIdxer).Width)

#define __ae2f_Bmp_Idx_DriveX(rIdxer, dx) ae2f_static_cast(uint32_t, (dx) < ae2f_Bmp_Idx_XLeft(rIdxer) ? (dx) : -1)
#define __ae2f_Bmp_Idx_DriveY(rIdxer, dy) ae2f_static_cast(uint32_t, (dy) < ae2f_Bmp_Idx_YLeft(rIdxer) ? (dy) : -1)

// uint32_t
// Check the element index is valid.
// could returns -1 when not good.
#define ae2f_Bmp_Idx_Drive(rIdxer, dx, dy) ae2f_static_cast(uint32_t, __ae2f_Bmp_Idx_DriveX(rIdxer, dx) == ae2f_static_cast(uint32_t, -1) ? -1 : __ae2f_Bmp_Idx_DriveY(rIdxer, dy) == ae2f_static_cast(uint32_t, -1) ? -1 : __ae2f_Bmp_Idx_DriveX(rIdxer, dx) + __ae2f_Bmp_Idx_DriveY(rIdxer, dy) * (rIdxer).Width)

// ae2f_Bmp_rIdxer
#define ae2f_Bmp_Idx_Cut(rIdxer, mX, MX, mY, MY) (((ae2f_Bmp_Idx_Drive(rIdxer, mX, mY) == -1 || ae2f_Bmp_Idx_Drive(rIdxer, MX, MY)) == -1) ? ae2f_record_make(ae2f_struct ae2f_Bmp_rIdxer, 0, 0, 0, 0) : ae2f_record_make(ae2f_struct ae2f_Bmp_rIdxer, (rIdxer).Width, ae2f_Bmp_Idx_Drive(rIdxer, MX, MY), (rIdxer).CurrX + mX, (rIdxer).CurrX + MX))

#endif