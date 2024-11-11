/*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 	*
 *	Title			:	task Header File							        *
 *	Author			: 	Maria Vinokur	                                    *
 *  Date            :   22/05/2023        							   	*
 *	Description  	: 	Contains type and function declarations				*
 *					  	required by task 			                        *
 *					  														*
 *	HRD30	Infinity Labs R&D		   										*
 *					  														*
 *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 	*/
 
#include <assert.h>

#include "task.h"

typedef int(*func_ptr)(void *param);

struct task
{
	uid_ty uid;
	func_ptr action_func;
	void *param;
	size_t interval;
	size_t nextRun;
};

task_ty *TaskCreate(size_t interval_seconds_,
					int (*action)(void *param), void *param_)
{
	/*assert action*/
	
	/*Create Task -> malloc */
	/*if failed*/
	/*  -return NULL */
	
	/*uid = UIDCreate()*/
	/*if failed*/
	/*  -return NULL*/
	/*action_func = action*/
	/*interval = interval_seconds_*/
	/*param = param_*/
	/*nextRun = interval*/

 	/*return task*/
 	
 	task_ty *task = NULL;
 	
 	assert(action);
 	
 	task = malloc(sizeof(task_ty));
 	if(NULL == task)
 	{
 		return NULL;
 	}
 	
 	task->uid = UIDCreate();
 	if(UIDIsSame(&BAD_UID, &task->uid))
 	{
 		TaskDestroy(task);
 		return NULL;
 	}
 	
 	task->action_func = action;
 	task->param = param_;
 	task->interval = interval_seconds_;
 	task->nextRun = interval_seconds_;
 	
 	return task;
 	
 	
 	
}
						
void TaskDestroy(task_ty *task)
{	
	/*fields to zero*/
	/*free(task)*/
	printf("task: %p\n", task);
	DEBUG_ONLY(
	if(NULL != task)
	{
		puts("task not null");
		task->uid = BAD_UID;
		task->action_func = NULL;
		task->param = NULL;
		task->interval = 0;
		task->nextRun = 0;
	}
	)
	
	free(task);
	task = NULL;
}

int TaskDoNUpdate(task_ty *task)
{
	/*assert*/
	
	/*task.nextRun += task.interval*/
	/*ret = task.action_func(task.param)*/
	/*return ret*/
	
	assert(task);
	
	task->nextRun += task->interval;
	
	return task->action_func(task->param);
}

size_t TaskWhen(const task_ty *task)
{
	/*assert*/
	/*return task.nextRun;*/
	
	assert(task);
	
	return task->nextRun;
}


int TaskCmp(const task_ty *task1, const task_ty *task2)
{
	/*assert*/
	/*retrun task2.nextRun - task1.nextRun*/
	
	assert(task1);
	assert(task2);
	
	return task2->nextRun - task1->nextRun;
}

int TaskIsMatchID(const task_ty *task, const uid_ty *uid)
{
	/*assert*/
	/*return UIDIsSame(task.uid, *uid)*/
	
	assert(task);
	assert(uid);
	
	return UIDIsSame(&task->uid, uid);
}

uid_ty TaskGetID(const task_ty *task)
{
	/*assert*/
	/*return task.uid*/
	
	assert(task);
	
	return task->uid;
}


