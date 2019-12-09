/*
 * Copyright (c) 2008 Travis Geiselbrecht
 *
 * Copyright (c) 2009-2014, The Linux Foundation. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <compiler.h>
#include <debug.h>
#include <string.h>
#include <app.h>
#include <arch.h>
#include <platform.h>
#include <target.h>
#include <lib/heap.h>
#include <kernel/thread.h>
#include <kernel/timer.h>
#include <kernel/dpc.h>
#include <boot_stats.h>

extern void *__ctor_list;
extern void *__ctor_end;
extern int __bss_start;
extern int _end;

static int bootstrap2(void *arg);

#if (ENABLE_NANDWRITE)
void bootstrap_nandwrite(void);
#endif

static void call_constructors(void)
{
	void **ctor;

	ctor = &__ctor_list;
	while(ctor != &__ctor_end) {
		void (*func)(void);

		func = (void (*)())*ctor;

		func();
		ctor++;
	}
}

/* called from crt0.S */
void kmain(void) __NO_RETURN __EXTERNALLY_VISIBLE;
void kmain(void)
{
	// get us into some sort of thread context
	thread_init_early();	/* thread系统早期初始化 */

	// early arch stuff
	arch_early_init();	/* arch架构相关早期初始化 */

	// do any super early platform initialization
	platform_early_init();	/* msm平台的早期初始化(board、时钟和中断控制器初始化等) */

	// do any super early target initialization
	target_early_init();	/* target早期初始化(主要是debug串口的初始化) */

	dprintf(INFO, "welcome to lk\n\n");
	bs_set_timestamp(BS_BL_START);

	// deal with any static constructors
	dprintf(SPEW, "calling constructors\n");
	call_constructors();

	// bring up the kernel heap
	dprintf(SPEW, "initializing heap\n");
	heap_init();	/* kernel heap初始化 */

	__stack_chk_guard_setup();

	// initialize the threading system
	dprintf(SPEW, "initializing threads\n");
	thread_init();	/* thread系统初始化 */

	// initialize the dpc system
	dprintf(SPEW, "initializing dpc\n");
	dpc_init();	/* dpc系统相关初始化 */

	// initialize kernel timers
	dprintf(SPEW, "initializing timers\n");
	timer_init();	/* kernel timer初始化 */

#if (!ENABLE_NANDWRITE)
	// create a thread to complete system initialization
	dprintf(SPEW, "creating bootstrap completion thread\n"); /* 创建bootstrap2线程完成system初始化 */
	thread_resume(thread_create("bootstrap2", &bootstrap2, NULL, DEFAULT_PRIORITY, DEFAULT_STACK_SIZE));

	// enable interrupts
	exit_critical_section();	/* 使能中断 */

	// become the idle thread
	thread_become_idle();	/* 将当前线程设置为idle状态 */
#else
    bootstrap_nandwrite();
#endif
}

int main(void);

/* lk启动的第二阶段(bootstrap2) */
static int bootstrap2(void *arg)
{
	dprintf(SPEW, "top of bootstrap2()\n");

	arch_init();	/* arch第二阶段初始化 */

	// XXX put this somewhere else
#if WITH_LIB_BIO
	bio_init();
#endif
#if WITH_LIB_FS
	fs_init();
#endif

	// initialize the rest of the platform
	dprintf(SPEW, "initializing platform\n");
	platform_init();	/* platform第二阶段初始化(msm8909只是简单输出debug信息) */

	// initialize the target
	dprintf(SPEW, "initializing target\n");
	target_init();	/* target第二阶段初始化 */

	dprintf(SPEW, "calling apps_init()\n");
	apps_init();	/* apps初始化 */

	return 0;
}

#if (ENABLE_NANDWRITE)
void bootstrap_nandwrite(void)
{
	dprintf(SPEW, "top of bootstrap2()\n");

	arch_init();

	// initialize the rest of the platform
	dprintf(SPEW, "initializing platform\n");
	platform_init();

	// initialize the target
	dprintf(SPEW, "initializing target\n");
	target_init();

	dprintf(SPEW, "calling nandwrite_init()\n");
	nandwrite_init();

	return 0;
}
#endif
