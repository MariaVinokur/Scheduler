/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 	*
 *	Title			:	scheduler Header File							        *
 *	Author			: 	Maria Vinokur	                                    *
 *  Date            :   22/05/2023        							   	*
 *	Description  	: 	Contains type and function declarations				*
 *					  	required by scheduler 			                        *
 *					  														*
 *	HRD30	Infinity Labs R&D		   										*
 *					  														*
 *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 	*/
#include <time.h>       /*  time_t  */
#include <assert.h>

#include "scheduler.h"

/*for implementation*/
#include "task.h"
#include "pqueue.h"
#include "utils.h"



/*in header #include "uid.h"*/

typedef int(*func_ptr)(void *param);

struct sched
{
	pq_ty *pq;
	int is_running;
	time_t time_offset;
	task_ty *curr;
	DEBUG_ONLY(int is_stopped);
	
};

static time_t Now(time_t offset)
{
	return (time(NULL) - offset);
}

static task_ty *CastToTask(void *data)
{
	return (task_ty *)data;
}


sched_ty *SchedCreate()
{
	/*Create Sched -> malloc */
	/*if failed*/
	/*  -return NULL*/
	/* sc->pq = CreatePq(TaskCmp);*/
	/*check if failed*/
	/*  -destroy Sched*/
	/*  -return NULL*/
	/*is_running = 0*/
	/*base_clock = 0*/
	
	sched_ty *sch = malloc(sizeof(sched_ty));
	if(NULL == sch)
	{
		return NULL;
	}
	
	sch->pq = PQCreate((int(*)(const void *, const void *))&TaskCmp);
	if(NULL == sch->pq)
	{
		free(sch);
		sch = NULL;
		return NULL;
	}
	
	sch->is_running = 0;
	sch->time_offset = 0;
	DEBUG_ONLY(sch->is_stopped = 0);
	
	return sch;
}

void SchedDestroy(sched_ty *scheduler_)
{	
	/*while PQ not empty*/
	/*res = Peek*/
	/*TaskDestroy(res)*/
	/*DQ*/
	
	/*fields = 0*/
	/*free*(sched)*/
	/*=NULL*/
	
	task_ty *res = NULL;
	
	assert(!scheduler_ ||  scheduler_->is_running == 0);
	
	while(!PQIsEmpty(scheduler_->pq))
	{
		res = CastToTask(PQPeek(scheduler_->pq));
		TaskDestroy(res);
		PQDequeue(scheduler_->pq);
	}
	
	PQDestroy(scheduler_->pq);
	
	scheduler_->pq = NULL;
	scheduler_->is_running = 0;
	scheduler_->time_offset = 0;
	scheduler_->curr = NULL;
	
	free(scheduler_);
	scheduler_ = NULL;
}

uid_ty SchedAdd(sched_ty *scheduler_, size_t interval_seconds_,
					int (*action)(void *param), void *param_)
{
	/*assert*/
	
	/*task_ty *task = TaskCreate(interval_seconds_, action, param)*/
	/*if failed*/
	/*  -return BAD_UID */
	
	/*add to PQEnque(scheduler.pq, task)*/
	/*if failed*/
	/*TaskDestroy(task)*/
	/*  -return BAD_UID*/
	/*return TaskGetUid(task)*/
	
	task_ty *task = NULL;
	
	assert(scheduler_);
	assert(action);
	assert(0 != interval_seconds_);
	
	task = TaskCreate(interval_seconds_, action, param_);
	if(NULL == task)
	{
		return BAD_UID;
	}
	
	if(0 != PQEnqueue(scheduler_->pq, task))
	{
		TaskDestroy(task);
		return BAD_UID;
	}
	
	return TaskGetID(task);
}

