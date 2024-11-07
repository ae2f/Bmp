#include "./Dot.h"

#if !defined(ae2f_Bmp_Dot_hpp)
#define ae2f_Bmp_Dot_hpp

namespace ae2f {
	namespace Bmp {
		namespace Dot {
			namespace eBlendPostFix {
				enum _ {
					F, D, L
				};
			}

			struct rRGB {
				uint32_t inst;
				constexpr rRGB(uint32_t a) noexcept : inst(a) {}
				constexpr rRGB(uint8_t r, uint8_t g, uint8_t b) noexcept
					: inst(ae2f_Bmp_Dot_RGB_Make(r, g, b)) {}

				constexpr uint8_t R() const noexcept {
					return ae2f_Bmp_Dot_RGBA_GetR(this->inst);
				}
				constexpr const rRGB R(uint8_t val) const noexcept {
					return ae2f_Bmp_Dot_RGBA_SetR(this->inst, val);
				}

				constexpr uint8_t G() const noexcept {
					return ae2f_Bmp_Dot_RGBA_GetG(this->inst);
				}
				constexpr const rRGB G(uint8_t val) const noexcept  {
					return ae2f_Bmp_Dot_RGBA_SetG(this->inst, val);
				}

				constexpr uint8_t B() const noexcept {
					return ae2f_Bmp_Dot_RGBA_GetB(this->inst);
				}
				constexpr const rRGB B(uint8_t val) const noexcept {
					return ae2f_Bmp_Dot_RGBA_SetB(this->inst, val);
				}
			};
			
			struct rRGBA : public rRGB {
				constexpr rRGBA(uint32_t a) noexcept : rRGB(a) {}
				constexpr rRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept
					: rRGB(ae2f_Bmp_Dot_RGBA_Make(r, g, b, a)) {}
				constexpr rRGBA(const rRGB rgb, uint8_t a = 255) noexcept
					: rRGB(ae2f_Bmp_Dot_RGBA_FromRGB(rgb.inst, a)) {}
				constexpr uint8_t A() const noexcept {
					return ae2f_Bmp_Dot_RGBA_GetA(this->inst);
				}
				constexpr const rRGBA A(uint8_t a) const noexcept {
					return ae2f_Bmp_Dot_RGBA_SetA(this->inst, a);
				}
			};

			template<eBlendPostFix::_ = eBlendPostFix::F>
			constexpr rRGB Blend(const rRGB background, const rRGBA colour_to_blend) noexcept;

			template<eBlendPostFix::_ = eBlendPostFix::F>
			constexpr rRGB Blend(const rRGBA __colour_A, const rRGBA __colour_B) noexcept;

			template<>
			constexpr rRGB Blend<eBlendPostFix::F>(const rRGB background, const rRGBA colour_to_blend) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGB(background.inst, colour_to_blend.inst, f);
			}

			template<>
			constexpr rRGB Blend<eBlendPostFix::F>(const rRGBA __colour_A, const rRGBA __colour_B) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGBA(__colour_A.inst, __colour_B.inst, f);
			}

			
			template<>
			constexpr rRGB Blend<eBlendPostFix::D>(const rRGB background, const rRGBA colour_to_blend) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGB(background.inst, colour_to_blend.inst, );
			}

			template<>
			constexpr rRGB Blend<eBlendPostFix::D>(const rRGBA __colour_A, const rRGBA __colour_B) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGBA(__colour_A.inst, __colour_B.inst, );
			}

			template<>
			constexpr rRGB Blend<eBlendPostFix::L>(const rRGB background, const rRGBA colour_to_blend) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGB(background.inst, colour_to_blend.inst, l);
			}

			template<>
			constexpr rRGB Blend<eBlendPostFix::L>(const rRGBA __colour_A, const rRGBA __colour_B) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGBA(__colour_A.inst, __colour_B.inst, l);
			}
		}
	}
}

#endif // !defined(ae2f_Bmp_Dot_hpp)