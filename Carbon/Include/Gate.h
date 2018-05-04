#ifndef GATE_H
#define GATE_H
#include "CarbonDefine.h"
#include "Descriptor.h"
typedef struct __gate__ {
    uint16_t offset1;///< offset bits 0..15 
	uint16_t selector;
	uint16_t attr;
	uint16_t offset2;///<offset bits 16..31 地址高16位
} Gate;
#endif // GATE_H