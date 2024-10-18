#include <ae2f/Bmp/Src.h>
#include <ae2f/Macro/Compare.h>
#include <ae2f/Bmp/Dot.h>
#include <ae2f/Macro/BitVector.h>
#include <ae2f/Bmp/Head.h>
#include <ae2f/Macro/Call.h>

#include <stdio.h>

typedef ae2f_Bmp_cSrc_Copy_ColourIdx(1) ae2f_Bmp_cSrc_BuildPrm_ColourIdx_LeastSuggested_t;

#define SOMETHING_SMALL 1

ae2f_extern ae2f_SHAREDCALL ae2f_errint_t ae2f_Bmp_cSrc_gDot(
	const ae2f_struct ae2f_Bmp_cSrc* src,
	uint32_t* retColour,
	double _min_x,
	double _min_y,
	double _max_x,
	double _max_y
) {
	retColour[0] = ae2f_Bmp_Dot_RGB_Make(_min_x, _min_y, _max_x);

	return ae2f_errGlobal_OK;
}

ae2f_SHAREDEXPORT ae2f_errint_t ae2f_Bmp_cSrc_Read(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	uint8_t* byte,
	size_t byteLength
) {
	if (byteLength < sizeof(struct ae2f_Bmp_Head_rBF) + sizeof(struct ae2f_Bmp_Head_rBI)) 
		return ae2f_Bmp_cSrc_Read_BYTEARR_TOO_SHORT;

	dest->ElSize = ((struct ae2f_Bmp_rHead*)byte)->rBI.biBitCount;
	dest->rIdxer.Width = dest->rIdxer.IdxXJump = ((struct ae2f_Bmp_rHead*)byte)->rBI.biWidth;
	dest->rIdxer.CurrX = 0;
	dest->rIdxer.Count = ((struct ae2f_Bmp_rHead*)byte)->rBI.biWidth * ((struct ae2f_Bmp_rHead*)byte)->rBI.biHeight;

	dest->Addr = byte + sizeof(struct ae2f_Bmp_Head_rBF) + sizeof(struct ae2f_Bmp_Head_rBI);
	return ae2f_errGlobal_OK;
}

ae2f_SHAREDEXPORT ae2f_errint_t ae2f_Bmp_cSrc_Fill(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	uint32_t colour
) {
	if(!(dest && dest->Addr))
	return ae2f_errGlobal_PTR_IS_NULL;

	switch (dest->ElSize) {
	case ae2f_Bmp_Idxer_eBC_RGB:
	case ae2f_Bmp_Idxer_eBC_RGBA: break;
	default: return ae2f_errGlobal_IMP_NOT_FOUND;
	}

	for(size_t i = 0; i < ae2f_Bmp_Idx_XLeft(dest->rIdxer); i++)	
	for(size_t j = 0; j < ae2f_Bmp_Idx_YLeft(dest->rIdxer); j++)
	for(uint8_t c = 0; c < dest->ElSize; c+=8)
	dest->Addr[(ae2f_Bmp_Idx_Drive(dest->rIdxer, i, j)) * (dest->ElSize >> 3) + (c >> 3)] = ae2f_Macro_BitVector_GetRanged(colour, c, c+8);

	return ae2f_errGlobal_OK;
}

