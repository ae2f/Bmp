#include <ae2f/Bmp/Dot.h>
#include <ae2f/Bmp/Head.h>
#include <ae2f/Bmp/Idx.h>
#include <ae2f/Bmp/Src.h>

#include <ae2f/Bmp/Src.h>
#include <ae2f/Bmp/Src/Rect.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_VAL(buff, ...) if((buff) = (__VA_ARGS__)) return (buff);
#define TEST(fun, buff) if((buff) = ((fun)())) return (buff);
int test0x0();
int test0x1();
int test0x2();
int test0x3();

// copy test: same size, same elsize [32 bit, rgba]
int test0x0() {
    struct ae2f_cBmpSrc a, b;
    struct ae2f_cBmpSrcRectCpyPrm Parameter;

    int ax = 10, ay = 9, code = 0;

#pragma region 'a' init
    a.rIdxer.Count = ax * ay,
    a.rIdxer.CurrX = 0,
    a.rIdxer.IdxXJump = ax,
    a.rIdxer.Width = ax;

    a.ElSize = 32;
    if(!(a.Addr = (uint8_t *)calloc(ax * ay, 4)))
    return ae2f_errGlob_ALLOC_FAILED;

#pragma endregion

#pragma region 'b' init
    b.rIdxer.Count = ax * ay,
    b.rIdxer.CurrX = 0,
    b.rIdxer.IdxXJump = ax,
    b.rIdxer.Width = ax;
    b.ElSize = 32;
    if(!(b.Addr = (uint8_t*)calloc(ax * ay, 4)))
    goto __KILL_A;

#pragma endregion

#pragma region 'a' val init & print
    ae2f_cBmpSrcFill(&a, 0xFFFFFFFF);

    printf("Bmp A\n");
    for(int i = 0; i < ax; i++) {
        for(int j = 0; j < ay; j++) {
            // ((uint32_t*)a.Addr)[ae2f_BmpIdxDrive(a.rIdxer, i, j)] = 0xFFFFFFFF;
            printf("%d ", ((uint32_t*)a.Addr)[ae2f_BmpIdxDrive(a.rIdxer, i, j)]);
        }

        printf("\n");
    }
#pragma endregion

#pragma region 'b' val print
    printf("Bmp B\n");
    for(int i = 0; i < ax; i++) {
        for(int j = 0; j < ay; j++) {
            // ((uint32_t*)b.Addr)[ae2f_BmpIdxDrive(b.rIdxer, i, j)] = 0xFFFFFFFF;
            printf("%d ", ((uint32_t*)b.Addr)[ae2f_BmpIdxDrive(b.rIdxer, i, j)]);
        }
        printf("\n");
    }
#pragma endregion

#pragma region Source Parameter Build
    Parameter.AddrDest = {
                .x = 0,
                .y = 0
            };

    Parameter.Resz = {
        .x = (unsigned int)ax,
        .y = (unsigned int)ay
    };

    Parameter.Alpha = 0,
    Parameter.DataToIgnore = 0;
#pragma endregion

#pragma region copying 'a' to 'b'
    if((code = ae2f_cBmpSrcRectCpy(&b, &a, &Parameter)) != ae2f_errGlob_OK) {
        goto __KILL_ALL;
    }
#pragma endregion

#pragma region 'a' cmp 'b'
    for(int i = 0; i < ax; i++) {
        for(int j = 0; j < ay; j++) {
            if(((uint32_t*)b.Addr)[ae2f_BmpIdxDrive(b.rIdxer, i, j)] != 0xFFFFFFFF) {
                code = ae2f_errGlob_WRONG_OPERATION;
                goto __KILL_ALL;
            }
        }
    }
#pragma endregion

#pragma region Freeing Memory


__KILL_ALL:
    free(b.Addr);

__KILL_A:
    free(a.Addr);
    return code;
#pragma endregion
}

