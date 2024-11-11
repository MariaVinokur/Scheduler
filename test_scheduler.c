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
 
 
#include "scheduler.h"

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

static int MyActionRemove(void *param_);
static int MyActionStop(void *sched);
static int MyActionAdd(void *sched);
static int PrintTwos(void *nothing);
static int PrintTrees(void *nothing);
static int PrintNines(void *nothing);
static int PrintA(void *nothing);



int TestCreate(void);
int TestAdd(void);
int TestRemove(void);
int TestRun(void);
int TestStop(void);

/*BLACK BOX TESTS*/

int counter_twos_g = 0;
int counter_trees_g = 0;
int counter_nines_g = 0;
int counter_adds_g = 0;

int main(void)
{
	/*RUN_TEST(TestCreate());
	RUN_TEST(TestAdd());*/
	RUN_TEST(TestRemove());
	/*RUN_TEST(TestRun());
	RUN_TEST(TestStop());*/
	
	return 0;
}

int TestCreate(void)
{
	sched_ty *sch = SchedCreate();
	expect(NULL != sch);
	expect(0 == SchedSize(sch));
	expect(true == SchedIsEmpty(sch));
	
	SchedDestroy(sch);
	
	return TEST_PASS;

}

int TestAdd(void)
{
	sched_ty *sch = SchedCreate();
	uid_ty my_action1 = SchedAdd(sch, 2, PrintTwos, NULL);
	uid_ty my_action2 = SchedAdd(sch, 3, PrintTrees, NULL);
	uid_ty my_action3 = SchedAdd(sch, 5, MyActionRemove, (void *)&my_action2);
	
	(void)my_action3;
	(void)my_action1;
	
	SchedDestroy(sch);
	
	return TEST_PASS;
}

typedef struct sch_n_uid
{
	sched_ty *sch;
	uid_ty uid;
}param_ty;

int TestRemove(void)
{
	param_ty param = {0};
	sched_ty *sch = SchedCreate();
	
 	uid_ty my_action1 = SchedAdd(sch, 2, PrintTwos, NULL);
	uid_ty my_action2 = SchedAdd(sch, 7, PrintTrees, NULL);
	uid_ty my_action3 = {0};
	uid_ty my_action4 = {0};
	
	(void)my_action1;
	(void)my_action2;
	(void)my_action3;
	(void)my_action4;
	
	counter_twos_g = 0;
	counter_trees_g = 0;
	counter_nines_g = 0;
	
	param.sch = sch;
	param.uid = my_action1;
	
	my_action3 = SchedAdd(sch, 10, MyActionRemove, (void *)&param);
	my_action4 = SchedAdd(sch, 11, MyActionStop, sch);
	
	expect(1 == SchedRun(sch));
	expect(2 == SchedSize(sch));
	
	SchedDestroy(sch);
	
	return TEST_PASS;
}

int TestRun(void)
{
	sched_ty *sch = SchedCreate();
	
	uid_ty my_action1 = SchedAdd(sch, 2, PrintTwos, NULL);
	uid_ty my_action2 = SchedAdd(sch, 3, PrintTrees, NULL);
	uid_ty my_action3 = SchedAdd(sch, 9, PrintNines, NULL);
	uid_ty my_action4 = SchedAdd(sch, 10, MyActionAdd, sch);
	
	counter_twos_g = 0;
	counter_trees_g = 0;
	counter_nines_g = 0;
	
	(void)my_action1;
	(void)my_action2;
	(void)my_action3;
	(void)my_action4;
	
	expect(0 == SchedRun(sch));
	
	SchedDestroy(sch);
	
	return TEST_PASS;
}

int TestStop(void)
{
	sched_ty *sch = SchedCreate();
	
	uid_ty my_action1 = SchedAdd(sch, 2, PrintTwos, NULL);
	uid_ty my_action2 = SchedAdd(sch, 3, PrintTrees, NULL);
	uid_ty my_action3 = SchedAdd(sch, 9, PrintNines, NULL);
	uid_ty my_action4 = SchedAdd(sch, 10, MyActionStop, sch);
	
	counter_twos_g = 0;
	counter_trees_g = 0;
	counter_nines_g = 0;
	
	(void)my_action1;
	(void)my_action2;
	(void)my_action3;
	(void)my_action4;
	
	expect(1 == SchedRun(sch));
	expect(3 == SchedSize(sch));
	
	SchedDestroy(sch);
	
	return TEST_PASS;
}

static int MyActionStop(void *sched)
{
	puts("TEST: myStop()");
	SchedStop(sched);
	
	return 0;
}

static int MyActionAdd(void *sched)
{
	SchedAdd(sched, 5, PrintA, NULL);
	
	++counter_adds_g;
	
	if(3 != counter_adds_g)
	{
		return 1;
	}
	
	return 0;
}

static int PrintA(void *nothing)
{
	puts("AAA");
	
	(void)nothing;
	
	return 0;
}

static int MyActionRemove(void *param_)
{
	param_ty *param = (param_ty *)param_;
	
	puts("remove");
	
	SchedRemove(param->sch, param->uid);
	
	return 1;
}

static int PrintTwos(void *nothing)
{
	puts("22222");
	
	++counter_twos_g;
	
	(void)nothing;
	
	if(10 != counter_twos_g)
	{
		return 1;
	}
	
	return 0;
}


static int PrintTrees(void *nothing)
{	
	puts("33333");
	
	++counter_trees_g;
	
	(void)nothing;
	
	if(4 != counter_trees_g)
	{
		return 1;
	}
	
	return 0;
}


static int PrintNines(void *nothing)
{
	puts("9999");
	
	++counter_nines_g;
	
	(void)nothing;
	
	if(3 != counter_nines_g)
	{
		return 1;
	}
	
	return 0;
}




