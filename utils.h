/************************************************************
Author: Masha
Reviewer: 
Date: 18/05/2023
Title: utils Header File
Description: Function declarations and macros for utils
HRD30
*************************************************************/

#include <stdio.h>
#include <stdlib.h>


#ifndef __SORTLIST_H
#define __SORTLIST_H



#ifdef __GNUC__
#define LIKELY(X)   __builtin_expect((X), 1)   /* most of the times true*/
#define UNLIKELY(X)   __builtin_expect((X), 0) /* most of the times false*/
#define UNUSED  __attribute__((unused)) 
#else
#define LIKELY(X)   (X)
#define UNLIKELY(X) (X)
#endif /*#ifdef __GNUC__*/



#define RETURN_IF_BAD(exp, msg, err_no) if(!(exp)){\
								fprintf(stderr, "%s", msg);	  \
								return err_no;}				  \
								
								
#ifndef NDEBUG
#define DEBUG_ONLY(X) X
#else
#define DEBUG_ONLY(X) 		
#endif /*#ifndef NDEBUG*/	

static void ExitIfBad(int exp, char *msg, int err_no)UNUSED;																	


static void ExitIfBad(int exp, char *msg, int err_no)
{
	if(!exp)
	{
		fprintf(stderr, "%s", msg);
		exit(err_no);
	}
}

#endif /*#ifndef __SORTLIST_H*/
