//#include "assert.h"
//#include "stddef.h"
//
//#define TEST_ASSERT_TRUE(result,msg) 					\
//do{														\
//	if((result)!=TRUE){									\
//		_assert(msg,__FILE__,__LINE__);					\
//		return FALSE;									\
//	}													\
//}while(0)
//
//
//#define TEST_ASSERT_FALSE(result,msg) TEST_ASSERT_TRUE(!(result),msg)
//
//#define TEST_CASE(testcase) {#testcase,testcase,TEST_RESULT_NOT_EXECUTED}
//
//#define ARY_LEN(ary) (sizeof(ary)/sizeof(ary[0]))
//
//
//typedef bool (*test_case_fun)(void);
//
///**
// * TestResult
// * TEST_RESULT_NOT_EXECUTED
// *
// */
//enum {
//	TEST_RESULT_NOT_EXECUTED = 0,
//	TEST_RESULT_PASS,
//	TEST_RESULT_FAIL,
//};
//
//struct TestCase_st {
//	char* testName;
//	test_case_fun testCase;
//	int testResult;
//};
//typedef struct TestCase_st TestCase;
//void init_test();
//void start_all_test();
//void start_test_case(TestCase* testCase);
//void show_test_case(TestCase* testCase);
//const char* get_test_result_str(int result);
