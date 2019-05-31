/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#include <config.h>
#include <benchmark/benchmark_track.h>
#include <model/statedata.h>

#ifdef CONFIG_BENCHMARK_TRACK_KERNEL_ENTRIES

void benchmark_track_exit(void)
{
    timestamp_t duration = 0;
    timestamp_t ksExit = timestamp();
    benchmark_track_kernel_entry_t *ksLog = (benchmark_track_kernel_entry_t *) KS_LOG_PPTR(getCurrentCPUIndex());

    if (likely(NODE_STATE(ksUserLogBuffer) != 0)) {
        /* If Log buffer is filled, do nothing */
        if (likely(NODE_STATE(ksLogIndex) < MAX_LOG_SIZE)) {
            duration = ksExit - NODE_STATE(ksEnter);
            ksLog[NODE_STATE(ksLogIndex)].entry = NODE_STATE(ksKernelEntry);
            ksLog[NODE_STATE(ksLogIndex)].start_time = NODE_STATE(ksEnter);
            ksLog[NODE_STATE(ksLogIndex)].duration = duration;
            NODE_STATE(ksLogIndex)++;
        }
    }
}
#endif /* CONFIG_BENCHMARK_TRACK_KERNEL_ENTRIES */
