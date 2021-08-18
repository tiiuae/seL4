#include <mode/smp/smp.h>
#include <arch/machine.h>

typedef struct {
	unsigned long func;
} trace_entry_t;

unsigned int te_head[CONFIG_MAX_NUM_NODES] = {0};
trace_entry_t tes[CONFIG_MAX_NUM_NODES][1024];

void __cyg_profile_func_enter(void *thisfn, void *call_site)
{
#ifdef ENABLE_SMP_SUPPORT
	int cpu = getCurrentCPUIndex();
#else
	int cpu = 0;
#endif
	tes[cpu][te_head[cpu]].func = (unsigned long) thisfn;
	te_head[cpu]++;
	te_head[cpu] &= 1023;
	__asm__ volatile ("dsb sy");
}

void __cyg_profile_func_exit(void *thisfn, void *call_site)
{
}
