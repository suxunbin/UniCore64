#ifndef __UNICORE64_UACCESS_H__
#define __UNICORE64_UACCESS_H__

/* To avoid unalignment problem */
#define __copy_from_user(to, from, n)	(memcpy(to, (void __force *)from, n), 0)
#define __copy_to_user(to, from, n)	(memcpy((void __force *)to, from, n), 0)

#include <asm-generic/uaccess.h>

#endif /* __UNICORE64_UACCESS_H__ */
