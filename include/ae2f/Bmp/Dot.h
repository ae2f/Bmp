#if !defined(ae2f_Bmp_Dot_h)

#pragma region dot_h_def
#define ae2f_Bmp_Dot_h

#pragma endregion

#include <ae2f/Cast.h>
#include <ae2f/BitVec.h>
#include <ae2f/Float.h>

/// @brief 
/// 32 - byte which means has four channels of [r, g, b, a].
typedef uint32_t ae2f_BmpDotRGBA_t;

#pragma region RGBA get-set

/// @brief
/// Gets the value of channel [R]
/// @param rgb {uint32_t} 
/// 3-channel colour integer.
#define ae2f_BmpDotRGBAGetR(rgb) ae2f_static_cast(uint8_t, ae2f_BitVec_GetRanged(ae2f_static_cast(uint32_t, rgb), 0, 8))

/// @brief
/// Gets the value of channel [G]
/// @param rgb {uint32_t} 3-channel colour integer.
#define ae2f_BmpDotRGBAGetG(rgb) ae2f_static_cast(uint8_t, ae2f_BitVec_GetRanged(ae2f_static_cast(uint32_t, rgb), 8, 16))

/// @brief
/// Gets the value of channel [B]
/// @param rgb {uint32_t} 3-channel colour integer.
#define ae2f_BmpDotRGBAGetB(rgb) ae2f_static_cast(uint8_t, ae2f_BitVec_GetRanged(ae2f_static_cast(uint32_t, rgb), 16, 24))

/// @brief
/// Gets the value of channel [A]
/// @param rgba {uint32_t} 4-channel colour integer.
#define ae2f_BmpDotRGBAGetA(rgba) ae2f_static_cast(uint8_t, ae2f_BitVec_GetRanged(ae2f_static_cast(uint32_t, rgba), 24, 32))

/// @brief
/// Sets the value of channel [R]
/// @param rgb {uint32_t}
/// @param val The value to set
#define ae2f_BmpDotRGBASetR(rgb, val)  ae2f_static_cast(uint32_t, ae2f_BitVec_SetRanged(ae2f_static_cast(uint32_t, rgb), 0, 8, val))

/// @brief
/// Sets the value of channel [G]
/// @param rgb {uint32_t}
/// @param val The value to set
#define ae2f_BmpDotRGBASetG(rgb, val)  ae2f_static_cast(uint32_t, ae2f_BitVec_SetRanged(ae2f_static_cast(uint32_t, rgb), 8, 16, val))

/// @brief
/// Sets the value of channel [B]
/// @param rgb {uint32_t}
/// @param val The value to set
#define ae2f_BmpDotRGBASetB(rgb, val)  ae2f_static_cast(uint32_t, ae2f_BitVec_SetRanged(ae2f_static_cast(uint32_t, rgb), 16, 24, val))

/// @brief
/// Sets the value of channel [A]
/// @param rgba {uint32_t}
/// @param val The value to set
#define ae2f_BmpDotRGBASetA(rgba, val) ae2f_static_cast(uint32_t, ae2f_BitVec_SetRanged(ae2f_static_cast(uint32_t, rgba), 24, 32, val))

/// @brief
/// Generates a new number with three channels configured(initialised).
/// @param r 
/// Initial Value for channel [R]
/// @param g 
/// Initial Value for channel [G]
/// @param b 
/// Initial Value for channel [B]
/// @return {uint32_t} 3-channel colour integer.
#define ae2f_BmpDotRGBMk(r, g, b) ae2f_static_cast(uint32_t, ae2f_static_cast(uint8_t, r) | (ae2f_static_cast(uint16_t, g) << 8) | (ae2f_static_cast(uint32_t, b) << 16))

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
#define ae2f_BmpDotRGBAMk(r, g, b, a) ae2f_static_cast(uint32_t, ae2f_static_cast(uint8_t, r) | (ae2f_static_cast(uint16_t, g) << 8) | (ae2f_static_cast(uint32_t, b) << 16) | (ae2f_static_cast(uint32_t, a) << 24))


/// @brief
/// Generates a new number with seed of [RGB] and initialising value for channel [A].
/// @param rgb
/// Seed RGB Channels
/// @param a
/// Initial value for Channel [A]
/// @return {uint32_t}
#define ae2f_BmpDotRGBMkA(rgb, a) ae2f_BmpDotRGBASetA(rgb, a)

#pragma endregion

#endif