#ifndef __ASM_UNICORE64_DMA_MAPPING_H__
#define __ASM_UNICORE64_DMA_MAPPING_H__

extern struct dma_map_ops swiotlb_dma_map_ops;

#define get_dma_ops(dev)		(&swiotlb_dma_map_ops)

#define dma_supported(d, m)			\
		get_dma_ops(dev)->dma_supported((d), (m))
#define dma_alloc_coherent(d, s, h, f)		\
		get_dma_ops(dev)->alloc_coherent((d), (s), (h), (f))
#define dma_free_coherent(d, s, a, h)		\
		get_dma_ops(dev)->free_coherent((d), (s), (a), (h))

#define dma_alloc_noncoherent(d, s, h, f)	\
		dma_alloc_coherent((d), (s), (h), (f))
#define dma_free_noncoherent(d, s, a, h)	\
		dma_free_coherent((d), (s), (a), (h))

#include <asm-generic/dma-mapping-common.h>

#endif /* __ASM_UNICORE64_DMA_MAPPING_H__ */
