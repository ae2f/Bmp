#include <ae2f/Bmp/Src.h>
#include <ae2f/Cmp.h>
#include <ae2f/Bmp/Dot.h>
#include <ae2f/BitVec.h>
#include <ae2f/Bmp/Head.h>
#include <ae2f/Call.h>


#ifndef ae2f_cBmpSrcRef
ae2f_SHAREDEXPORT ae2f_err_t ae2f_cBmpSrcRef(
	ae2f_struct ae2f_cBmpSrc* dest,
	uint8_t* byte,
	size_t byteLength
) {
	if (byteLength < sizeof(struct ae2f_rBmpHeadBF) + sizeof(struct ae2f_rBmpHeadBI)) 
		return ae2f_errBmpSrcRef_ARR_TOO_SHORT;

	dest->ElSize = ((struct ae2f_rBmpHead*)byte)->rBI.biBitCount;
	dest->rIdxer.Width = dest->rIdxer.IdxXJump = ((struct ae2f_rBmpHead*)byte)->rBI.biWidth;
	dest->rIdxer.CurrX = 0;
	dest->rIdxer.Count = ((struct ae2f_rBmpHead*)byte)->rBI.biWidth * ((struct ae2f_rBmpHead*)byte)->rBI.biHeight;

	dest->Addr = byte + sizeof(struct ae2f_rBmpHeadBF) + sizeof(struct ae2f_rBmpHeadBI);
	return ae2f_errGlob_OK;
}
#endif
ae2f_SHAREDEXPORT ae2f_err_t ae2f_cBmpSrcFill(
	ae2f_struct ae2f_cBmpSrc* dest,
	uint32_t colour
) {
	if(!(dest && dest->Addr))
	return ae2f_errGlob_PTR_IS_NULL;

	switch (dest->ElSize) {
	case ae2f_eBmpBitCount_RGB:
	case ae2f_eBmpBitCount_RGBA: break;
	default: return ae2f_errGlob_IMP_NOT_FOUND;
	}

	for(size_t i = 0; i < ae2f_BmpIdxW(dest->rIdxer); i++)	
	for(size_t j = 0; j < ae2f_BmpIdxH(dest->rIdxer); j++)
	for(uint8_t c = 0; c < dest->ElSize; c+=8)
	dest->Addr[(ae2f_BmpIdxDrive(dest->rIdxer, i, j)) * (dest->ElSize >> 3) + (c >> 3)] = ae2f_BitVecGetRanged(colour, c, c+8);

	return ae2f_errGlob_OK;
}

ae2f_SHAREDEXPORT ae2f_err_t ae2f_cBmpSrcFillPartial(
	ae2f_struct ae2f_cBmpSrc* dest,
	uint32_t colour,

	uint32_t partial_min_x,
	uint32_t partial_min_y,
	uint32_t partial_max_x,
	uint32_t partial_max_y
) {
	if(!(dest && dest->Addr))
	return ae2f_errGlob_PTR_IS_NULL;

	switch (dest->ElSize) {
	case ae2f_eBmpBitCount_RGB:
	case ae2f_eBmpBitCount_RGBA: break;
	default: return ae2f_errGlob_IMP_NOT_FOUND;
	}

	uint32_t width = ae2f_BmpIdxW(dest->rIdxer), height = ae2f_BmpIdxH(dest->rIdxer);

	for(size_t i = partial_min_x; i < width && i < partial_max_x; i++)	
	for(size_t j = partial_min_y; j < height && j < partial_max_y; j++)
	for(uint8_t c = 0; c < dest->ElSize; c+=8)
		dest->Addr[(ae2f_BmpIdxDrive(dest->rIdxer, i, j)) * (dest->ElSize >> 3) + (c >> 3)] = ae2f_BitVecGetRanged(colour, c, c+8);

	return ae2f_errGlob_OK;
}
