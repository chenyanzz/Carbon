//#include "stdio.h"
//#include "test.h"
//
//// extern all test case here
//extern bool memory_page_alloc_test(void);
//extern bool memory_page_alloc_test_all_wirteable(void);
//bool memory_heap_test(void);
//bool memory_heap_test_no_leak(void);
//bool kernel_memory_heap_test(void);
//// end of extern all test case
//
//// add all test case here
//static TestCase mTestCases[] =
//{
//	TEST_CASE(memory_page_alloc_test),
//	TEST_CASE(memory_page_alloc_test_all_wirteable),
//	TEST_CASE(memory_heap_test),
//	TEST_CASE(memory_heap_test_no_leak),
//	TEST_CASE(kernel_memory_heap_test),
//	TEST_CASE(NULL),
//};
//// end of add all test case
//
//
//void init_test(void)
//{
//	printk("init kernel test...\n");
//	start_all_test();
//}
//
//void start_all_test()
//{
//	printk("start all kernel test...\n");
//	for(int index = 0;index<ARY_LEN(mTestCases);index++){
//		TestCase* testCase = &mTestCases[index];
//		if(testCase->testCase!=NULL){
//			start_test_case(testCase);
//			show_test_case(testCase);
//		}
//	}
//}
//
//void start_test_case(TestCase* testCase)
//{
//	printk("Test:%s started.\n",testCase->testName);
//	bool result = testCase->testCase();
//	if(result){
//		// pass
//		testCase->testResult = TEST_RESULT_PASS;
//	}else{
//		// fail
//		testCase->testResult = TEST_RESULT_FAIL;
//	}
//	//printk("Test:%s finished.\n",testCase->testName);
//}
//
//const char* get_test_result_str(int result)
//{
//	switch(result){
//		case TEST_RESULT_NOT_EXECUTED:
//			return "not executed";
//		case TEST_RESULT_PASS:
//			return "pass";
//		case TEST_RESULT_FAIL:
//			return "fail";
//		default:
//			break;
//	}
//	return "unknown";
//}
//
//void show_test_case(TestCase* testCase)
//{
//	printk("Test:%s Result:%s.\n",testCase->testName,get_test_result_str(testCase->testResult));
//}
