#include <asm/unaligned.h>
#include "uncompress.h"

unsigned char *output_data;
unsigned long output_ptr;

unsigned int free_mem_ptr;
unsigned int free_mem_end_ptr;

/**
 * error() - print error information.
 * @x: error information
 *
 * It will print the error information, then halt.
 */
static void error(char *x)
{
	arch_decomp_puts("\n\n");
	arch_decomp_puts(x);
	arch_decomp_puts("\n\n -- System halted");

	arch_decomp_error(x);

	for (;;)
		;
}

/**
 * Heap size should be adjusted for different decompress method
 */
#ifdef CONFIG_KERNEL_GZIP
#include "../../../../lib/decompress_inflate.c"
#endif

#ifdef CONFIG_KERNEL_BZIP2
#include "../../../../lib/decompress_bunzip2.c"
#endif

#ifdef CONFIG_KERNEL_LZO
#include "../../../../lib/decompress_unlzo.c"
#endif

#ifdef CONFIG_KERNEL_LZMA
#include "../../../../lib/decompress_unlzma.c"
#endif

/**
 * decompress_kernel() - Decompress the kernel image
 * @output_start: the address of kernel output
 * @free_mem_ptr_p: the pointer of free memory
 * @free_mem_ptr_end_p: the pointer of the end of free memory
 */
unsigned long decompress_kernel(unsigned long output_start,
		unsigned long free_mem_ptr_p,
		unsigned long free_mem_ptr_end_p)
{
	unsigned char *tmp;

	output_data		= (unsigned char *)output_start;
	free_mem_ptr		= free_mem_ptr_p;
	free_mem_end_ptr	= free_mem_ptr_end_p;

	arch_decomp_setup();

	tmp = (unsigned char *) (((unsigned long)input_data_end) - 4);
	output_ptr = get_unaligned_le32(tmp);

	arch_decomp_puts("Uncompressing Linux...");
	decompress(input_data, input_data_end - input_data, NULL, NULL,
			output_data, NULL, error);
	arch_decomp_puts(" done, booting the kernel.\n");
	return output_ptr;
}
