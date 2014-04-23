#ifndef __UNICORE64_ASM_DMA_MAPPING_H__
#define __UNICORE64_ASM_DMA_MAPPING_H__

#ifndef __ASSEMBLY__

/*
 * Optional coherency support.  Currently used only by selected
 * Intel XSC3-based systems.
 */
#ifndef arch_is_coherent
#define arch_is_coherent()		1
#endif

/*
 * The DMA mask corresponding to the maximum bus address allocatable
 * using GFP_DMA.  The default here places no restriction on DMA
 * allocations.  This must be the smallest DMA mask in the system,
 * so a successful GFP_DMA allocation will always satisfy this.
 */
#ifndef ISA_DMA_THRESHOLD
#define ISA_DMA_THRESHOLD	(0xffffffffULL)
#endif

#endif

static inline void *dma_alloc_noncoherent(struct device *dev, size_t size,
		dma_addr_t *handle, gfp_t gfp)
{
	return NULL;
}

static inline void dma_free_noncoherent(struct device *dev, size_t size,
		void *cpu_addr, dma_addr_t handle)
{

}

static inline int dma_supported(struct device *dev, u64 mask)
{
	if (mask < ISA_DMA_THRESHOLD)
		return 0;
	return 1;
}

static inline dma_addr_t virt_to_dma(struct device *dev, void *addr)
{
	return (dma_addr_t)__va((unsigned long)(addr));
}

static inline dma_addr_t page_to_dma(struct device *dev, struct page *page)
{
	return (dma_addr_t)__pa((unsigned long)page_address(page));
}

static inline dma_addr_t dma_map_page(struct device *dev, struct page *page,
	     unsigned long offset, size_t size, enum dma_data_direction dir)
{
	return page_to_dma(dev, page) + offset;
}

static inline void dma_unmap_page(struct device *dev, dma_addr_t handle,
		size_t size, enum dma_data_direction dir)
{
	/* do nothing */
}

static inline int dma_mapping_error(struct device *dev, dma_addr_t dma_addr)
{
	return dma_addr == ~0;
}


extern void dma_free_coherent(struct device *, size_t, void *, dma_addr_t);
extern void *dma_alloc_coherent(struct device *, size_t, dma_addr_t *, gfp_t);
/*
 * The scatter list versions of the above methods.
 */
extern int dma_map_sg(struct device *, struct scatterlist *, int,
		enum dma_data_direction);
extern void dma_unmap_sg(struct device *, struct scatterlist *, int,
		enum dma_data_direction);
extern void dma_sync_sg_for_cpu(struct device *, struct scatterlist *, int,
		enum dma_data_direction);
extern void dma_sync_sg_for_device(struct device *, struct scatterlist *, int,
		enum dma_data_direction);

#endif /* __UNICORE64_ASM_DMA_MAPPING_H__ */
