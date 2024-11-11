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
 
 
#ifndef __ILRD_TASK_H
#define __ILRD_TASK_H

#include "uid.h" 

typedef struct task task_ty;

/*O(1)*/
/*param can be NULL*/
task_ty *TaskCreate(size_t interval_seconds_,
					int (*action)(void *param), void *param_);
					
/*O(1)*/				
void TaskDestroy(task_ty *task);

/*O(param size)*/
int TaskDoNUpdate(task_ty *task);

/*O(1)*/
size_t TaskWhen(const task_ty *task);

/*O(1)*/
int TaskCmp(const task_ty *task1, const task_ty *task2);

/*O(1)*/
int TaskIsMatchID(const task_ty *task, const uid_ty *uid);

/*O(1)*/
uid_ty TaskGetID(const task_ty *task);


#endif