// copy test: Partial, same elsize [32 bits, rgba]
int test0x1() {
    struct ae2f_cBmpSrc a, b;
    int ax = 10, ay = 9, code = 0;
    struct ae2f_cBmpSrcRectCpyPrm Parameter;

    Parameter.AddrDest.x = 0;
    Parameter.AddrDest.y = 0;
    Parameter.Alpha = 0;
    Parameter.DataToIgnore = 0;
    Parameter.Resz.x = 0;
    Parameter.Resz.y = 0;

#pragma region 'a' init
    a.rIdxer.Count = ax * ay,
    a.rIdxer.CurrX = 0,
    a.rIdxer.IdxXJump = ax,
    a.rIdxer.Width = ax;
    a.ElSize = 32;
    if(!(a.Addr = (uint8_t*)calloc(ax * ay, 4)))
    return ae2f_errGlob_ALLOC_FAILED;

#pragma endregion

#pragma region 'b' init
    b.rIdxer.Count = ax * ay,
    b.rIdxer.CurrX = 0,
    b.rIdxer.IdxXJump = ax,
    b.rIdxer.Width = ax;
    b.ElSize = 32;
    if(!(b.Addr = (uint8_t*)calloc(ax * ay, 4)))
    goto __KILL_A;

#pragma endregion

#pragma region 'a' val init & print
    printf("Bmp A\n");
    for(int i = 0; i < ax; i++) {
        for(int j = 0; j < ay; j++) {
            ((uint32_t*)a.Addr)[ae2f_BmpIdxDrive(a.rIdxer, i, j)] = 0xFFFFFFFF;
            printf("%d ", ((uint32_t*)a.Addr)[ae2f_BmpIdxDrive(a.rIdxer, i, j)]);
        }

        printf("\n");
    }
#pragma endregion

#pragma region 'b' val print
    printf("Bmp B\n");
    for(int i = 0; i < ax; i++) {
        for(int j = 0; j < ay; j++) {
            printf("%d ", ((uint32_t*)b.Addr)[ae2f_BmpIdxDrive(b.rIdxer, i, j)]);
        }
        printf("\n");
    }
#pragma endregion

#pragma region copying 'a' to 'b'
    if((code = ae2f_cBmpSrcRectCpyPartial(&b, &a, &Parameter, 3, 4, 6, 5)) != ae2f_errGlob_OK) {
        goto __KILL_ALL;
    }
#pragma endregion

#pragma region 'a' cmp 'b'
    for(int i = 0; i < ax; i++) {
        for(int j = 0; j < ay; j++) {
            uint32_t cond[2] = {0, 0xFFFFFFFF};

            if((
                (uint32_t*)b.Addr)[ae2f_BmpIdxDrive(b.rIdxer, i, j)] != 
                cond[i < 6 && i >= 3 && j >= 4 && j < 5]
            ) {
                code = ae2f_errGlob_WRONG_OPERATION;
                goto __KILL_ALL;
            }
        }
    }
#pragma endregion

#pragma region Freeing Memory


__KILL_ALL:
    free(b.Addr);

__KILL_A:
    free(a.Addr);
    return code;
#pragma endregion
}

// copy test: Partial, same elsize [24 bits, rgb]
int test0x2() {

    struct ae2f_cBmpSrc a, b;

    int ax = 10, ay = 9, code = 0;
#pragma region Source Parameter Build
    struct ae2f_cBmpSrcRectCpyPrm Parameter;

    Parameter.AddrDest.x = 0;
    Parameter.AddrDest.y = 0;
    Parameter.Alpha = 0;
    Parameter.DataToIgnore = 0;
    Parameter.Resz.x = 0;
    Parameter.Resz.y = 0;
#pragma endregion

#pragma region 'a' init
    a.rIdxer.Count = ax * ay,
    a.rIdxer.CurrX = 0,
    a.rIdxer.IdxXJump = ax,
    a.rIdxer.Width = ax;

    a.ElSize = 24;
    if(!(a.Addr = (uint8_t*)calloc(ax * ay, 3)))
    return ae2f_errGlob_ALLOC_FAILED;

#pragma endregion

#pragma region 'b' init
    b.rIdxer.Count = ax * ay,
    b.rIdxer.CurrX = 0,
    b.rIdxer.IdxXJump = ax,
    b.rIdxer.Width = ax;
    b.ElSize = 24;
    if(!(b.Addr = (uint8_t*)calloc(ax * ay, 3)))
    goto __KILL_A;

#pragma endregion

#if 1
#pragma region 'a' val init & print
    if(ae2f_cBmpSrcFill(&a, 0xFFFFFF) != ae2f_errGlob_OK)
    goto __KILL_ALL;
#pragma endregion

#pragma region 'b' val print
    if(ae2f_cBmpSrcFill(&b, 0) != ae2f_errGlob_OK)
    goto __KILL_ALL;
#pragma endregion
#endif

#pragma region copying 'a' to 'b'
    if((code = ae2f_cBmpSrcRectCpy(&b, &a, &Parameter)) != ae2f_errGlob_OK) {
        goto __KILL_ALL;
    }
#pragma endregion

#pragma region 'a' cmp 'b'
    for(int i = 0; i < ax; i++) {
        for(int j = 0; j < ay; j++) {
            if(ae2f_BmpIdxDrive(b.rIdxer, i, j) != -1) {
                printf("\n%d %d %d\n",
                    b.Addr[ae2f_BmpIdxDrive(b.rIdxer, i, j) * 3 + 0],
                    b.Addr[ae2f_BmpIdxDrive(b.rIdxer, i, j) * 3 + 1],
                    b.Addr[ae2f_BmpIdxDrive(b.rIdxer, i, j) * 3 + 2]
                );
            }
        }
    }
#pragma endregion

#pragma region Freeing Memory


__KILL_ALL:
    free(b.Addr);

__KILL_A:
    free(a.Addr);
    return code;
#pragma endregion
}

