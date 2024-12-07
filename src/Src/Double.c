#include <ae2f/Bmp/Src.h>
#include <ae2f/Cmp.h>
#include <ae2f/Bmp/Dot.h>
#include <ae2f/BitVec.h>
#include <ae2f/Bmp/Head.h>
#include <ae2f/Call.h>
#include <ae2f/Bmp/Blend.h>

#include <math.h>
#include <stdio.h>

ae2f_cBmpSrcCpyPrmDef(1);

typedef ae2f_struct ae2f_cBmpSrcCpyPrmDef_i1 ae2f_cBmpSrcCpyPrmDef_i1;

ae2f_SHAREDEXPORT ae2f_err_t ae2f_cBmpSrcGDot(
	const ae2f_struct ae2f_cBmpSrc* src,
	uint32_t* retColour,
	ae2f_float_t _min_x,
	ae2f_float_t _min_y,
	ae2f_float_t _max_x,
	ae2f_float_t _max_y,

	uint8_t reverseIdx
) {
	const uint32_t 
	xleft = ae2f_BmpIdxW(src->rIdxer), 
	yleft = ae2f_BmpIdxH(src->rIdxer);

	if(!(src && retColour && src->Addr))
	return ae2f_errGlob_PTR_IS_NULL;

	struct {
		ae2f_float_t R, G, B, A, Count;
	} Channel = {0, 0, 0, 0, 0};

	switch(src->ElSize) {
		case ae2f_eBmpBitCount_RGB:
		case ae2f_eBmpBitCount_RGBA:
		break;
		default: return ae2f_errGlob_IMP_NOT_FOUND;
	}

	if(_min_x < 0) _min_x = 0;
	if(_min_y < 0) _min_y = 0;
	if(_max_x < 0) _max_x = 0;
	if(_max_y < 0) _max_y = 0;

	if(_min_x >= xleft) 
	_min_x = xleft;

	if(_max_x >= xleft)
	_max_x = xleft;

	if(_min_y >= yleft) 
	_min_y = yleft;

	if(_max_y >= yleft) 
	_max_y = yleft;

	if(_min_x >= _max_x || _min_y >= _max_y) {
		retColour = 0;
		return ae2f_errGlob_OK;
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

	if(reverseIdx & ae2f_eBmpSrcCpyPrm_RVSE_I_X) {
		Corner.minx = xleft - Corner.minx;
		Corner.maxx = xleft - Corner.maxx;

		if(Corner.minx) Corner.minx--;
		if(Corner.maxx) Corner.maxx--;

		Corner.maxx ^= Corner.minx; 
		Corner.minx ^= Corner.maxx; 
		Corner.maxx ^= Corner.minx; 
	}

	if(reverseIdx & ae2f_eBmpSrcCpyPrm_RVSE_I_Y) {
		Corner.miny = yleft - Corner.miny;
		Corner.maxy = yleft - Corner.maxy;

		if(Corner.miny) Corner.miny--;
		if(Corner.maxy) Corner.maxy--;

		Corner.maxy ^= Corner.miny;
		Corner.miny ^= Corner.maxy;
		Corner.maxy ^= Corner.miny;
	}

	if(Corner.minx == Corner.maxx)
	Corner.maxx++;

	if(Corner.miny == Corner.maxy)
	Corner.maxy++;

	#pragma region Centre
	for(size_t i = Corner.minx; i < Corner.maxx; i++)
	for(size_t j = Corner.miny; j < Corner.maxy; j++) {
		const uint8_t* const __src = src->Addr + ae2f_BmpIdxDrive(src->rIdxer, i, j) * (src->ElSize >> 3);

		// invalid index check
		// index validation
		if(__src + 1 == src->Addr) continue;

		switch(src->ElSize) {
			case ae2f_eBmpBitCount_RGB: {
				Channel.R += __src[0];
				Channel.G += __src[1];
				Channel.B += __src[2];
				Channel.Count += 1;
			} break;

			case ae2f_eBmpBitCount_RGBA: {
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
		case ae2f_eBmpBitCount_RGBA: {
			retColour[0] = 
			ae2f_BmpDotRGBAMk(
				Channel.R / Channel.Count, 
				Channel.G / Channel.Count,
				Channel.B / Channel.Count,
				Channel.A / Channel.Count
			);
		} break;
		case ae2f_eBmpBitCount_RGB: {
			retColour[0] = 
			ae2f_BmpDotRGBAMk(
				Channel.R / Channel.Count,
				Channel.G / Channel.Count,
				Channel.B / Channel.Count,
				255
			);
		} break;
	}
	return ae2f_errGlob_OK;
}


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

#ifndef ae2f_Mov2DotDef_uint32_t
#define ae2f_Mov2DotDef_uint32_t ae2f_Mov2DotDef_uint32_t
ae2f_Mov2DotDef(uint32_t);
#endif

static ae2f_Mov2DotRotDef(uint32_t);
static ae2f_Mov2DotRotDef(ae2f_float_t);


#pragma region buffall


ae2f_SHAREDEXPORT ae2f_err_t ae2f_cBmpSrcCpy(
	ae2f_struct ae2f_cBmpSrc* dest,
	const ae2f_struct ae2f_cBmpSrc* src,
	const struct ae2f_cBmpSrcCpyPrm* _srcprm
) {
#define srcprm ae2f_static_cast(const ae2f_cBmpSrcCpyPrmDef_i1*, _srcprm)
	ae2f_err_t code;

	if (!(src && dest && srcprm && src->Addr && dest->Addr)) {
		return ae2f_errGlob_PTR_IS_NULL;
	}

	// check if all alpha is zero
	if (!srcprm->global.Alpha && src->ElSize != ae2f_eBmpBitCount_RGBA)
		return ae2f_errGlob_OK;

	switch (dest->ElSize) {
	case ae2f_eBmpBitCount_RGB:
	case ae2f_eBmpBitCount_RGBA: break;
	default: return ae2f_errGlob_IMP_NOT_FOUND;
	}

	ae2f_struct ae2f_Mov2DotDefName(ae2f_float_t) dot = {
		.x = (ae2f_BmpIdxW(src->rIdxer) / (ae2f_float_t)srcprm->global.Resz.x),
		.y = (ae2f_BmpIdxH(src->rIdxer) / (ae2f_float_t)srcprm->global.Resz.y)
	};

	for (uint32_t y = 0; y < srcprm->global.Resz.y; y++) {
		for (uint32_t x = 0; x < srcprm->global.Resz.x; x++)
		{
			union {
				uint32_t a;
				uint8_t b[4];
			} el;

			uint32_t _x, _y;
			_x = x; _y = y;

			code = ae2f_cBmpSrcGDot(
				src, &el.a, 
				dot.x * _x, 
				dot.y * _y, 
				dot.x * (_x + 1), 
				dot.y * (_y+1),
				srcprm->global.ReverseIdx
			);

			ae2f_struct ae2f_Mov2DotDefName(ae2f_float_t) 
			rotatedS = dot; // rotated: scalar

			ae2f_Mov2DotRotDefName(ae2f_float_t)
			(&rotatedS, 0, srcprm->global.RotateXYCounterClockWise);

			if(rotatedS.x < 0) rotatedS.x = -rotatedS.x;
			if(rotatedS.y < 0) rotatedS.y = -rotatedS.y; // normalisation

			if(code != ae2f_errGlob_OK) {
				return code;
			}

			if(el.a == srcprm->global.DataToIgnore) continue;
			
			if(src->ElSize == ae2f_eBmpBitCount_RGB) {
				el.b[3] = srcprm->global.Alpha;
			}


			// rotated as vector
			ae2f_struct ae2f_Mov2DotDefName(uint32_t) rotated = {
				.x = _x - srcprm->global.Axis.x,
				.y = _y - srcprm->global.Axis.y
			};

			ae2f_Mov2DotRotDefName(uint32_t)(
				&rotated, 
				&srcprm->global.Axis, 
				srcprm->global.RotateXYCounterClockWise
			);

			for(int32_t i = 0; !i || i < rotatedS.x; i++) 
			for(int32_t j = 0; !j || j < rotatedS.y; j++) {
				#pragma region single dot
				
				uint32_t foridx = 
				ae2f_BmpIdxDrive(
					dest->rIdxer, rotated.x + i + srcprm->global.AddrDest.x, rotated.y + j + srcprm->global.AddrDest.y);
				
				if(foridx == -1) goto __breakloopforx;

				int32_t k = 0;
				for (
					uint8_t* 
					addr = dest->Addr + (dest->ElSize >> 3) * foridx; 
					k < (src->ElSize >> 3); 
					k++
					
					) {
					
					switch (k) {
					default: {
						addr[k] = ae2f_BmpBlend_imp(
							el.b[k], 
							addr[k], 
							((ae2f_static_cast(ae2f_float_t, el.b[3])) / 255.0), 
							uint8_t
						);
					} break;
					case 3: {
						addr[k] = (ae2f_static_cast(uint16_t, addr[k]) + el.b[k]) >> 1;
					}
					}
				}

				#pragma endregion
			}
		}

	__breakloopforx:;
	}

	return ae2f_errGlob_OK;
}
#pragma endregion


ae2f_SHAREDEXPORT ae2f_err_t ae2f_cBmpSrcCpyPartial(
	ae2f_struct ae2f_cBmpSrc* dest,
	const ae2f_struct ae2f_cBmpSrc* src,
	const ae2f_struct ae2f_cBmpSrcCpyPrm* _srcprm,
	uint32_t partial_min_x,
	uint32_t partial_min_y,
	uint32_t partial_max_x,
	uint32_t partial_max_y
) {
	#define srcprm ae2f_static_cast(const ae2f_cBmpSrcCpyPrmDef_i1*, _srcprm)
	ae2f_err_t code;

	if (!(src && dest && srcprm && src->Addr && dest->Addr)) {
		return ae2f_errGlob_PTR_IS_NULL;
	}

	// check if all alpha is zero
	if (!srcprm->global.Alpha && src->ElSize != ae2f_eBmpBitCount_RGBA)
		return ae2f_errGlob_OK;

	switch (dest->ElSize) {
	case ae2f_eBmpBitCount_RGB:
	case ae2f_eBmpBitCount_RGBA: break;
	default: return ae2f_errGlob_IMP_NOT_FOUND;
	}

	
	ae2f_float_t 
		dotw = (ae2f_BmpIdxW(src->rIdxer) / (ae2f_float_t)srcprm->global.Resz.x), 
		doth = (ae2f_BmpIdxH(src->rIdxer) / (ae2f_float_t)srcprm->global.Resz.y);

	for (uint32_t y = partial_min_y; y < srcprm->global.Resz.y && y < partial_max_y; y++) {
		for (uint32_t x = partial_min_x; x < srcprm->global.Resz.x && x < partial_max_x; x++)
		{
			union {
				uint32_t a;
				uint8_t b[4];
			} el;

			uint32_t _x, _y;
			_x = x; _y = y;

			code = ae2f_cBmpSrcGDot(
				src, &el.a, 
				dotw * _x, 
				doth * _y, 
				dotw * (_x + 1), 
				doth * (_y+1),
				srcprm->global.ReverseIdx
			);

			ae2f_float_t 
			rotatedW = dotw * cos(srcprm->global.RotateXYCounterClockWise) + doth * sin(srcprm->global.RotateXYCounterClockWise),
			rotatedH = doth * cos(srcprm->global.RotateXYCounterClockWise) - dotw * sin(srcprm->global.RotateXYCounterClockWise);

			if(rotatedW < 0) rotatedW = -rotatedW;
			if(rotatedH < 0) rotatedH = -rotatedH;

			if(code != ae2f_errGlob_OK) {
				return code;
			}

			if(el.a == srcprm->global.DataToIgnore) continue;
			
			if(src->ElSize == ae2f_eBmpBitCount_RGB) {
				el.b[3] = srcprm->global.Alpha;
			}

			ae2f_float_t 
			_transx = (ae2f_float_t)_x - srcprm->global.Axis.x, 
			_transy = (ae2f_float_t)_y - srcprm->global.Axis.y,
			rotatedX = _transx * cos(srcprm->global.RotateXYCounterClockWise) + _transy * sin(srcprm->global.RotateXYCounterClockWise) + srcprm->global.Axis.x,
			rotatedY = _transy * cos(srcprm->global.RotateXYCounterClockWise) - _transx * sin(srcprm->global.RotateXYCounterClockWise) + srcprm->global.Axis.y;

			for(int32_t i = 0; !i || i < rotatedW; i++) 
			for(int32_t j = 0; !j || j < rotatedH; j++) {
				#pragma region single dot
				uint32_t foridx = 
				
				ae2f_BmpIdxDrive(
					dest->rIdxer, (uint32_t)rotatedX + i + srcprm->global.AddrDest.x, (uint32_t)rotatedY + j + srcprm->global.AddrDest.y);
				
				if(foridx == -1) goto __breakloopforx;

				int32_t k = 0;
				for (
					uint8_t* 
					addr = dest->Addr + (dest->ElSize >> 3) * foridx;
					k < (src->ElSize >> 3); 
					k++
					
					) {
					
					switch (k) {
					default: {
						addr[k] = ae2f_BmpBlend_imp(
							el.b[k], 
							addr[k], 
							((ae2f_static_cast(ae2f_float_t, el.b[3])) / 255.0), 
							uint8_t
						);
					} break;
					case 3: {
						addr[k] = (ae2f_static_cast(uint16_t, addr[k]) + el.b[k]) >> 1;
					}
					}
				}

				#pragma endregion
			}
		}

	__breakloopforx:;
	}
	return ae2f_errGlob_OK;
}