
#ifndef __CMDQ_MMP_H__
#define __CMDQ_MMP_H__

#include "mmprofile.h"
#include "cmdq_core.h"

struct CMDQ_MMP_events_t {
	mmp_event CMDQ;
	mmp_event CMDQ_IRQ;
	mmp_event thread_en;
	mmp_event warning;
	mmp_event loopBeat;
	mmp_event autoRelease_add;
	mmp_event autoRelease_done;
	mmp_event consume_add;
	mmp_event consume_done;
	mmp_event alloc_task;
	mmp_event wait_task;
	mmp_event wait_task_done;
	mmp_event wait_thread;
	mmp_event MDP_reset;
	mmp_event thread_suspend;
	mmp_event thread_resume;
	mmp_event alloc_buffer;
};

void cmdq_mmp_init(void);
struct CMDQ_MMP_events_t *cmdq_mmp_get_event(void);

#endif				/* __CMDQ_MMP_H__ */