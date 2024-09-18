#if !defined(ae2f_Bmp_Dot_h)
#define ae2f_Bmp_Dot_h

#include <ae2f/Macro/Cast.h>
#include <ae2f/Macro/BitVector.h>
#include <stdint.h>

typedef uint32_t ae2f_Bmp_Dot_rgba_t;
typedef float ae2f_Bmp_Dot_Blender_tf;
typedef double ae2f_Bmp_Dot_Blender_t;
typedef long double ae2f_Bmp_Dot_Blender_tl;

// Type explained
//	idk_t:
//		Basic calculating method must be implemented.
// 
// Parameter
//	a: idk_t
//	b: idk_t
// 
//	ratio_a: float, double, long double
//		ratio suggestion for [a] when mixed
// 
//	rtn_t: typename
//		return data type definition
// 
//	prefixForOperatee
//	f, l, or just nothing.
// 
// Return:
//	Blended value of [a] and [b] according to the [ratio_a].
#define ae2f_Bmp_Dot_Blend_imp(a, b, ratio_a, rtn_t, prefixForOperatee) ae2f_static_cast(rtn_t, (((a) * (ratio_a) + (b) * (1.0##prefixForOperatee - (ratio_a))) / 2.0##prefixForOperatee))

#define ae2f_Bmp_Dot_RGBA_GetR(rgb) ae2f_static_cast(uint8_t, ae2f_Macro_BitVector_GetRanged(ae2f_static_cast(uint32_t, rgb), 0, 8))
#define ae2f_Bmp_Dot_RGBA_GetG(rgb) ae2f_static_cast(uint8_t, ae2f_Macro_BitVector_GetRanged(ae2f_static_cast(uint32_t, rgb), 8, 16))
#define ae2f_Bmp_Dot_RGBA_GetB(rgb) ae2f_static_cast(uint8_t, ae2f_Macro_BitVector_GetRanged(ae2f_static_cast(uint32_t, rgb), 16, 24))
#define ae2f_Bmp_Dot_RGBA_GetA(rgba) ae2f_static_cast(uint8_t, ae2f_Macro_BitVector_GetRanged(ae2f_static_cast(uint32_t, rgba), 24, 32))

#define ae2f_Bmp_Dot_RGBA_SetR(rgb, val)  ae2f_static_cast(uint32_t, ae2f_Macro_BitVector_SetRanged(ae2f_static_cast(uint32_t, rgb), 0, 8, val))
#define ae2f_Bmp_Dot_RGBA_SetG(rgb, val)  ae2f_static_cast(uint32_t, ae2f_Macro_BitVector_SetRanged(ae2f_static_cast(uint32_t, rgb), 8, 16, val))
#define ae2f_Bmp_Dot_RGBA_SetB(rgb, val)  ae2f_static_cast(uint32_t, ae2f_Macro_BitVector_SetRanged(ae2f_static_cast(uint32_t, rgb), 16, 24, val))
#define ae2f_Bmp_Dot_RGBA_SetA(rgba, val) ae2f_static_cast(uint32_t, ae2f_Macro_BitVector_SetRanged(ae2f_static_cast(uint32_t, rgba), 24, 32, val))

#define ae2f_Bmp_Dot_RGB_Make(r, g, b) ae2f_static_cast(uint32_t, ae2f_static_cast(uint8_t, r) | (ae2f_static_cast(uint16_t, g) << 8) | (ae2f_static_cast(uint32_t, b) << 16))
#define ae2f_Bmp_Dot_RGBA_Make(r, g, b, a) ae2f_static_cast(uint32_t, ae2f_static_cast(uint8_t, r) | (ae2f_static_cast(uint16_t, g) << 8) | (ae2f_static_cast(uint32_t, b) << 16) | (ae2f_static_cast(uint32_t, a) << 24))
#define ae2f_Bmp_Dot_RGBA_FromRGB(rgb, a) ae2f_Bmp_Dot_RGBA_SetA(rgb, a)


#define ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, iRGB, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba1), ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba2), ae2f_Bmp_Dot_RGBA_GetA(rgba1) / (ae2f_static_cast(ae2f_Bmp_Dot_Blender_t##pfOper, ae2f_Bmp_Dot_RGBA_GetA(rgba1)) + ae2f_Bmp_Dot_RGBA_GetA(rgba2)), uint8_t, pfOper)
#define ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgb, rgba, iRGB, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba), ae2f_Bmp_Dot_RGBA_Get##iRGB(rgb), ae2f_Bmp_Dot_RGBA_GetA(rgba) / 255.0##pfOper, uint8_t, pfOper)
#define ae2f_Bmp_Dot_rRGBA_BlendA(rgba1, rgba2, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_GetA(rgba1), ae2f_Bmp_Dot_RGBA_GetB(rgba2), 0.5##pfOper, ae2f_Bmp_Dot_Blender_t##pfOper, pfOper)

#define ae2f_Bmp_Dot_rRGBA_BlendRGB(rgb, rgba, pfOper) ae2f_Bmp_Dot_RGB_Make(ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, R, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, G, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, B, pfOper))
#define ae2f_Bmp_Dot_rRGBA_BlendRGBA(rgba1, rgba2, pfOper) ae2f_Bmp_Dot_RGBA_Make(ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, R, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, G, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, B, pfOper), ae2f_Bmp_Dot_rRGBA_BlendA(rgba1, rgba2, pfOper))

#endif // !defined(ae2f_Bmp_Dot_h)

#if !defined(ae2f_Bmp_Dot_hpp) && defined(__cplusplus)
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
			const rRGB Blend(const rRGB background, const rRGBA colour_to_blend) noexcept;

			template<eBlendPostFix::_ = eBlendPostFix::F>
			const rRGB Blend(const rRGBA __colour_A, const rRGBA __colour_B) noexcept;

			template<>
			const rRGB Blend<eBlendPostFix::F>(const rRGB background, const rRGBA colour_to_blend) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGB(background.inst, colour_to_blend.inst, f);
			}

			template<>
			const rRGB Blend<eBlendPostFix::F>(const rRGBA __colour_A, const rRGBA __colour_B) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGBA(__colour_A.inst, __colour_B.inst, f);
			}

			template<>
			const rRGB Blend<eBlendPostFix::D>(const rRGB background, const rRGBA colour_to_blend) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGB(background.inst, colour_to_blend.inst, );
			}

			template<>
			const rRGB Blend<eBlendPostFix::D>(const rRGBA __colour_A, const rRGBA __colour_B) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGBA(__colour_A.inst, __colour_B.inst, );
			}

			template<>
			const rRGB Blend<eBlendPostFix::L>(const rRGB background, const rRGBA colour_to_blend) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGB(background.inst, colour_to_blend.inst, l);
			}

			template<>
			const rRGB Blend<eBlendPostFix::L>(const rRGBA __colour_A, const rRGBA __colour_B) noexcept {
				return ae2f_Bmp_Dot_rRGBA_BlendRGBA(__colour_A.inst, __colour_B.inst, l);
			}
		}
	}
}

#endif // !defined(ae2f_Bmp_Dot_hpp)
