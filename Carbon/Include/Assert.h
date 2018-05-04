#ifndef ASSERT_H
#define ASSERT_H
#include "CarbonKernelIO.h"
#include "CarbonDefine.h"
#include "CarbonELFDescriptor.h"
#ifndef NDEBUG
    #define assert(expr) (void)((expr) || ((Assert(#expr,__FILE__,__LINE__),0)))
#else
    #define assert(expr) ((void)0)
#endif // NDEBUG
void Assert(void *exp, void *file, unsigned int line);
void InitDebug();
void PrintStackTrace();
#endif // ASSERT_H