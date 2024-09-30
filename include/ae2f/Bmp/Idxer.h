#if !defined(ae2f_Bmp_Idxer_h)
#define ae2f_Bmp_Idxer_h

#include <stdint.h>
#include <ae2f/Macro/errGlobal.h>
#include <ae2f/Macro/Compare.h>
#include <ae2f/Macro/Cast.h>

// Enum about Bit Count
enum ae2f_Bmp_Idxer_eBC {
	ae2f_Bmp_Idxer_eBC_BIT = 1,
	ae2f_Bmp_Idxer_eBC_HALF = 4,
	ae2f_Bmp_Idxer_eBC_BYTE = 8,
	ae2f_Bmp_Idxer_eBC_RGB = 24,
	ae2f_Bmp_Idxer_eBC_RGBA = 32,

	ae2f_Bmp_Idxer_eBC_REMINDER_OWNER = 64
};

typedef uint8_t ae2f_Bmp_Idxer_eBC_t;


// Suggest array as matrix.
// as element count
// IMPORTANT: DO NOT THINK THAT THEY ARE CONSIDERED AS BYTE
struct ae2f_Bmp_rIdxer {
	uint32_t 
		// Actually considered width
		Width, 
		// the actual element count
		Count, 
		// Describe the current position as X where an address points.
		CurrX,
		// Suggested width
		IdxXJump;
};

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

#endif // !defined(ae2f_Bmp_Idxer_h)