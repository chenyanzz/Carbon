#ifndef CARBONSTDARG_H
#define CARBONSTDARG_H
#include "CarbonDefine.h"
typedef char* va_list;
#define va_start(p, first) (p = (va_list)&first + sizeof(first))
#define va_args(p, next) ({ (*(next*)((p += sizeof(next)) - sizeof(next))); })
#define va_end(p) (p = (va_list)NULL)
#endif // CARBONSTDARG_H