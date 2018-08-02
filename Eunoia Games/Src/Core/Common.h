#pragma once

#include <cstdio>
#include <cstdlib>

namespace Eunoia {

	typedef signed char int8;
	typedef unsigned char uint8;
	typedef signed short int int16;
	typedef unsigned short int uint16;
	typedef signed int int32;
	typedef unsigned int uint32;
	typedef signed long long int64;
	typedef unsigned long long uint64;

#define ASSERT(Condition, Message) if(!(Condition)) { printf(Message); printf("\n"); system("PAUSE"); std::exit(-1); }
}
