
#include <ae2f/Bmp/Src.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_VAL(buff, ...) if((buff) = (__VA_ARGS__)) return (buff);
#define TEST(fun, buff) if((buff) = ((fun)())) return (buff);
int test0x0();

// copy test: same size, same elsize [32 bit, rgba]
int test0x0() {
    struct ae2f_Bmp_cSrc a, b;

    int ax = 10, ay = 9, code = 0;

#pragma region 'a' init
    a.rIdxer = (struct ae2f_Bmp_rIdxer) {
        .Count = ax * ay,
        .CurrX = 0,
        .IdxXJump = ax,
        .Width = ax
    };
    a.ElSize = 32;
    if(!(a.Addr = calloc(ax * ay, 4)))
    return ae2f_errGlobal_ALLOC_FAILED;

#pragma endregion

#pragma region 'b' init
    b.rIdxer = (struct ae2f_Bmp_rIdxer) {
        .Count = ax * ay,
        .CurrX = 0,
        .IdxXJump = ax,
        .Width = ax
    };
    b.ElSize = 32;
    if(!(b.Addr = calloc(ax * ay, 4)))
    goto __KILL_A;

#pragma endregion

#pragma region 'a' val init & print
    printf("Bmp A\n");
    for(int i = 0; i < ax; i++) {
        for(int j = 0; j < ay; j++) {
            ((uint32_t*)a.Addr)[ae2f_Bmp_Idx_Drive(a.rIdxer, i, j)] = 0xFFFFFFFF;
            printf("%d ", ((uint32_t*)a.Addr)[ae2f_Bmp_Idx_Drive(a.rIdxer, i, j)]);
        }

        printf("\n");
    }
#pragma endregion

#pragma region 'b' val print
    printf("Bmp B\n");
    for(int i = 0; i < ax; i++) {
        for(int j = 0; j < ay; j++) {
            ((uint32_t*)b.Addr)[ae2f_Bmp_Idx_Drive(b.rIdxer, i, j)] = 0xFFFFFFFF;
            printf("%d ", ((uint32_t*)b.Addr)[ae2f_Bmp_Idx_Drive(b.rIdxer, i, j)]);
        }
        printf("\n");
    }
#pragma endregion

#pragma region Source Parameter Build
    struct ae2f_Bmp_cSrc_Copy_Global Parameter = {
        .AddrXForDest = 0,
        .AddrYForDest = 0,
        .Alpha = 0,
        .DataToIgnore = 0,
        .HeightAsResized = ay,
        .WidthAsResized = ax
    };
#pragma endregion

#pragma region copying 'a' to 'b'
    if((code = ae2f_Bmp_cSrc_Copy(&b, &a, &Parameter)) != ae2f_errGlobal_OK) {
        goto __KILL_ALL;
    }
#pragma endregion

#pragma region 'a' cmp 'b'
    for(int i = 0; i < ax; i++) {
        for(int j = 0; j < ay; j++) {
            if(((uint32_t*)a.Addr)[ae2f_Bmp_Idx_Drive(a.rIdxer, i, j)] != ((uint32_t*)b.Addr)[ae2f_Bmp_Idx_Drive(b.rIdxer, i, j)]) {
                code = ae2f_errGlobal_WRONG_OPERATION;
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

int main() {
    int code;

    TEST(test0x0, code);

    return 0;
}