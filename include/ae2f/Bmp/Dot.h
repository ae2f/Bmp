#if !defined(ae2f_Bmp_Dot_h)

#pragma region dot_h_def
#define ae2f_Bmp_Dot_h

#pragma endregion

#include <ae2f/Macro/Cast.h>
#include <ae2f/Macro/BitVec.h>

typedef uint8_t uchar;
typedef uint16_t ushort;
typedef uint32_t uint;

/// @brief 
/// 32 - byte which means has four channels of [r, g, b, a].
typedef uint ae2f_Bmp_Dot_rgba_t;

/// @brief 
/// For blending(float point) as float
typedef float ae2f_Bmp_Dot_Blender_tf;

/// @brief 
/// For blending(float point) as double
typedef double ae2f_Bmp_Dot_Blender_t;

/// @brief 
/// For blending(float point) as long double
typedef long double ae2f_Bmp_Dot_Blender_tl;

/// @brief
/// Gets the value of channel [R]
/// @param rgb {uint32_t} 
/// 3-channel colour integer.
#define ae2f_Bmp_Dot_RGBA_GetR(rgb) ae2f_static_cast(uchar, ae2f_Macro_BitVec_GetRanged(ae2f_static_cast(uint, rgb), 0, 8))

/// @brief
/// Gets the value of channel [G]
/// @param rgb {uint32_t} 3-channel colour integer.
#define ae2f_Bmp_Dot_RGBA_GetG(rgb) ae2f_static_cast(uchar, ae2f_Macro_BitVec_GetRanged(ae2f_static_cast(uint, rgb), 8, 16))

/// @brief
/// Gets the value of channel [B]
/// @param rgb {uint32_t} 3-channel colour integer.
#define ae2f_Bmp_Dot_RGBA_GetB(rgb) ae2f_static_cast(uchar, ae2f_Macro_BitVec_GetRanged(ae2f_static_cast(uint, rgb), 16, 24))

/// @brief
/// Gets the value of channel [A]
/// @param rgba {uint32_t} 4-channel colour integer.
#define ae2f_Bmp_Dot_RGBA_GetA(rgba) ae2f_static_cast(uchar, ae2f_Macro_BitVec_GetRanged(ae2f_static_cast(uint, rgba), 24, 32))

/// @brief
/// Sets the value of channel [R]
/// @param rgb {uint32_t}
/// @param val The value to set
#define ae2f_Bmp_Dot_RGBA_SetR(rgb, val)  ae2f_static_cast(uint, ae2f_Macro_BitVec_SetRanged(ae2f_static_cast(uint, rgb), 0, 8, val))

/// @brief
/// Sets the value of channel [G]
/// @param rgb {uint32_t}
/// @param val The value to set
#define ae2f_Bmp_Dot_RGBA_SetG(rgb, val)  ae2f_static_cast(uint, ae2f_Macro_BitVec_SetRanged(ae2f_static_cast(uint, rgb), 8, 16, val))

/// @brief
/// Sets the value of channel [B]
/// @param rgb {uint32_t}
/// @param val The value to set
#define ae2f_Bmp_Dot_RGBA_SetB(rgb, val)  ae2f_static_cast(uint, ae2f_Macro_BitVec_SetRanged(ae2f_static_cast(uint, rgb), 16, 24, val))

/// @brief
/// Sets the value of channel [A]
/// @param rgba {uint32_t}
/// @param val The value to set
#define ae2f_Bmp_Dot_RGBA_SetA(rgba, val) ae2f_static_cast(uint, ae2f_Macro_BitVec_SetRanged(ae2f_static_cast(uint, rgba), 24, 32, val))

/// @brief
/// Generates a new number with three channels configured(initialised).
/// @param r 
/// Initial Value for channel [R]
/// @param g 
/// Initial Value for channel [G]
/// @param b 
/// Initial Value for channel [B]
/// @return {uint32_t} 3-channel colour integer.
#define ae2f_Bmp_Dot_RGB_Make(r, g, b) ae2f_static_cast(uint, ae2f_static_cast(uchar, r) | (ae2f_static_cast(ushort, g) << 8) | (ae2f_static_cast(uint, b) << 16))

