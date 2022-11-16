#pragma once
#include "Sieve.h"
#include "OpenCLHelper.h"
#define VECTOR_SIZE 1024

using namespace std;

int Sieve::SieveGPU(size_t n)
{

		cl_context context = 0;
		cl_command_queue commandQueue = 0;
		cl_program program = 0;
		cl_device_id device = 0;
		cl_kernel kernel = 0;
		cl_mem memObjects[2] = { 0, 0 };
		cl_int errNum;
		int array_size = 10;

		// Create an OpenCL context on first available platform
		context = OpenCLHelper::CreateContextGPU();
		if (context == NULL)
		{
			std::cerr << "Failed to create OpenCL context." << std::endl;
			system("pause");
			return 1;
		}

		// Create a command-queue on the first device available
		// on the created context
		commandQueue = OpenCLHelper::CreateCommandQueue(context, &device);
		if (commandQueue == NULL)
		{
			OpenCLHelper::CleanupSieve(context, commandQueue, program, kernel, memObjects);
			system("pause");
			return 2;
		}

		// Create OpenCL program from HelloWorld.cl kernel source
		program = OpenCLHelper::CreateProgram(context, device, "SieveAlg.cl");
		if (program == NULL)
		{
			OpenCLHelper::CleanupSieve(context, commandQueue, program, kernel, memObjects);
			system("pause");
			return 3;
		}

		// Create OpenCL kernel
		kernel = clCreateKernel(program, "main_kernel", NULL);
		if (kernel == NULL)
		{
			std::cerr << "Failed to create kernel" << std::endl;
			OpenCLHelper::Cleanup(context, commandQueue, program, kernel, memObjects);
			system("pause");
			return 4;
		}



		int	A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int	B[]= { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		// Read the output buffer back to the Host
		errNum = clEnqueueWriteBuffer(commandQueue, memObjects[1], CL_TRUE,
			0, sizeof(int), A,
			0, NULL, NULL);

		errNum = clEnqueueWriteBuffer(commandQueue, memObjects[1], CL_TRUE,
			0, sizeof(int), B,
			0, NULL, NULL);



		// Set the kernel arguments (result, a, b)
		errNum = clSetKernelArg(kernel, 0, sizeof(cl_mem), &memObjects[0]);
		errNum |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &memObjects[1]);


		size_t globalWorkSize[1] = { 8 };
		size_t localWorkSize[1] = { 1 };

		//timer.Start();

		// Queue the kernel up for execution across the array
		errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,
			globalWorkSize, localWorkSize,
			0, NULL, NULL);



		//timer.End();
		//if (timer.Diff(seconds, useconds))
		//	std::cerr << "Warning: timer returned negative difference!" << std::endl;
		//std::cout << "OpenCL ran in " << seconds << "." << useconds << " seconds" << std::endl << std::endl;

		OpenCLHelper::CleanupSieve(context, commandQueue, program, kernel, memObjects);

	
}
