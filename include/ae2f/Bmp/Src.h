#if !defined(ae2f_Bmp_Src_h)
#define ae2f_Bmp_Src_h

#include "Idxer.h"
#include <ae2f/Macro/Call.h>

// Pre-made parameter for 
struct ae2f_Bmp_cSrc_Copy_Global {
	const uint8_t Alpha;
	const uint32_t 
		WidthAsResized, 
		HeightAsResized, 
		AddrXForDest, 
		AddrYForDest, 
		DataToIgnore;
};

#define ae2f_Bmp_cSrc_Copy_ColourIdx(len) struct { ae2f_struct ae2f_Bmp_cSrc_Copy_Global global; uint32_t ColourIdx[len]; }

struct ae2f_Bmp_cSrc {
	// Indexing suporter
	ae2f_struct ae2f_Bmp_rIdxer rIdxer;

	// size of each element as bit
	ae2f_Bmp_Idxer_eBC_t ElSize;
	uint8_t* Addr;
};

/// @brief 
/// Copies the data of `src` to `dest`.
/// @param dest 
/// Destination where the `src` would be copied.
/// 
/// Allocating will not be automatically done.
/// @param src 
/// Source which has the actual data.
/// @param srcprm 
/// Additional operator attribute for `src`.
ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_Copy(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	const ae2f_struct ae2f_Bmp_cSrc* src,
	const ae2f_struct ae2f_Bmp_cSrc_Copy_Global* srcprm
);

/// @brief 
/// `byte` is not long enough to parse.
#define ae2f_Bmp_cSrc_Read_BYTEARR_TOO_SHORT ae2f_errGlobal_LMT

/// @brief 
/// # After this operation `dest` will still not own the memory, but `byte` will.
/// @param dest 
/// Destination where the `byte` 
/// @param byte 
/// The data of bmp structure with header.
/// @param byteLength 
/// size of the `byte`.
/// @return 
ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_Read(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	uint8_t* byte,
	size_t byteLength
);

#define ae2f_Bmp_Src_Cut(cSrc, mX, MX, mY, MY) ae2f_record_make(ae2f_struct ae2f_Bmp_cSrc, ae2f_Bmp_Idx_Cut((cSrc).rIdxer, mX, MX, mY, MX), (cSrc).ElSize, (cSrc).Addr + ae2f_Bmp_Idx_Drive((cSrc).rIdxer, mX, mY) * (cSrc).ElSize)

#endif // !defined(ae2f_Bmp_Src_h)
