#ifndef ae2f_Bmp_Blend_h
#define ae2f_Bmp_Blend_h

#include "Dot.h"

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
/// @warning choose between f, l, or nothing otherwise would cause error.
/// @return {rtn_t} The blended value.
#define ae2f_BmpBlend_imp(a, b, ratio_a, rtn_t) ae2f_static_cast(rtn_t, (((a) * (ratio_a) + (b) * (ae2f_static_cast(ae2f_float_t, 1) - (ratio_a)))))

/// @brief
/// Get each channel of two, blend two based on Alpha Channel.
/// @param rgba1 {uint32_t}
/// Seed 4-channel integer.
/// @param rgba2 {uint32_t}
/// Seed 4-channel integer.
/// @param iRGB {R | G | B}
/// Channel Name
/// @return {uint8_t}
/// Blended channel value
/// @see @ref ae2f_BmpBlend_imp
/// @see @ref ae2f_BmpDotRGBAGetR
/// @see @ref ae2f_BmpDotRGBAGetG
/// @see @ref ae2f_BmpDotRGBAGetB
/// @see @ref ae2f_BmpDotRGBAGetA
#define ae2f_BmpBlendChannel44_imp(rgba1, rgba2, iRGB) ae2f_BmpBlend_imp(ae2f_BmpDotRGBAGet##iRGB(rgba1), ae2f_BmpDotRGBAGet##iRGB(rgba2), ae2f_BmpDotRGBAGetA(rgba1) / (ae2f_static_cast(ae2f_float_t, ae2f_BmpDotRGBAGetA(rgba1)) + ae2f_BmpDotRGBAGetA(rgba2)), uint8_t)

/// @brief
/// Blends the Channel
/// @param rgb {uint32_t}
/// 3-channel colour integer
/// @param rgba {uint32_t}
/// 4-channel colour integer
/// @param iRGB {R | G | B}
/// Channel Name
/// @return {uint8_t} Blended channel value
#define ae2f_BmpBlendChannel34_imp(rgb, rgba, iRGB) ae2f_BmpBlend_imp(ae2f_BmpDotRGBAGet##iRGB(rgba), ae2f_BmpDotRGBAGet##iRGB(rgb), ae2f_BmpDotRGBAGetA(rgba) / ae2f_static_cast(ae2f_float_t, 255), uint8_t)

/// @brief
/// Alpha channel blending
#define ae2f_BmpBlendA(rgba1, rgba2) ae2f_BmpBlend_imp(ae2f_BmpDotRGBAGetA(rgba1), ae2f_BmpDotRGBAGetA(rgba2), ae2f_static_cast(ae2f_float_t, 0.5))

/// @brief
/// Colour blending as three-to-four channel.
#define ae2f_BmpBlendRGB(rgb, rgba) ae2f_BmpDotRGBMk(ae2f_BmpBlendChannel34_imp(rgba, rgba, R), ae2f_BmpBlendChannel34_imp(rgba, rgba, G), ae2f_BmpBlendChannel34_imp(rgba, rgba, B))

/// @brief
/// Colour blending as four-to-four channel.
#define ae2f_BmpBlendRGBA(rgba1, rgba2) ae2f_BmpDotRGBAMk(ae2f_BmpBlendChannel44_imp(rgba1, rgba2, R), ae2f_BmpBlendChannel44_imp(rgba1, rgba2, G), ae2f_BmpBlendChannel44_imp(rgba1, rgba2, B), ae2f_BmpBlendA(rgba1, rgba2))

#endif 