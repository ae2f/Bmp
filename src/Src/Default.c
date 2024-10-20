#include <ae2f/Bmp/Src.h>
#include <ae2f/Macro/Compare.h>
#include <ae2f/Bmp/Dot.h>
#include <ae2f/Macro/BitVector.h>
#include <ae2f/Bmp/Head.h>
#include <ae2f/Macro/Call.h>

#include <stdio.h>

typedef ae2f_Bmp_cSrc_Copy_ColourIdx(1) ae2f_Bmp_cSrc_BuildPrm_ColourIdx_LeastSuggested_t;

ae2f_SHAREDEXPORT ae2f_errint_t ae2f_Bmp_cSrc_gDot(
	const ae2f_struct ae2f_Bmp_cSrc* src,
	uint32_t* retColour,
	double _min_x,
	double _min_y,
	double _max_x,
	double _max_y
) {
	if(!(src && retColour && src->Addr))
	return ae2f_errGlobal_PTR_IS_NULL;

	struct {
		double R, G, B, A, Count;
	} Channel = {0, 0, 0, 0, 0};

	switch(src->ElSize) {
		case ae2f_Bmp_Idxer_eBC_RGB:
		case ae2f_Bmp_Idxer_eBC_RGBA:
		break;
		default: return ae2f_errGlobal_IMP_NOT_FOUND;
	}

	if(_min_x < 0) _min_x = 0;
	if(_min_y < 0) _min_y = 0;
	if(_max_x < 0) _max_x = 0;
	if(_max_y < 0) _max_y = 0;

	if(_min_x >= ae2f_Bmp_Idx_XLeft(src->rIdxer)) 
	_min_x = ae2f_Bmp_Idx_XLeft(src->rIdxer);

	if(_max_x >= ae2f_Bmp_Idx_XLeft(src->rIdxer))
	_max_x = ae2f_Bmp_Idx_XLeft(src->rIdxer);

	if(_min_y >= ae2f_Bmp_Idx_YLeft(src->rIdxer)) 
	_min_y = ae2f_Bmp_Idx_YLeft(src->rIdxer);

	if(_max_y >= ae2f_Bmp_Idx_YLeft(src->rIdxer)) 
	_max_y = ae2f_Bmp_Idx_YLeft(src->rIdxer);

	if(_min_x >= _max_x || _min_y >= _max_y) {
		retColour = 0;
		return ae2f_errGlobal_OK;
	}

	struct {
		size_t Width, Height;
	} Size;
	struct {
		size_t minx, maxx, miny, maxy;
	} Corner; // as integer

	Corner.maxx = (size_t)_max_x;
	Corner.maxy = (size_t)_max_y;
	
	Corner.minx = (size_t)_min_x;
	Corner.miny = (size_t)_min_y;

	if(Corner.minx == Corner.maxx)
	Corner.maxx++;

	if(Corner.miny == Corner.maxy)
	Corner.maxy++;

	#pragma region Centre
	for(size_t i = Corner.minx; i < Corner.maxx; i++)
	for(size_t j = Corner.miny; j < Corner.maxy; j++) {
		const uint8_t* const __src = src->Addr + ae2f_Bmp_Idx_Drive(src->rIdxer, i, j) * (src->ElSize >> 3);

		if(__src + 1 == src->Addr) continue;

		switch(src->ElSize) {
			case ae2f_Bmp_Idxer_eBC_RGB: {
				Channel.R += __src[0];
				Channel.G += __src[1];
				Channel.B += __src[2];
				Channel.Count += 1;
			} break;

			case ae2f_Bmp_Idxer_eBC_RGBA: {
				Channel.R += __src[0] * __src[3];
				Channel.G += __src[1] * __src[3];
				Channel.B += __src[2] * __src[3];
				Channel.A += __src[3];
				Channel.Count += __src[3];
			} break;
		}
	}
	#pragma endregion

	switch(src->ElSize) {
		case ae2f_Bmp_Idxer_eBC_RGBA: {
			retColour[0] = 
			ae2f_Bmp_Dot_RGBA_Make(
				Channel.R / Channel.Count, 
				Channel.G / Channel.Count,
				Channel.B / Channel.Count,
				Channel.A / Channel.Count
			);
		} break;
		case ae2f_Bmp_Idxer_eBC_RGB: {
			retColour[0] = 
			ae2f_Bmp_Dot_RGBA_Make(
				Channel.R / Channel.Count,
				Channel.G / Channel.Count,
				Channel.B / Channel.Count,
				255
			);
		} break;
	}
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

			uint32_t _x, _y;

			switch(srcprm->global.ReverseIdx) {
				case 1: case 3:
				_x = srcprm->global.WidthAsResized - x - 1;
				if(srcprm->global.ReverseIdx == 1) goto ignore___lbl_y;

				case 2:
				_y = srcprm->global.HeightAsResized - y - 1;
				ignore___lbl_y:

				case 0:
				_x = x; _y = y;
				break;
			}

			code = ae2f_Bmp_cSrc_gDot(src, &el.a, dotw * _x, doth * _y, dotw * (_x + 1), doth * (_y+1));
			if(code != ae2f_errGlobal_OK) {
				return code;
			}

			if(el.a == srcprm->global.DataToIgnore) continue;
			
			if(src->ElSize == ae2f_Bmp_Idxer_eBC_RGB) {
				el.b[3] = srcprm->global.Alpha;
			}

			uint32_t foridx = ae2f_Bmp_Idx_Drive(dest->rIdxer, x + srcprm->global.AddrXForDest, y + srcprm->global.AddrYForDest);
			if(foridx == -1) break;

			for (
				uint8_t* 
				addr = dest->Addr + (dest->ElSize >> 3) * foridx, 
				i = 0; 
				
				i < (src->ElSize >> 3); 
				
				i++
				
				) {
				
				switch (i) {
				default: {
					addr[i] = ae2f_Bmp_Dot_Blend_imp(
						el.b[i], 
						addr[i], 
						((ae2f_static_cast(double, el.b[3])) / 255.0), 
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

	for (uint32_t y = partial_min_y; y < partial_max_y && y < srcprm->global.HeightAsResized; y++)
		for (uint32_t x = partial_min_x; x < partial_max_x && x < srcprm->global.WidthAsResized; x++)
		{
			union {
				uint32_t a;
				uint8_t b[4];
			} el;

			uint32_t _x, _y;

			switch(srcprm->global.ReverseIdx) {
				case 1: case 3:
				_x = srcprm->global.WidthAsResized - x - 1;
				if(srcprm->global.ReverseIdx == 1) goto ignore___lbl_y;

				case 2:
				_y = srcprm->global.HeightAsResized - y - 1;
				ignore___lbl_y:

				case 0:
				_x = x; _y = y;
				break;
			}

			code = ae2f_Bmp_cSrc_gDot(src, &el.a, dotw * _x, doth * _y, dotw * (_x + 1), doth * (_y+1));
			if(code != ae2f_errGlobal_OK) {
				return code;
			}

			if(el.a == srcprm->global.DataToIgnore) continue;

			if(src->ElSize == ae2f_Bmp_Idxer_eBC_RGB) {
				el.b[3] = srcprm->global.Alpha;
			}

			uint32_t foridx = ae2f_Bmp_Idx_Drive(dest->rIdxer, x + srcprm->global.AddrXForDest, y + srcprm->global.AddrYForDest);
			if(foridx == -1) break;

			for (
				uint8_t* 
				addr = dest->Addr + (dest->ElSize >> 3) * foridx, 
				i = 0; 
				
				i < (src->ElSize >> 3); 
				
				i++
				
				) {
				uint8_t addr_a = 255 - el.b[3];
				
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