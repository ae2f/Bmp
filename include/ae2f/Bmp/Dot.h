#if !defined(ae2f_Bmp_Dot_h)

#pragma region dot_h_def

/// @brief
/// Predefined string for content of this header.
#define ae2f_Bmp_Dot_h \
"typedef uint ae2f_Bmp_Dot_rgba_t;" \
"typedef float ae2f_Bmp_Dot_Blender_tf;" \
"typedef double ae2f_Bmp_Dot_Blender_t;" \
"typedef long double ae2f_Bmp_Dot_Blender_tl;" \
\
"\n#define _ae2f_Bmp_Dot_RGBA_Get(rgb, bidx, eidx) ((uchar)((((((uint)(rgb))) >> (0)) & ((uchar)((sizeof(uchar) << 3) == ((eidx) - (bidx)) ? ((uchar)(-1)) : (((uchar)(((uchar)(1)) << ((eidx) - (bidx)))) - 1))))))" \
"\n#define ae2f_Bmp_Dot_RGBA_GetR(rgb) _ae2f_Bmp_Dot_RGBA_Get(rgb, 0, 8)" \
"\n#define ae2f_Bmp_Dot_RGBA_GetG(rgb) _ae2f_Bmp_Dot_RGBA_Get(rgb, 8, 16)" \
"\n#define ae2f_Bmp_Dot_RGBA_GetB(rgb) _ae2f_Bmp_Dot_RGBA_Get(rgb, 16, 24)" \
"\n#define ae2f_Bmp_Dot_RGBA_GetA(rgb) _ae2f_Bmp_Dot_RGBA_Get(rgb, 24, 32)" \
\
"\n#define _ae2f_Bmp_Dot_RGBA_Set(a, b, c, d) ((uint)(((((uint)(a))) & (~((((uint)((sizeof(uint) << 3) == ((d) - (c)) ? ((uint)(-1)) : (((uint)(((uint)(1)) << ((d) - (c)))) - 1)))) << c)) | ((b) << c))))" \
"\n#define ae2f_Bmp_Dot_RGBA_SetR(rgb, val) _ae2f_Bmp_Dot_RGBA_Set(rgb, val, 0, 8)" \
"\n#define ae2f_Bmp_Dot_RGBA_SetG(rgb, val) _ae2f_Bmp_Dot_RGBA_Set(rgb, val, 8, 16)" \
"\n#define ae2f_Bmp_Dot_RGBA_SetB(rgb, val) _ae2f_Bmp_Dot_RGBA_Set(rgb, val, 16, 24)" \
"\n#define ae2f_Bmp_Dot_RGBA_SetA(rgb, val) _ae2f_Bmp_Dot_RGBA_Set(rgb, val, 24, 32)" \
\
"\n#define ae2f_Bmp_Dot_RGB_Make(r, g, b) (((uchar)(r)) | ((ushort)(g) << 8) | ((uint)(b) << 16))" \
"\n#define ae2f_Bmp_Dot_RGBA_Make(r, g, b, a) (((uchar)(r)) | ((ushort)(g) << 8) | ((uint)(b) << 16) | ((uint)(a) << 24))" \
"\n#define ae2f_Bmp_Dot_RGBA_FromRGB(rgb, a) ae2f_Bmp_Dot_RGBA_SetA(rgb, a)" \
\
"\n#define ae2f_Bmp_Dot_Blend_imp(a, b, c, d, e) ((d)((((a) * (c) + (b) * (1.0##e - (c))))))" \
\
"\n#define ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, iRGB, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba1), ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba2), ae2f_Bmp_Dot_RGBA_GetA(rgba1) / (((ae2f_Bmp_Dot_Blender_t##pfOper)ae2f_Bmp_Dot_RGBA_GetA(rgba1)) + ae2f_Bmp_Dot_RGBA_GetA(rgba2)), uchar, pfOper)" \
"\n#define ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgb, rgba, iRGB, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba), ae2f_Bmp_Dot_RGBA_Get##iRGB(rgb), ae2f_Bmp_Dot_RGBA_GetA(rgba) / 255.0##pfOper, uchar, pfOper)" \
"\n#define ae2f_Bmp_Dot_rRGBA_BlendA(rgba1, rgba2, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_GetA(rgba1), ae2f_Bmp_Dot_RGBA_GetB(rgba2), 0.5##pfOper, ae2f_Bmp_Dot_Blender_t##pfOper, pfOper)" \
\
"\n#define ae2f_Bmp_Dot_rRGBA_BlendRGB(rgb, rgba, pfOper) ae2f_Bmp_Dot_RGB_Make(ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, R, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, G, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, B, pfOper))" \
"\n#define ae2f_Bmp_Dot_rRGBA_BlendRGBA(rgba1, rgba2, pfOper) ae2f_Bmp_Dot_RGBA_Make(ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, R, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, G, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, B, pfOper), ae2f_Bmp_Dot_rRGBA_BlendA(rgba1, rgba2, pfOper))" \
\

#pragma endregion

#include <ae2f/Macro/Cast.h>
#include <ae2f/Macro/BitVec.h>
#include <stdint.h>

