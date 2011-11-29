#ifndef __ASM_UNICORE64_DMA_MAPPING_H__
#define __ASM_UNICORE64_DMA_MAPPING_H__

extern struct dma_map_ops swiotlb_dma_map_ops;

#define get_dma_ops(dev)		(&swiotlb_dma_map_ops)

#define dma_supported(d, m)			\
		(get_dma_ops(dev)->dma_supported((d), (m)))
#define dma_alloc_coherent(d, s, h, f)		\
		(get_dma_ops(dev)->alloc_coherent((d), (s), (h), (f)))
#define dma_free_coherent(d, s, a, h)		\
		(get_dma_ops(dev)->free_coherent((d), (s), (a), (h)))

#define dma_alloc_noncoherent(d, s, h, f)	\
		dma_alloc_coherent((d), (s), (h), (f))
#define dma_free_noncoherent(d, s, a, h)	\
		dma_free_coherent((d), (s), (a), (h))

extern bool dma_capable(struct device *dev, dma_addr_t addr, size_t size);
extern dma_addr_t phys_to_dma(struct device *dev, phys_addr_t paddr);
extern phys_addr_t dma_to_phys(struct device *dev, dma_addr_t daddr);
extern void dma_mark_clean(void *addr, size_t size);

#include <asm-generic/dma-mapping-common.h>

#endif /* __ASM_UNICORE64_DMA_MAPPING_H__ */
