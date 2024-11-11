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
 
 
#include "task.h"

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


/*DECLARATIONS OF TEST FUNCS*/

int TestCreate(void);
int TestDoNUpdate(void);
int TestWhen(void);
int TestCmp(void);
int TestIsMatch(void);
int TestGetUid(void);

/*DECLARATIONS OF HELP FUNCS*/

static int PrintTwos(void *nothing);


/*BLACK BOX TESTS*/
int main(void)
{
	RUN_TEST(TestCreate());
	RUN_TEST(TestDoNUpdate());
	RUN_TEST(TestWhen());
	RUN_TEST(TestCmp());
	RUN_TEST(TestIsMatch());
	RUN_TEST(TestGetUid());

	
	return 0;
}

/*DEFINITIONS*/

int TestCreate(void)
{
	task_ty *task = NULL;
	task = TaskCreate(2, PrintTwos, NULL);
	
	expect(NULL != task);
	expect(false == TaskIsMatchId(task, &BAD_UID));
	
	TaskDestroy(task);
	
	return TEST_PASS;
} 

int TestDoNUpdate(void)
{
	task_ty *task = NULL;
	int ret = 0;
	
	task = TaskCreate(2, PrintTwos, NULL);
	
	ret = TaskDoNUpdate(task);
	
	expect(true == ret);
	expect(4 == TaskWhen(task));
	
	TaskDestroy(task);
	
	return TEST_PASS;
} 

int TestWhen(void)
{
	task_ty *task = NULL;
	int ret = 0;
	
	task = TaskCreate(2, PrintTwos, NULL);
	
	ret = TaskDoNUpdate(task);
	
	expect(true == ret);
	expect(4 == TaskWhen(task));
	
	ret = TaskDoNUpdate(task);
	
	expect(true == ret);
	expect(6 == TaskWhen(task));
	
	TaskDestroy(task);
	
	return TEST_PASS;
} 

int TestCmp(void)
{
	task_ty *task1 = NULL;
	task_ty *task2 = NULL;
	
	task1 = TaskCreate(2, PrintTwos, NULL);
	task2 = TaskCreate(5, PrintTwos, NULL);
		
	expect(0 < TaskCmp(task1, task2));
	
	TaskDestroy(task1);
	TaskDestroy(task2);
	
	return TEST_PASS;
} 

int TestIsMatch(void)
{
	task_ty *task1 = NULL;
	task_ty *task2 = NULL;
	
	uid_ty uid1 = {0};
	uid_ty uid2 = {0};
	
	task1 = TaskCreate(2, PrintTwos, NULL);
	task2 = TaskCreate(5, PrintTwos, NULL);
	
	uid1 = TaskGetId(task1);
	uid2 = TaskGetId(task2);
		
	expect(false == TaskIsMatchId(task1, &uid2));
	expect(true == TaskIsMatchId(task1, &uid1));
	
	TaskDestroy(task1);
	TaskDestroy(task2);
	
	return TEST_PASS;
} 

int TestGetUid(void)
{
	task_ty *task1 = NULL;
	task_ty *task2 = NULL;
	
	uid_ty uid1 = {0};
	uid_ty uid2 = {0};
	
	task1 = TaskCreate(2, PrintTwos, NULL);
	task2 = TaskCreate(5, PrintTwos, NULL);
	
	uid1 = TaskGetId(task1);
	uid2 = TaskGetId(task2);
		
	expect(false == TaskIsMatchId(task1, &uid2));
	expect(true == TaskIsMatchId(task1, &uid1));
	expect(false == TaskIsMatchId(task1, &BAD_UID));
	
	TaskDestroy(task1);
	TaskDestroy(task2);
	
	return TEST_PASS;
} 

static int PrintTwos(void *nothing)
{
	static counter = 0;
	
	puts("22222");
	
	++counter;
	
	if(5 != counter)
	{
		return 1;
	}
	
	return 0;
}