typedef uint8_t uchar;
typedef uint16_t ushort;
typedef uint32_t uint;

typedef uint ae2f_Bmp_Dot_rgba_t;
typedef float ae2f_Bmp_Dot_Blender_tf;
typedef double ae2f_Bmp_Dot_Blender_t;
typedef long double ae2f_Bmp_Dot_Blender_tl;



#define ae2f_Bmp_Dot_RGBA_GetR(rgb) ae2f_static_cast(uchar, ae2f_Macro_BitVec_GetRanged(ae2f_static_cast(uint, rgb), 0, 8))
#define ae2f_Bmp_Dot_RGBA_GetG(rgb) ae2f_static_cast(uchar, ae2f_Macro_BitVec_GetRanged(ae2f_static_cast(uint, rgb), 8, 16))
#define ae2f_Bmp_Dot_RGBA_GetB(rgb) ae2f_static_cast(uchar, ae2f_Macro_BitVec_GetRanged(ae2f_static_cast(uint, rgb), 16, 24))
#define ae2f_Bmp_Dot_RGBA_GetA(rgba) ae2f_static_cast(uchar, ae2f_Macro_BitVec_GetRanged(ae2f_static_cast(uint, rgba), 24, 32))

#define ae2f_Bmp_Dot_RGBA_SetR(rgb, val)  ae2f_static_cast(uint, ae2f_Macro_BitVec_SetRanged(ae2f_static_cast(uint, rgb), 0, 8, val))
#define ae2f_Bmp_Dot_RGBA_SetG(rgb, val)  ae2f_static_cast(uint, ae2f_Macro_BitVec_SetRanged(ae2f_static_cast(uint, rgb), 8, 16, val))
#define ae2f_Bmp_Dot_RGBA_SetB(rgb, val)  ae2f_static_cast(uint, ae2f_Macro_BitVec_SetRanged(ae2f_static_cast(uint, rgb), 16, 24, val))
#define ae2f_Bmp_Dot_RGBA_SetA(rgba, val) ae2f_static_cast(uint, ae2f_Macro_BitVec_SetRanged(ae2f_static_cast(uint, rgba), 24, 32, val))

#define ae2f_Bmp_Dot_RGB_Make(r, g, b) ae2f_static_cast(uint, ae2f_static_cast(uchar, r) | (ae2f_static_cast(ushort, g) << 8) | (ae2f_static_cast(uint, b) << 16))
#define ae2f_Bmp_Dot_RGBA_Make(r, g, b, a) ae2f_static_cast(uint, ae2f_static_cast(uchar, r) | (ae2f_static_cast(ushort, g) << 8) | (ae2f_static_cast(uint, b) << 16) | (ae2f_static_cast(uint, a) << 24))
#define ae2f_Bmp_Dot_RGBA_FromRGB(rgb, a) ae2f_Bmp_Dot_RGBA_SetA(rgb, a)

/// @tparam	idk_t
///	The type where basic calculating method must be implemented.
/// 
/// @tparam rtn_t
/// return data type definition
/// 
///	@param a:   idk_t
///	@param b:   idk_t
/// 
///	@param ratio_a 
/// float / double / long double
/// 
///	ratio suggestion for [a] when mixed
/// 
/// Must be within 0 ~ 1
///	@param prefixForOperatee
///	f, l, or just nothing.
/// 
/// @returns
///	Blended value of [a] and [b] according to the [ratio_a].
#define ae2f_Bmp_Dot_Blend_imp(a, b, ratio_a, rtn_t, prefixForOperatee) ae2f_static_cast(rtn_t, (((a) * (ratio_a) + (b) * (1.0##prefixForOperatee - (ratio_a)))))

#define ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, iRGB, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba1), ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba2), ae2f_Bmp_Dot_RGBA_GetA(rgba1) / (ae2f_static_cast(ae2f_Bmp_Dot_Blender_t##pfOper, ae2f_Bmp_Dot_RGBA_GetA(rgba1)) + ae2f_Bmp_Dot_RGBA_GetA(rgba2)), uchar, pfOper)
#define ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgb, rgba, iRGB, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba), ae2f_Bmp_Dot_RGBA_Get##iRGB(rgb), ae2f_Bmp_Dot_RGBA_GetA(rgba) / 255.0##pfOper, uchar, pfOper)
#define ae2f_Bmp_Dot_rRGBA_BlendA(rgba1, rgba2, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_GetA(rgba1), ae2f_Bmp_Dot_RGBA_GetB(rgba2), 0.5##pfOper, ae2f_Bmp_Dot_Blender_t##pfOper, pfOper)

#define ae2f_Bmp_Dot_rRGBA_BlendRGB(rgb, rgba, pfOper) ae2f_Bmp_Dot_RGB_Make(ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, R, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, G, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, B, pfOper))
#define ae2f_Bmp_Dot_rRGBA_BlendRGBA(rgba1, rgba2, pfOper) ae2f_Bmp_Dot_RGBA_Make(ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, R, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, G, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, B, pfOper), ae2f_Bmp_Dot_rRGBA_BlendA(rgba1, rgba2, pfOper))

#endif