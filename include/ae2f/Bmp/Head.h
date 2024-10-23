#if !defined(ae2f_Bmp_Head_h)
#define ae2f_Bmp_Head_h

#include <stdint.h>
#include <ae2f/Macro/Cast.h>

#pragma pack(push, 1) 

// Bitmap File Header
struct ae2f_Bmp_Head_rBF {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1; // unless 0 would be fucked up
    uint16_t bfReserved2; // unless 0 would be fucked up
    uint32_t bfOffBits;
};

#pragma pack(pop)

#pragma pack(push, 1)

// Bitmap Info Header
struct ae2f_Bmp_Head_rBI {
    uint32_t biSize;
    int32_t  biWidth;         // unit: px
    int32_t  biHeight;        // unit: px
    uint16_t biPlanes;        // unless 1 would be fucked up
    uint16_t biBitCount;      // among { 1, 4, 8, 24, 32 }
    uint32_t biCompression;
    uint32_t biSizeImage;     // unit: Byte
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#pragma pack(pop)

#pragma pack(push, 1)

struct ae2f_Bmp_rHead {
    ae2f_struct ae2f_Bmp_Head_rBF rBF;
    ae2f_struct ae2f_Bmp_Head_rBI rBI;
};

#pragma pack(pop)
#endif