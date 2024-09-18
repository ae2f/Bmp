#if !defined(ae2f_Bmp_Idxer_h)
#define ae2f_Bmp_Idxer_h

#include <stdint.h>
#include <ae2f/Macro/errGlobal.h>
#include <ae2f/Macro/Compare.h>
#include <ae2f/Macro/Cast.h>

enum ae2f_Bmp_Idxer_eBC {
	ae2f_Bmp_Idxer_eBC_BIT = 1,
	ae2f_Bmp_Idxer_eBC_HALF = 4,
	ae2f_Bmp_Idxer_eBC_BYTE = 8,
	ae2f_Bmp_Idxer_eBC_RGB = 24,
	ae2f_Bmp_Idxer_eBC_RGBA = 32,

	ae2f_Bmp_Idxer_eBC_REMINDER_OWNER = 64
};

typedef uint8_t ae2f_Bmp_Idxer_eBC_t;

struct ae2f_Bmp_rIdxer {
	// as element count
	uint32_t Width, Count, CurrX, IdxXJump;
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



#endif // !defined(ae2f_Bmp_Idxer_h)

#if defined(__cplusplus) && !defined(ae2f_Bmp_Idxer_hpp)
#define ae2f_Bmp_Idxer_hpp

namespace ae2f {
	namespace Bmp {
		struct Idxer : public ae2f_Bmp_rIdxer {
			constexpr Idxer(uint32_t width, uint32_t count, uint32_t currentX) 
				noexcept : ae2f_Bmp_rIdxer{width, count, currentX} {}

			constexpr uint32_t Drive(uint32_t dx, uint32_t dy) const noexcept {
				return ae2f_Bmp_Idx_Drive(this[0], dx, dy);
			}
		};
	}
}

#endif // !defined(__cplusplus)