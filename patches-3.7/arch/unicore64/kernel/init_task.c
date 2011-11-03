#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>
#include <linux/mqueue.h>
#include <linux/hardirq.h>

/**
 * union init_thread_union - Initial thread structure.
 *
 * We need to make sure that this is 8192-byte aligned due to the
 * way process stacks are handled. This is done by making sure
 * the linker maps this in the .text segment right after head.S,
 * and making head.S ensure the proper alignment.
 *
 * The things we do for performance..
 */
union thread_union init_thread_union __init_task_data = {
	INIT_THREAD_INFO(init_task) };

/**
 * struct init_signals -
 */
static struct signal_struct init_signals = INIT_SIGNALS(init_signals);

/**
 * struct init_sighand -
 */
static struct sighand_struct init_sighand = INIT_SIGHAND(init_sighand);

/**
 * struct init_task - Initial task structure.
 *
 * All other task structs will be allocated on slabs in fork.c
 */
struct task_struct init_task = INIT_TASK(init_task);
