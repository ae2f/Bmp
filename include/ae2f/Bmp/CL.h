#if !defined(ae2f_Bmp_CL_h)
#define ae2f_Bmp_CL_h
#include "CL/config.h"
#include <ae2f/Macro/errGlob.h>

ae2f_add_when_c(static) ae2f_add_when_cxx(constexpr) const char* ae2f_Bmp_CL_src() {
    return 
    ""
    #ifdef ae2f_Bmp_Dot_h
    ae2f_Bmp_Dot_h
    #endif
    ;
}

#if _ae2f_Bmp_Use_OpenCL 

ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_CL_Init();
ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_CL_Release();

#else
/// No implementation.
#define ae2f_Bmp_CL_Init(...)  ae2f_errGlob_OK

/// No implementation.
#define ae2f_Bmp_CL_Release(...) ae2f_errGlob_OK
#endif
#endif