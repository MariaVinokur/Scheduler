/************************************************************
Author: Masha
Reviewer: 
Date: 17/05/2023
Title: priority queue Header File
Description: Function declarations of priority queue
HRD30
*************************************************************/

#include "pqueue.h" 
#include <stdio.h>  /*  printf, puts  */

typedef enum 
{
	false = 0, 
	true = 1
} status;

enum {TEST_PASS = 0, TEST_FAIL = 1};

static const char *RED = "\33[1;31m";
static const char *GREEN = "\33[32;1m";
static const char *RESET = "\33[0m";

#define RUN_TEST(x) if(TEST_FAIL == (x)) {                            \
						printf("%s : %sFAILURE%s\n", #x, RED, RESET); \
						}											  \
					else {											  \
						printf("%s : %sSUCCESS%s\n", #x, GREEN, RESET); \
						}											  \
										
						
#define expect(x) if (!(x)) {return TEST_FAIL;} 

int TestCreate(void);
int TestEnq(void);
int TestDq(void);
int TestPeek(void);
int TestEmpty(void);
int TestSize(void);
int TestErase(void);
int TestClear(void);

static int IsMatch(const void *val1, const void *val2);

static int IntCmp(const void *val1, const void *val2);

int main(void)
{
	RUN_TEST(TestCreate());
	RUN_TEST(TestEnq());
	RUN_TEST(TestDq());
	RUN_TEST(TestPeek());
	RUN_TEST(TestEmpty());
	RUN_TEST(TestSize());
	RUN_TEST(TestErase());
	RUN_TEST(TestClear());
	
	return (0);
}

int TestCreate(void)
{
	pq_ty *my_list = NULL;
	my_list = PQCreate(IntCmp);
	
	expect(0 == PQSize(my_list));
	expect(true == PQIsEmpty(my_list));
	
	PQDestroy(my_list);
	
	return TEST_PASS;
} 


int TestEnq(void)
{
	int num1 = 2;
	int num2 = 9; 
	int num3 = 6; 
	
	int arr_expected[] = {9, 6, 2};
	
	unsigned int counter = 0, i = 0;

	
	pq_ty *my_pq = PQCreate(IntCmp);
	if(NULL == my_pq)
	{
		fprintf(stderr, "%s", "CREATE FAILED\n");
	}

	PQEnqueue(my_pq, &num1);
	PQEnqueue(my_pq, &num2);
	PQEnqueue(my_pq, &num3);
	
	expect(9 == *(int *)PQPeek(my_pq));
	
	puts("11");
	
	while(!PQIsEmpty(my_pq))
	{
			printf("*(int *)PQPeek(my_q): %d\n", *(int *)PQPeek(my_pq));
			if(*(int *)PQPeek(my_pq) == arr_expected[i])
			{
				++counter;
			}
			
			PQDequeue(my_pq);
		++i;
	}
	
	expect(3 == counter);
	
	PQDestroy(my_pq);
	
	
	return TEST_PASS;
} 

int TestDq(void)
{
	int num1 = 2;
	int num2 = 9; 
	int num3 = 6; 
	 
	
	pq_ty *my_q = PQCreate(IntCmp);
	if(NULL == my_q)
	{
		fprintf(stderr, "%s", "CREATE FAILED\n");
	}


	PQEnqueue(my_q, &num1);
	PQEnqueue(my_q, &num2);
	PQEnqueue(my_q, &num3);
	
	expect(9 == *(int *)PQPeek(my_q));
	PQDequeue(my_q);
	
	expect(6 == *(int *)PQPeek(my_q));
	PQDequeue(my_q);
	
	expect(2 == *(int *)PQPeek(my_q));
	PQDequeue(my_q);
	
	expect(true == PQIsEmpty(my_q));
	expect(0 == PQSize(my_q));
	
	PQDestroy(my_q);
	
	return TEST_PASS;
}

int TestClear(void)
{
	int num1 = 2;
	int num2 = 9; 
	int num3 = 6;  
	
	pq_ty *my_pq = PQCreate(IntCmp);
	if(NULL == my_pq)
	{
		fprintf(stderr, "%s", "CREATE FAILED\n");
	}


	PQEnqueue(my_pq, &num1);
	PQEnqueue(my_pq, &num2);
	PQEnqueue(my_pq, &num3);
	
	
	PQClear(my_pq);
	
	expect(0 == PQSize(my_pq));
	expect(true == PQIsEmpty(my_pq));
	
	PQDestroy(my_pq);
	
	return TEST_PASS;
}

int TestErase(void)
{
	int num1 = 2;
	int num2 = 9; 
	int num3 = 6; 
	
	int arr_expected[] = {9, 2};
	
	unsigned int counter = 0, i = 0;
	 
	
	pq_ty *my_pq = PQCreate(IntCmp);
	if(NULL == my_pq)
	{
		fprintf(stderr, "%s", "CREATE FAILED\n");
	}


	PQEnqueue(my_pq, &num1);
	PQEnqueue(my_pq, &num2);
	PQEnqueue(my_pq, &num3);
	
	
	PQErase(my_pq, IsMatch, &num3);
	
	expect(2 == PQSize(my_pq));
	
	while(!PQIsEmpty(my_pq))
	{
			printf("*(int *)PQPeek(my_q): %d\n", *(int *)PQPeek(my_pq));
			if(*(int *)PQPeek(my_pq) == arr_expected[i])
			{
				++counter;
			}
			
			PQDequeue(my_pq);
		++i;
	}
	
	
	expect(2 == counter);
	
	PQDestroy(my_pq);
	
	return TEST_PASS;
}

int TestPeek(void)
{
	int num1 = 5;
	int num2 = 6; 
	
	pq_ty *my_q = PQCreate(IntCmp);
	if(NULL == my_q)
	{
		fprintf(stderr, "%s", "CREATE FAILED\n");
	}


	PQEnqueue(my_q, &num1);
	PQEnqueue(my_q, &num2);
	
	expect(6 == *(int *)PQPeek(my_q));
	PQDequeue(my_q);
	
	expect(5 == *(int *)PQPeek(my_q));
	PQDequeue(my_q);
	
	PQDestroy(my_q);
	
	return TEST_PASS;
}

int TestEmpty(void)
{
	int num1 = 5;
	int num2 = 6; 
	int num3 = 8; 
	
	pq_ty *my_q = PQCreate(IntCmp);
	if(NULL == my_q)
	{
		fprintf(stderr, "%s", "CREATE FAILED\n");
	}

	PQEnqueue(my_q, &num1);
	PQEnqueue(my_q, &num2);
	PQEnqueue(my_q, &num3);
	
	expect(false == PQIsEmpty(my_q));
	
	PQDequeue(my_q);
	PQDequeue(my_q);
	PQDequeue(my_q);

	expect(true == PQIsEmpty(my_q));

	PQDestroy(my_q);
	
	return TEST_PASS;
}

int TestSize(void)
{
	int num1 = 5;
	int num2 = 6; 
	int num3 = 8; 
	
	pq_ty *my_q = PQCreate(IntCmp);
	if(NULL == my_q)
	{
		fprintf(stderr, "%s", "CREATE FAILED\n");
	}

	PQEnqueue(my_q, &num1);
	PQEnqueue(my_q, &num2);
	PQEnqueue(my_q, &num3);

	expect(3 == PQSize(my_q));
	
	PQDequeue(my_q);
	
	expect(2 == PQSize(my_q));
	
	PQDequeue(my_q);
	PQDequeue(my_q);
	
	expect(0 == PQSize(my_q));
	
	PQDestroy(my_q);
	
	return TEST_PASS;
}

static int IntCmp(const void *val1, const void *val2)
{
	/*printf("INT CMP: val1 - val2: %d\n", *(int *)val1 - *(int *)val2);*/
	return (*(int *)val1 - *(int *)val2);
}

static int IsMatch(const void *val1, const void *val2)
{
	/*printf("INT CMP: val1 - val2: %d\n", *(int *)val1 - *(int *)val2);*/
	return (*(int *)val1 == *(int *)val2);
}




