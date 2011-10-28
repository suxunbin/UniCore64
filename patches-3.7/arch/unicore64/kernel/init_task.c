#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>
#include <linux/mqueue.h>

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
