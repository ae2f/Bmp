#include <ae2f/Bmp/Idxer.h>

#if !defined(ae2f_Bmp_Idxer_hpp)
#define ae2f_Bmp_Idxer_hpp

namespace ae2f {
	namespace Bmp {
		struct Idxer : public ae2f_Bmp_rIdxer {
			constexpr Idxer(const Idxer& r, uint32_t minX, uint32_t maxX, uint32_t minY, uint32_t maxY)
				noexcept : ae2f_Bmp_rIdxer(ae2f_Bmp_Idx_Cut(r, minX, maxX, minY, maxY)) {}

			constexpr Idxer(uint32_t width, uint32_t count, uint32_t currentX) 
				noexcept : ae2f_Bmp_rIdxer{width, count, currentX} {}

			constexpr uint32_t Drive(uint32_t dx, uint32_t dy) const noexcept {
				return ae2f_Bmp_Idx_Drive(this[0], dx, dy);
			}
		};
	}
}

#endif // !defined(__cplusplus)