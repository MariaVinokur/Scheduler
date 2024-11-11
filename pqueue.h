/************************************************************
Author: Masha
Reviewer: 
Date: 17/05/2023
Title: priority queue Header File
Description: Function declarations of priority queue
HRD30
*************************************************************/

#ifndef __PQ_H
#define __PQ_H

#include <stddef.h> /* size_t */

typedef struct pq pq_ty;

/*
* returns NULL if fails
*/
pq_ty *PQCreate(int(* CmpFnc)(const void *el1, const void *el2));

/*
*	Complexity:	O(pq size). 
*/

void PQDestroy(pq_ty *pq);

/*
*	Output:		0 on success, -1 on fail.
*	Complexity:	O(pq size). 
*/

int PQEnqueue(pq_ty *pq, void *data);

/*	Output: undefined on empty queue
*	Complexity:	O(1). 
*/

void PQDequeue(pq_ty *pq);

/*  Output: undefined on empty queue
*	Complexity:	O(1). 
*/

void *PQPeek(pq_ty *pq);

/*
*	Complexity:	O(pq size). 
*/

size_t PQSize(const pq_ty *pq);

/*
*	Output:		Boolean
*	Complexity:	O(1). 
*/

int PQIsEmpty(const pq_ty *pq);

/*
*	Desc:		empties the pqueue without destoing it.
*	Complexity:	O(pq size). 
*/

void PQClear(pq_ty *pq);

/*
*	Desc: Erase matching element, by the match param
	Output: Returns pointer to erased data?????? NULL if failed???	
*	Complexity:	O(pq size)
*/

void *PQErase(pq_ty *pq_, 
			 int (*is_match_)(const void *elem_, const void *param_), 
			 const void *match_param_);

#endif 


