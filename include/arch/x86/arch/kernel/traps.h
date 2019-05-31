/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#ifndef __KERNEL_X86_TRAPS_H
#define __KERNEL_X86_TRAPS_H

#include <config.h>
#include <util.h>

static inline void arch_c_entry_hook(void)
{
#ifdef CONFIG_VTX
#ifdef CONFIG_BENCHMARK_TRACK_UTILISATION
    tcb_t *cur_thread = NODE_STATE(ksCurThread);
    if (thread_state_ptr_get_tsType(&cur_thread->tcbState) == ThreadState_RunningVM) {
        if (likely(NODE_STATE(benchmark_log_utilisation_enabled))) {
            if (likely(NODE_STATE(ksEnter) > cur_thread->benchmark.vcpu_start_time)) {
                cur_thread->benchmark.vcpu_utilisation += (NODE_STATE(ksEnter) - cur_thread->benchmark.vcpu_start_time);
            }
        }
    }
#endif
#endif
}

static inline void arch_c_exit_hook(void)
{
#ifdef CONFIG_VTX
#ifdef CONFIG_BENCHMARK_TRACK_UTILISATION
    tcb_t *cur_thread = NODE_STATE(ksCurThread);
    if (thread_state_ptr_get_tsType(&cur_thread->tcbState) == ThreadState_RunningVM) {
        if (likely(NODE_STATE(benchmark_log_utilisation_enabled))) {
            cur_thread->benchmark.vcpu_start_time = timestamp();
        }
    }
#endif
#endif
}

void c_handle_syscall(word_t cptr, word_t msgInfo, syscall_t syscall, word_t reply)
VISIBLE NORETURN;

void restore_user_context(void)
VISIBLE NORETURN;

void c_nested_interrupt(int irq)
VISIBLE;

void c_handle_interrupt(int irq, int syscall)
VISIBLE NORETURN;

void c_handle_vmexit(void)
VISIBLE NORETURN;

#endif /* __KERNEL_X86_TRAPS_H */