// copy test: Partial, same elsize, non-same width/height [24 bits, rgb]
int test0x3() {
    struct ae2f_cBmpSrc a, b;

    int ax = 10, ay = 9, code = 0,
        bx = 1920, by = 1080;

#pragma region Source Parameter Build
    struct ae2f_cBmpSrcRectCpyPrm Parameter;
    
    Parameter.AddrDest.x = 0;
    Parameter.AddrDest.y = 0;
    Parameter.Alpha = 0;
    Parameter.DataToIgnore = 0;
    Parameter.Resz.x = 0;
    Parameter.Resz.y = 0;
#pragma endregion

#pragma region 'a' init
    a.rIdxer.Count = ax * ay,
    a.rIdxer.CurrX = 0,
    a.rIdxer.IdxXJump = ax,
    a.rIdxer.Width = ax,
    a.ElSize = 24;
    if(!(a.Addr = (uint8_t*)calloc(ax * ay, 3)))
    return ae2f_errGlob_ALLOC_FAILED;

#pragma endregion

#pragma region 'b' init
    b.rIdxer.Count = bx * by,
    b.rIdxer.CurrX = 0,
    b.rIdxer.IdxXJump = bx,
    b.rIdxer.Width = bx,
    b.ElSize = 24;
    if(!(b.Addr = (uint8_t*)calloc(bx * by, 3)))
    goto __KILL_A;

#pragma endregion

#if 1
#pragma region 'a' val init & print
    if(ae2f_cBmpSrcFill(&a, 0xFFFFFF) != ae2f_errGlob_OK)
    goto __KILL_ALL;
#pragma endregion

#pragma region 'b' val print
    if(ae2f_cBmpSrcFill(&b, 0) != ae2f_errGlob_OK)
    goto __KILL_ALL;
#pragma endregion
#endif

#pragma region copying 'a' to 'b'
    if((code = ae2f_cBmpSrcRectCpy(&b, &a, &Parameter)) != ae2f_errGlob_OK) {
        goto __KILL_ALL;
    }
#pragma endregion

#pragma region 'a' cmp 'b'
    for(int i = 0; i < bx; i++) {
        for(int j = 0; j < by; j++) {
            if(ae2f_BmpIdxDrive(b.rIdxer, i, j) != -1) {
                printf("\n%d %d %d\n",
                    b.Addr[ae2f_BmpIdxDrive(b.rIdxer, i, j) * 3 + 0],
                    b.Addr[ae2f_BmpIdxDrive(b.rIdxer, i, j) * 3 + 1],
                    b.Addr[ae2f_BmpIdxDrive(b.rIdxer, i, j) * 3 + 2]
                );
            }
        }
    }
#pragma endregion

#pragma region Freeing Memory


__KILL_ALL:
    free(b.Addr);

__KILL_A:
    free(a.Addr);
    return code;
#pragma endregion
}


#include <ae2f/Bmp/Head.h>
int main() {
    int code;

    if(sizeof(ae2f_struct ae2f_rBmpHead) != 54)
    return 1;
    
    // TEST(test0x0, code);
    // TEST(test0x1, code);
    TEST(test0x2, code);
    TEST(test0x3, code);

    return 0;
}