void SchedRemove(sched_ty *scheduler_, uid_ty id_)
{
	/*assert*/
	/*if TaskGetUid(curr) == task_*/
	/*  -DestroyTask(curr)*/
	/*  -curr = NULL*/
	
	/*else*/
	/*  -res = PQErase(TaskIsMatch) */
	
	/*if res != NULL*/
	/*    -DestroyTask(res)*/
	/*    -res = NULL*/
	
	task_ty *to_rem = scheduler_->curr;
	
	assert(scheduler_);
	assert(&id_);
	
	puts("sch remove");
	
	
	if(to_rem && TaskIsMatchID(to_rem, &id_))
	{
		scheduler_->curr = NULL;
	}
	
	else
	{
		puts("not current");
		to_rem = PQErase(scheduler_->pq, 
		(int(*)(const void *, const void *))&TaskIsMatchID,
		(void *)&id_);
		
		printf("to_rem:%p\n", to_rem);
	}
	
	TaskDestroy(to_rem);


	
}

int SchedRun(sched_ty *scheduler_)
{
	/*assert*/
	/*assert - is_running == 0*/   /*would not run again if already running!!*/
	/*assert - debug_was_stopped == 0*/ /*would not run again if stopped!!*/
	
	/*time_offset = time() */ 
	/*is_running = 1*/
	
	/*-while PQ not empty && is_running*/
	/*  -curr = CastToTask(Peek)*/
	/*  -while (now(offset) < When()) */
	/*     -sleep(When() - now(offset)) */
	/*  -Pop*/
	/*  -DoNUpdate saved task((cast to task)curr)*/
	/*  -if 1 returned && curr!=NULL*/ /*enque just if wasnt removed!!*/
	/*    -Enq - saved task*/
	/*  -else 0 */
	/*    -TaskDestroy(saved task)*/
	/*DEBUG_ONLY(debug_was_stopped = 1)*/
	/*return !PQIsEmpty*/
	
	assert(scheduler_);
	assert(0 == scheduler_->is_running);
	assert(0 == scheduler_->is_stopped);
	
	scheduler_->time_offset = time(NULL);
	scheduler_->is_running = 1;
	
	while(!PQIsEmpty(scheduler_->pq) && scheduler_->is_running)
	{
		puts("activate");
		scheduler_->curr = CastToTask(PQPeek(scheduler_->pq));
		
		while(Now(scheduler_->time_offset) < (time_t)TaskWhen(scheduler_->curr))
		{
			sleep(TaskWhen(scheduler_->curr) - Now(scheduler_->time_offset));
		}
		
		PQDequeue(scheduler_->pq);
		

		if(1 == TaskDoNUpdate(scheduler_->curr) && NULL != scheduler_->curr)
		{
			puts("update and current != NULL");
			
			if(0 != PQEnqueue(scheduler_->pq, (void *)scheduler_->curr))
			{
				DEBUG_ONLY(scheduler_->is_stopped = 1);
				TaskDestroy(scheduler_->curr);
				return -1;
			}
		}
		else
		{
			puts("not update or current == NULL");
			TaskDestroy(scheduler_->curr);
		}
	}
	
	DEBUG_ONLY(scheduler_->is_stopped = 1);
	return !PQIsEmpty(scheduler_->pq);
	
}

void SchedStop(sched_ty *scheduler_)
{
	/*assert*/
	/*assert is_runnig == 1*/
	
	/*is_runnig = 0 */	
	
	assert(scheduler_);
	assert(1 == scheduler_->is_running);
	
	scheduler_->is_running = 0;
}

size_t SchedSize(const sched_ty *scheduler_)
{
	/*PQSize*/
	assert(scheduler_);
	
	return PQSize(scheduler_->pq);
}

int SchedIsEmpty(const sched_ty *scheduler_)
{
	/*PQIsEmpty*/
	assert(scheduler_);
	
	return PQIsEmpty(scheduler_->pq);
}

void SchedClear(sched_ty *scheduler_)
{
	/*while PQ not empty*/
	/*TaskDestroy(Peek)*/
	/*DQ*/
	
	task_ty *res = NULL;
	
	assert(scheduler_);
	
	while(!PQIsEmpty(scheduler_->pq))
	{
		res = CastToTask(PQPeek(scheduler_->pq));
		TaskDestroy(res);
		PQDequeue(scheduler_->pq);
	}
	
	/*TaskDestroy(scheduler_->curr);*/
	scheduler_->curr = NULL;
}








