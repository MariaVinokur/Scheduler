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
 
 
#ifndef __ILRD_SCHEDULER_H
#define __ILRD_SCHEDULER_H

#include "uid.h"

typedef struct sched sched_ty;

/*Complexity: O(1)*/
/*can fail with memory allocations*/
sched_ty *SchedCreate();

/*Complexity: O(number of tasks)*/
void SchedDestroy(sched_ty *scheduler_);
	
/*Complexity: O(number of tasks)*/
/*action return 1 if needs to ENQ again, 0 if not*/
uid_ty SchedAdd(sched_ty *scheduler_, size_t interval_seconds_,
					int (*action)(void *param), void *param_);
	
/*Complexity: O(number of tasks)*/
void SchedRemove(sched_ty *scheduler_, uid_ty task_);
	
/*Complexity: O(number of tasks)*/
/*can fail with memory allocations*/
int SchedRun(sched_ty *scheduler_);
	
/*Complexity: O(1)*/
void SchedStop(sched_ty *scheduler_);

/*Complexity: O(number of tasks)*/
size_t SchedSize(const sched_ty *scheduler_);

/*Complexity: O(1)*/
int SchedIsEmpty(const sched_ty *scheduler_);

/*Complexity: O(number of tasks)*/
void SchedClear(sched_ty *scheduler_);



#endif
