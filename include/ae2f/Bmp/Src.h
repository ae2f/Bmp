#if !defined(ae2f_Bmp_Src_h)
#define ae2f_Bmp_Src_h

#include "Idxer.h"

// Pre-made parameter for 
struct ae2f_Bmp_cSrc_Copy_Global {
	const uint8_t Alpha;
	const uint32_t NWidth, NHeight, NX, NY, DataToIgnore;
};

#define ae2f_Bmp_cSrc_Copy_ColourIdx(len) struct { ae2f_struct ae2f_Bmp_cSrc_Copy_Global global; uint32_t ColourIdx[len]; }

struct ae2f_Bmp_cSrc {
	ae2f_struct ae2f_Bmp_rIdxer rIdxer;

	// size of each element as bit
	ae2f_Bmp_Idxer_eBC_t ElSize;
	uint8_t* Addr;
};

ae2f_extern ae2f_errint_t ae2f_Bmp_cSrc_Copy(
	ae2f_struct ae2f_Bmp_cSrc* dest, 
	const ae2f_struct ae2f_Bmp_cSrc* src,
	const ae2f_struct ae2f_Bmp_cSrc_Copy_Global* srcprm
);

#endif // !defined(ae2f_Bmp_Src_h)

#if defined(__cplusplus) && !defined(ae2f_Bmp_Src_hpp)
#define ae2f_Bmp_Src_hpp

#include <ae2f/DataStructure/Allocator.h>

namespace ae2f {
	namespace Bmp {
		namespace BuildPrm {
			using Global = ae2f_Bmp_cSrc_Copy_Global;

			struct Indexed : private DataStructure::Allocator::cOwner {
				inline Indexed(uint8_t len, ae2f_errint_t* err = 0) noexcept 
					: cOwner(
						len + sizeof(Global), 
						&ae2f_ds_Alloc_vOwner_cLinear, 
						&ae2f_ds_Alloc_vRefer_cLinear, 
						err
					) {}

				constexpr Global* GlobalBuff() noexcept {  
					return this->data ? static_cast<Global*>(static_cast<void*>(this->data + sizeof(size_t))) : 0;
				}

				constexpr const Global* GlobalBuff() const noexcept {
					return this->data ? static_cast<const Global*>(static_cast<const void*>(this->data + sizeof(size_t))) : 0;
				}

				constexpr uint8_t len() const noexcept {
					return this->data ? static_cast<const uint8_t*>(static_cast<const void*>(this->data))[0] : 0;
				}
			};
		};

		struct cSrc : public ae2f_Bmp_cSrc {
			inline ae2f_errint_t Copy(
				const cSrc& src,
				const BuildPrm::Global& srcPrm
			) {
				switch (src.ElSize) {
				case ae2f_Bmp_Idxer_eBC_RGB:
				case ae2f_Bmp_Idxer_eBC_RGBA:
					break;
				default:
					return ae2f_errGlobal_WRONG_OPERATION;
				}
				return ae2f_Bmp_cSrc_Copy(this, &src, &srcPrm);
			}

			inline ae2f_errint_t Copy(
				const cSrc&& src,
				const BuildPrm::Global& srcPrm
			) {
				switch (src.ElSize) {
				case ae2f_Bmp_Idxer_eBC_RGB:
				case ae2f_Bmp_Idxer_eBC_RGBA:
					break;
				default:
					return ae2f_errGlobal_WRONG_OPERATION;
				}
				return ae2f_Bmp_cSrc_Copy(this, &src, &srcPrm);
			}

			inline ae2f_errint_t Copy(
				const cSrc& src,
				const BuildPrm::Global&& srcPrm
			) {
				switch (src.ElSize) {
				case ae2f_Bmp_Idxer_eBC_RGB:
				case ae2f_Bmp_Idxer_eBC_RGBA:
					break;
				default:
					return ae2f_errGlobal_WRONG_OPERATION;
				}
				return ae2f_Bmp_cSrc_Copy(this, &src, &srcPrm);
			}

			inline ae2f_errint_t Copy(
				const cSrc&& src,
				const BuildPrm::Global&& srcPrm
			) {
				switch (src.ElSize) {
				case ae2f_Bmp_Idxer_eBC_RGB:
				case ae2f_Bmp_Idxer_eBC_RGBA:
					break;
				default:
					return ae2f_errGlobal_WRONG_OPERATION;
				}
				return ae2f_Bmp_cSrc_Copy(this, &src, &srcPrm);
			}

			inline ae2f_errint_t Copy(
				const cSrc& src,
				const BuildPrm::Indexed& srcPrm
			) {
				if (srcPrm.len() < (1 << src.ElSize))
					return ae2f_errGlobal_WRONG_OPERATION;

				return ae2f_Bmp_cSrc_Copy(this, &src, srcPrm.GlobalBuff());
			}

			inline ae2f_errint_t Copy(
				const cSrc&& src,
				const BuildPrm::Indexed& srcPrm
			) {
				if (srcPrm.len() < (1 << src.ElSize))
					return ae2f_errGlobal_WRONG_OPERATION;

				return ae2f_Bmp_cSrc_Copy(this, &src, srcPrm.GlobalBuff());
			}
		};
	}
}

#endif // !defined(__cplusplus)