ae2f_SHAREDEXPORT ae2f_errint_t ae2f_Bmp_cSrc_Copy(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	const ae2f_struct ae2f_Bmp_cSrc* src,
	const struct ae2f_Bmp_cSrc_Copy_Global* _srcprm
) {
#define srcprm ae2f_static_cast(const ae2f_Bmp_cSrc_BuildPrm_ColourIdx_LeastSuggested_t*, _srcprm)
	ae2f_errint_t code;

	if (!(src && dest && srcprm && src->Addr && dest->Addr)) {
		return ae2f_errGlobal_PTR_IS_NULL;
	}

	// check if all alpha is zero
	if (!srcprm->global.Alpha && src->ElSize != ae2f_Bmp_Idxer_eBC_RGBA)
		return ae2f_errGlobal_OK;

	switch (dest->ElSize) {
	case ae2f_Bmp_Idxer_eBC_RGB:
	case ae2f_Bmp_Idxer_eBC_RGBA: break;
	default: return ae2f_errGlobal_IMP_NOT_FOUND;
	}

	
	double 
		dotw = (ae2f_Bmp_Idx_XLeft(src->rIdxer) / (double)srcprm->global.WidthAsResized), 
		doth = (ae2f_Bmp_Idx_YLeft(src->rIdxer) / (double)srcprm->global.HeightAsResized);

	for (uint32_t y = 0; y < srcprm->global.HeightAsResized; y++)
		for (uint32_t x = 0; x < srcprm->global.WidthAsResized; x++)
		{
			union {
				uint32_t a;
				uint8_t b[4];
			} el;

			if(src->ElSize == ae2f_Bmp_Idxer_eBC_RGB) {
				el.b[3] = srcprm->global.Alpha;
			}

			code = ae2f_Bmp_cSrc_gDot(src, &el.a, dotw * x, doth * y, dotw * (x + 1), doth * (y+1));
			if(code != ae2f_errGlobal_OK) {
				return code;
			}

			for (
				uint8_t* 
				addr = dest->Addr + (dest->ElSize >> 3) * ae2f_Bmp_Idx_Drive(dest->rIdxer, x + srcprm->global.AddrXForDest, y + srcprm->global.AddrYForDest), 
				i = 0; 
				
				i < (src->ElSize >> 3); 
				
				i++
				
				) {
				uint8_t addr_a = src->ElSize == ae2f_Bmp_Idxer_eBC_RGB ? 255 : addr[3];
				
				switch (i) {
				default: {
					addr[i] = ae2f_Bmp_Dot_Blend_imp(
						el.b[i], 
						addr[i], 
						((ae2f_static_cast(double, el.b[3])) / ae2f_static_cast(double, addr_a + el.b[3])), 
						uint8_t, 
					);
				} break;
				case 3: {
					addr[i] = (ae2f_static_cast(uint16_t, addr[i]) + el.b[i]) >> 1;
				}
				}
			}
		}
	return ae2f_errGlobal_OK;
}

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
ae2f_SHAREDEXPORT ae2f_errint_t ae2f_Bmp_cSrc_Copy_Partial(
	ae2f_struct ae2f_Bmp_cSrc* dest,
	const ae2f_struct ae2f_Bmp_cSrc* src,
	const ae2f_struct ae2f_Bmp_cSrc_Copy_Global* _srcprm,
	uint32_t partial_min_x,
	uint32_t partial_min_y,
	uint32_t partial_max_x,
	uint32_t partial_max_y
) {
		if (!(src && dest && srcprm && src->Addr && dest->Addr)) {
		return ae2f_errGlobal_PTR_IS_NULL;
	}

	// check if all alpha is zero
	if (!srcprm->global.Alpha && src->ElSize != ae2f_Bmp_Idxer_eBC_RGBA)
		return ae2f_errGlobal_OK;

	switch (dest->ElSize) {
	case ae2f_Bmp_Idxer_eBC_RGB:
	case ae2f_Bmp_Idxer_eBC_RGBA: break;
	default: return ae2f_errGlobal_IMP_NOT_FOUND;
	}

	uint32_t
		dotW = ae2f_Bmp_Idx_XLeft(src->rIdxer) / srcprm->global.WidthAsResized,
		dotH = ae2f_Bmp_Idx_YLeft(src->rIdxer) / srcprm->global.HeightAsResized;

	dotW || (dotW++);
	dotH || (dotH++);

	for (uint32_t y = partial_min_y; y < partial_max_y && y < srcprm->global.HeightAsResized; y++) 
		for (uint32_t x = partial_min_x; x < partial_max_x && x < srcprm->global.WidthAsResized; x++)
		{
			// is it able to be pasted in this dir
			if (
				(ae2f_Bmp_Idx_Drive(dest->rIdxer, x + srcprm->global.AddrXForDest, y + srcprm->global.AddrYForDest))
				== 
				ae2f_static_cast(uint32_t, -1)
				) break;

			uint64_t
				tmpColour_Count = 0,
				tmpColour[4] = { 0, 0, 0, src->ElSize == ae2f_Bmp_Idxer_eBC_RGBA ? 0 : srcprm->global.Alpha };

#define tmpColour_R tmpColour[0]
#define tmpColour_G tmpColour[1]
#define tmpColour_B tmpColour[2]
#define tmpColour_A tmpColour[3]

			for (uint32_t doty = 0; doty < dotH; doty++) 
				for(uint32_t dotx = 0; dotx < dotW; dotx++) {
					// index for source as count
					uint64_t srcDir = ae2f_Bmp_Idx_Drive(src->rIdxer, x * dotW + dotx, y * dotH + doty);

					if (srcDir == -1) break;
					switch (src->ElSize) {
					case ae2f_Bmp_Idxer_eBC_RGBA:
					case ae2f_Bmp_Idxer_eBC_RGB: {
						uint32_t
							_tmpColour_R = (src->Addr + (srcDir * (src->ElSize >> 3)))[0],
							_tmpColour_G = (src->Addr + (srcDir * (src->ElSize >> 3)))[1],
							_tmpColour_B = (src->Addr + (srcDir * (src->ElSize >> 3)))[2];

						if (
							ae2f_Bmp_Dot_RGB_Make(_tmpColour_R, _tmpColour_G, _tmpColour_B) == srcprm->global.DataToIgnore
							&& src->ElSize == ae2f_Bmp_Idxer_eBC_RGB
							) { break; }

						switch (src->ElSize) {
						case ae2f_Bmp_Idxer_eBC_RGBA:
							_tmpColour_R *= (src->Addr + (srcDir * (src->ElSize >> 3)))[3];
							_tmpColour_G *= (src->Addr + (srcDir * (src->ElSize >> 3)))[3];
							_tmpColour_B *= (src->Addr + (srcDir * (src->ElSize >> 3)))[3];
							tmpColour_A += (src->Addr + (srcDir * (src->ElSize >> 3)))[3] * (src->Addr + (srcDir * (src->ElSize >> 3)))[3];
						case ae2f_Bmp_Idxer_eBC_RGB:
							tmpColour_R += _tmpColour_R;
							tmpColour_G += _tmpColour_G;
							tmpColour_B += _tmpColour_B;
							break;
						}

						tmpColour_Count += src->ElSize == ae2f_Bmp_Idxer_eBC_RGBA ? (src->Addr + (srcDir * (src->ElSize >> 3)))[3] : 1;
					} break;

					default: { // 1 4 8
						uint8_t ColourIdx 
							= ae2f_Macro_BitVector_GetRanged(
								(src->Addr + ((srcDir * src->ElSize) >> 3))[0],
								(srcDir * src->ElSize) & 7,
								((srcDir * src->ElSize) & 7) + src->ElSize
							);

						uint32_t ColourTmp = srcprm->ColourIdx[ColourIdx];

						if (ColourTmp == srcprm->global.DataToIgnore) {
							tmpColour_Count++;
							break;
						}

						tmpColour_R += ae2f_Bmp_Dot_RGBA_GetR(ColourTmp);
						tmpColour_G += ae2f_Bmp_Dot_RGBA_GetG(ColourTmp);
						tmpColour_B += ae2f_Bmp_Dot_RGBA_GetB(ColourTmp);
						tmpColour_Count++;
					} break;
					}
				}

			if(!tmpColour_Count) continue;
			tmpColour_R /= tmpColour_Count;
			tmpColour_G /= tmpColour_Count;
			tmpColour_B /= tmpColour_Count;

			(src->ElSize == ae2f_Bmp_Idxer_eBC_RGBA) && (tmpColour_A /= tmpColour_Count);

			for (
				uint8_t* 
				addr = dest->Addr + (dest->ElSize >> 3) * ae2f_Bmp_Idx_Drive(dest->rIdxer, x + srcprm->global.AddrXForDest, y + srcprm->global.AddrYForDest), 
				i = 0; 
				
				i < (src->ElSize >> 3); 
				
				i++
				
				) {
				uint8_t addr_a = src->ElSize == ae2f_Bmp_Idxer_eBC_RGB ? 255 : addr[3];
				
				switch (i) {
				default: {

					addr[i] = ae2f_Bmp_Dot_Blend_imp(
						tmpColour[i], 
						addr[i], 
						((ae2f_static_cast(double, tmpColour_A)) / ae2f_static_cast(double, addr_a + tmpColour_A)), 
						uint8_t, 
					);
				} break;
				case 3: {
					addr[i] = (ae2f_static_cast(uint16_t, addr[i]) + tmpColour[i]) >> 1;
				}
				}
			}
#undef Done
#undef addr_tar
		}
	return ae2f_errGlobal_OK;
}