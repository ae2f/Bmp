#include <ae2f/Bmp/CL.h>

#if _ae2f_Bmp_Use_OpenCL 

ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_CL_Init() {
    return ae2f_errGlob_IMP_NOT_FOUND;
}
ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_CL_Release() {
    return ae2f_errGlob_IMP_NOT_FOUND;
}
#endif