#pragma once
#include <stdlib.h>
#include <vector>
#include <CL/cl.hpp>

class Sieve
{
public:
	/* Get number of all prime numbers between 1 and n with OpenCL on the CPU. */
	static int SieveGPU(size_t n);
};
