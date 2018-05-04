#ifndef CARBONDEFINE_H
#define CARBONDEFINE_H


#ifndef NULL
#define NULL (0)
#endif // NULL

#ifndef __cplusplus

#define true (1)
#define false (0)

#define nullptr (0);

typedef int bool;

#endif //__cplusplus

#define TRUE true
#define FALSE false

typedef unsigned long long uint64_t;
typedef long long int64_t;

typedef unsigned int uint32_t;
typedef int int32_t;

typedef unsigned short uint16_t;
typedef short int16_t;

typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef uint32_t size_t;
typedef uint32_t id_t;


#endif // CARBONDEFINE_H