#include <linux/mm.h>

/**
 * pgd_alloc() - Allocates a new Page Global Directory
 * @mm:
 */
pgd_t *pgd_alloc(struct mm_struct *mm)
{
	/* FIXME */
	BUG();
}

/**
 * pgd_free() - Release a page table and insert the freed page frame in cache
 * @mm:
 * @pgd:
 */
void pgd_free(struct mm_struct *mm, pgd_t *pgd)
{
	/* FIXME */
	BUG();
}