/// @brief
/// Generates a new number with four channels configured(initialised).
/// @param r 
/// Initial Value for channel [R]
/// @param g 
/// Initial Value for channel [G]
/// @param b 
/// Initial Value for channel [B]
/// @param a
/// Initial Value for channel [A]
/// @return {uint32_t} 4-channel colour integer.
#define ae2f_Bmp_Dot_RGBA_Make(r, g, b, a) ae2f_static_cast(uint, ae2f_static_cast(uchar, r) | (ae2f_static_cast(ushort, g) << 8) | (ae2f_static_cast(uint, b) << 16) | (ae2f_static_cast(uint, a) << 24))


/// @brief
/// Generates a new number with seed of [RGB] and initialising value for channel [A].
/// @param rgb
/// Seed RGB Channels
/// @param a
/// Initial value for Channel [A]
/// @return {uint32_t}
#define ae2f_Bmp_Dot_RGBA_FromRGB(rgb, a) ae2f_Bmp_Dot_RGBA_SetA(rgb, a)

/// @brief
/// The implementation of channel blending.
/// @param a {rtn_t}
/// Channel under operation.
/// @param b {rtn_t}
/// Channel under operation.
/// @param ratio_a
/// Ratio for [a].
/// @tparam rtn_t {typename}
/// Data type to return. \n
/// Normally equals to channel type.
/// @tparam prefixForOperatee {f | l | }
/// decides the data type for literal floating type (1.0) on calculation.
/// @warning choose between f, l, or nothing otherwise would cause error.
/// @return {rtn_t} The blended value.
#define ae2f_Bmp_Dot_Blend_imp(a, b, ratio_a, rtn_t, prefixForOperatee) ae2f_static_cast(rtn_t, (((a) * (ratio_a) + (b) * (1.0##prefixForOperatee - (ratio_a)))))

/// @brief
/// Get each channel of two, blend two based on Alpha Channel.
/// @param rgba1 {uint32_t}
/// Seed 4-channel integer.
/// @param rgba2 {uint32_t}
/// Seed 4-channel integer.
/// @param iRGB {R | G | B}
/// Channel Name
/// @tparam pfOper {f | l | }
/// Decides the data type for literal floating type (1.0) on calculation.
/// @return {uint8_t}
/// Blended channel value
/// @see @ref ae2f_Bmp_Dot_Blend_imp
/// @see @ref ae2f_Bmp_Dot_RGBA_GetR
/// @see @ref ae2f_Bmp_Dot_RGBA_GetG
/// @see @ref ae2f_Bmp_Dot_RGBA_GetB
/// @see @ref ae2f_Bmp_Dot_RGBA_GetA
#define ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, iRGB, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba1), ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba2), ae2f_Bmp_Dot_RGBA_GetA(rgba1) / (ae2f_static_cast(ae2f_Bmp_Dot_Blender_t##pfOper, ae2f_Bmp_Dot_RGBA_GetA(rgba1)) + ae2f_Bmp_Dot_RGBA_GetA(rgba2)), uchar, pfOper)
#define ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgb, rgba, iRGB, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_Get##iRGB(rgba), ae2f_Bmp_Dot_RGBA_Get##iRGB(rgb), ae2f_Bmp_Dot_RGBA_GetA(rgba) / 255.0##pfOper, uchar, pfOper)

/// @brief
#define ae2f_Bmp_Dot_rRGBA_BlendA(rgba1, rgba2, pfOper) ae2f_Bmp_Dot_Blend_imp(ae2f_Bmp_Dot_RGBA_GetA(rgba1), ae2f_Bmp_Dot_RGBA_GetB(rgba2), 0.5##pfOper, ae2f_Bmp_Dot_Blender_t##pfOper, pfOper)

#define ae2f_Bmp_Dot_rRGBA_BlendRGB(rgb, rgba, pfOper) ae2f_Bmp_Dot_RGB_Make(ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, R, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, G, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mpRGB(rgba, rgba, B, pfOper))
#define ae2f_Bmp_Dot_rRGBA_BlendRGBA(rgba1, rgba2, pfOper) ae2f_Bmp_Dot_RGBA_Make(ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, R, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, G, pfOper), ae2f_Bmp_Dot_rRGBA_Blend_mRGB(rgba1, rgba2, B, pfOper), ae2f_Bmp_Dot_rRGBA_BlendA(rgba1, rgba2, pfOper))

#endif