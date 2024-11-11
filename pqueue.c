/************************************************************
Author: Masha
Reviewer: 
Date: 17/05/2023
Title: priority queue Header File
Description: Function declarations of priority queue
HRD30
*************************************************************/

#include <assert.h> /*   assert          */
#include <stdio.h>


#include "pqueue.h"
#include "sortlist.h"


static sortlist_ty *CastToSortList(const pq_ty *pq_)
{
	assert(pq_);
	
	return (sortlist_ty *)pq_;
}

pq_ty *PQCreate(int(* CmpFnc)(const void *el1_, const void *el2_))
{	
	assert(CmpFnc);
	
	return (pq_ty *)SortListCreate(CmpFnc);
}

void PQClear(pq_ty *pq_)
{
	assert(pq_);
	
	while(!PQIsEmpty(pq_))
	{
		PQDequeue(pq_);
	}
}

void *PQErase(pq_ty *pq_, 
			 int (*is_match_)(const void *elem_, const void *param_), 
			 const void *match_param_)
{
	
	sort_iter_ty current = {0};
	sort_iter_ty end = {0};

		
	assert(pq_);
	assert(is_match_);
	assert(match_param_);
	
	current = SortListBegin(CastToSortList(pq_));
	end = SortListEnd(CastToSortList(pq_));
	
	while(!SortListIsEqual(current, end))
	{
		if(is_match_(SortListGetData(current), match_param_))
		{
			void *ret = NULL;
			ret = SortListGetData(current);
			SortListRemove(current);
			return ret;
		}
		
		current = SortListNext(current);
	}
	
	return NULL;
}

void PQDestroy(pq_ty *pq_)
{
	assert(pq_);
	
	if(NULL != pq_)
	{
		SortListDestroy(CastToSortList(pq_));
		pq_ = NULL;
	}
} 


int PQEnqueue(pq_ty *pq_, void *data_)
{	
	assert(pq_);
	assert(data_);
			
	return SortListInsert(CastToSortList(pq_), data_);
	
}

size_t PQSize(const pq_ty *pq_)
{
	assert(pq_);
	
	return SortListSize(CastToSortList(pq_));
}


void PQDequeue(pq_ty *pq_)
{
	assert(pq_);
	
	SortListPopFront(CastToSortList(pq_));
}

int PQIsEmpty(const pq_ty *pq_)
{
	assert(pq_);
	
	return SortListIsEmpty(CastToSortList(pq_));
}

void *PQPeek(pq_ty *pq_)
{
	assert(pq_);
	
	return SortListGetData(SortListBegin(CastToSortList(pq_)));
}



