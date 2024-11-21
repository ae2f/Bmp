#if !defined(ae2f_Bmp_Head_h)
#define ae2f_Bmp_Head_h

#include <stdint.h>
#include <ae2f/Cast.h>

#pragma pack(push, 1) 

/// @brief
/// Pre-defined [B]itmap [F]ile header [BF]
struct ae2f_rBmpHeadBF {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1; // unless 0 would be fucked up
    uint16_t bfReserved2; // unless 0 would be fucked up
    uint32_t bfOffBits;
};

/// @brief
/// [B]itmap [I]nfo Header [BI]
struct ae2f_rBmpHeadBI {
    /// @brief
    /// Actual size
    uint32_t biSize;

    /// @brief
    /// Unit as pixel count
    int32_t  biWidth;

    /// @brief
    /// Height as pixel count
    int32_t  biHeight;

    
    uint16_t biPlanes;        // unless 1 would be fucked up

    /// @brief
    /// The size of each elements.
    uint16_t biBitCount;      // among { 1, 4, 8, 24, 32 }
    uint32_t biCompression;
    uint32_t biSizeImage;     // unit: Byte
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};


/// @brief 
/// Bitmap header suggested.
struct ae2f_rBmpHead {
    ae2f_struct ae2f_rBmpHeadBF rBF;
    ae2f_struct ae2f_rBmpHeadBI rBI;
};


#pragma pack(pop)
#endif