//#include "stdio.h"
//#include "test.h"
//#include "memory.h"
//#include "memory_heap.h"
//#include "kmemory.h"
//
//#define ALLOC_PAGE (100)
//
//bool memory_page_alloc_test(void)
//{
//	uint8_t* testPointer = malloc_page(ALLOC_PAGE);
//	TEST_ASSERT_TRUE(testPointer!=NULL,"malloc_page must return not null.");
//	free_page(testPointer,ALLOC_PAGE);
//	return TRUE;
//}
//
//bool memory_page_alloc_test_all_wirteable(void)
//{
//	uint8_t* testPointer = malloc_page(ALLOC_PAGE);
//	TEST_ASSERT_TRUE(testPointer!=NULL,"malloc_page must return not null.");
//	for(int index=0;index<ALLOC_PAGE*PAGE_SIZE;index++){
//		uint8_t value = (uint8_t)(index&0xff);
//		testPointer[index] = value;
//	}
//	for(int index=0;index<ALLOC_PAGE*PAGE_SIZE;index++){
//		uint8_t value = (uint8_t)(index&0xff);
//		TEST_ASSERT_TRUE(testPointer[index] == value,"malloc_page must return writeable memory.");
//	}
//	free_page(testPointer,ALLOC_PAGE);
//	return TRUE;
//}
//
//bool memory_heap_test(void)
//{
//	const int HEAP_PAGE = 100;
//	uint8_t* page = malloc_page(HEAP_PAGE);
//	TEST_ASSERT_TRUE(page!=NULL,"malloc_page must return not null.");
//	MemoryHeap* heap = createMemoryHeap(page,HEAP_PAGE*PAGE_SIZE);
//	TEST_ASSERT_TRUE(heap!=NULL,"createMemoryHeap must return not null.");
//
//	int* testPointer = MemoryHeap_malloc(heap,1024);
//	testPointer[0] = 100;
//	TEST_ASSERT_TRUE(testPointer[0] == 100,"MemoryHeap_malloc must return writeable memory.");
//	MemoryHeap_free(heap,testPointer);
//
//	destoryMemoryHeap(heap);
//	free_page(page,HEAP_PAGE);
//	return TRUE;
//}
//
//bool memory_heap_test_no_leak(void)
//{
//	const int HEAP_PAGE = 100;
//	uint8_t* page = malloc_page(HEAP_PAGE);
//	TEST_ASSERT_TRUE(page!=NULL,"malloc_page must return not null.");
//	MemoryHeap* heap = createMemoryHeap(page,HEAP_PAGE*PAGE_SIZE);
//	TEST_ASSERT_TRUE(heap!=NULL,"createMemoryHeap must return not null.");
//
//	size_t total = MemoryHeap_total(heap);
//	TEST_ASSERT_TRUE(total>0,"heap total must lage than 0.");
//	TEST_ASSERT_TRUE(total<HEAP_PAGE*PAGE_SIZE,"heap total must less than HEAP_PAGE*PAGE_SIZE.");
//	TEST_ASSERT_TRUE(MemoryHeap_used(heap)==0,"heap used must be zero.");
//
//	printk("step1:Loop malloc and free.\n");
//	for(int i=0;i<HEAP_PAGE;i++){
//		int* p = MemoryHeap_malloc(heap,PAGE_SIZE);
//		TEST_ASSERT_TRUE(p!=NULL,"MemoryHeap_malloc must return not null.");
//		TEST_ASSERT_TRUE(MemoryHeap_used(heap)>0,"heap used must lage than zero.");
//		TEST_ASSERT_TRUE(MemoryHeap_used(heap)==MemoryHeap_real_used(heap),"MemoryHeap_used must equal MemoryHeap_real_used.");
//		MemoryHeap_free(heap,p);
//		TEST_ASSERT_TRUE(MemoryHeap_used(heap)==0,"heap used must be zero.");
//		TEST_ASSERT_TRUE(MemoryHeap_used(heap)==MemoryHeap_real_used(heap),"MemoryHeap_used must equal MemoryHeap_real_used.");
//	}
//
//	int* pointerArray[HEAP_PAGE];
//	printk("step2:Loop malloc,Then loop free.\n");
//	for(int i=0;i<HEAP_PAGE;i++){
//		pointerArray[i] = MemoryHeap_malloc(heap,PAGE_SIZE/2);
//		TEST_ASSERT_TRUE(pointerArray[i]!=NULL,"MemoryHeap_malloc must return not null.");
//		TEST_ASSERT_TRUE(MemoryHeap_used(heap)==MemoryHeap_real_used(heap),"MemoryHeap_used must equal MemoryHeap_real_used.");
//	}
//	for(int i=0;i<HEAP_PAGE;i++){
//		MemoryHeap_free(heap,pointerArray[i]);
//		TEST_ASSERT_TRUE(MemoryHeap_used(heap)==MemoryHeap_real_used(heap),"MemoryHeap_used must equal MemoryHeap_real_used.");
//	}
//	TEST_ASSERT_TRUE(MemoryHeap_used(heap)==0,"heap used must be zero.");
//
//	printk("step3:Loop malloc with random free.Then loop free.\n");
//	for(int i=0;i<HEAP_PAGE;i++){
//		pointerArray[i] = MemoryHeap_malloc(heap,PAGE_SIZE);
//		TEST_ASSERT_TRUE(pointerArray[i]!=NULL,"MemoryHeap_malloc must return not null.");
//		TEST_ASSERT_TRUE(MemoryHeap_used(heap)==MemoryHeap_real_used(heap),"MemoryHeap_used must equal MemoryHeap_real_used.");
//		if(i%3==0){
//			MemoryHeap_free(heap,pointerArray[i]);
//			pointerArray[i] = NULL;
//		}
//	}
//	for(int i=0;i<HEAP_PAGE;i++){
//		if(pointerArray[i]!=NULL){
//			MemoryHeap_free(heap,pointerArray[i]);
//			TEST_ASSERT_TRUE(MemoryHeap_used(heap)==MemoryHeap_real_used(heap),"MemoryHeap_used must equal MemoryHeap_real_used.");
//		}
//	}
//	TEST_ASSERT_TRUE(MemoryHeap_used(heap)==0,"heap used must be zero.");
//
//
//	printk("step4:Loop malloc with write random free.Then loop read and free.\n");
//	for(int i=0;i<HEAP_PAGE;i++){
//		pointerArray[i] = MemoryHeap_malloc(heap,PAGE_SIZE);
//		TEST_ASSERT_TRUE(pointerArray[i]!=NULL,"MemoryHeap_malloc must return not null.");
//		TEST_ASSERT_TRUE(MemoryHeap_used(heap)==MemoryHeap_real_used(heap),"MemoryHeap_used must equal MemoryHeap_real_used.");
//		for(int j=0;j<PAGE_SIZE/sizeof(int);j++){
//			int value = i+j;
//			pointerArray[i][j] = value;
//		}
//		if(i%3==0){
//			MemoryHeap_free(heap,pointerArray[i]);
//			pointerArray[i] = NULL;
//		}
//	}
//	for(int i=0;i<HEAP_PAGE;i++){
//		if(pointerArray[i]!=NULL){
//			for(int j=0;j<PAGE_SIZE/sizeof(int);j++){
//				int value = i+j;
//				TEST_ASSERT_TRUE(pointerArray[i][j] == value,"");
//			}
//			MemoryHeap_free(heap,pointerArray[i]);
//			TEST_ASSERT_TRUE(MemoryHeap_used(heap)==MemoryHeap_real_used(heap),"MemoryHeap_used must equal MemoryHeap_real_used.");
//		}
//	}
//	TEST_ASSERT_TRUE(MemoryHeap_used(heap)==0,"heap used must be zero.");
//
//	destoryMemoryHeap(heap);
//	free_page(page,HEAP_PAGE);
//	return TRUE;
//}
//
//bool kernel_memory_heap_test(void)
//{
//	int* pointer = kmalloc(1024);
//	TEST_ASSERT_TRUE(pointer!=NULL,"kmalloc must return not null.");
//	pointer[0] = 123456;
//	TEST_ASSERT_TRUE(pointer[0]==123456,"kmalloc must return writeable memory.");
//	kfree(pointer);
//	return TRUE;
//}
//
