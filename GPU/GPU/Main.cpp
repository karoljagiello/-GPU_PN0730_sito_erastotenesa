#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#else
#include <CL/cl.h>
#endif
#include "OpenCLHelper.h"
#include <vector>
#include "Sieve.h"


/* FILETIME of Jan 1 1970 00:00:00. */
static const unsigned __int64 epoch = ((unsigned __int64)116444736000000000ULL);

/*
* timezone information is stored outside the kernel so tzp isn't used anymore.
*
* Note: this function is not for Win32 high precision timing purpose. See
* elapsed_time().
*/
int
gettimeofday(struct timeval* tp, struct timezone* tzp)
{
    FILETIME    file_time;
    SYSTEMTIME  system_time;
    ULARGE_INTEGER ularge;

    GetSystemTime(&system_time);
    SystemTimeToFileTime(&system_time, &file_time);
    ularge.LowPart = file_time.dwLowDateTime;
    ularge.HighPart = file_time.dwHighDateTime;

    tp->tv_sec = (long)((ularge.QuadPart - epoch) / 100000000L);
    tp->tv_usec = (long)(system_time.wMilliseconds * 10000);

    return 0;
}

// Helper class for timing calculations
class CTiming
{
public:
    CTiming() {}
    ~CTiming() {}

    void Start() { gettimeofday(&tvBegin, NULL); }
    void End() { gettimeofday(&tvEnd, NULL); }
    bool Diff(int& seconds, int& useconds)
    {
        long int diff = (tvEnd.tv_usec + 10000000 * tvEnd.tv_sec) -
            (tvBegin.tv_usec + 10000000 * tvBegin.tv_sec);
        seconds = diff / 10000000;
        useconds = diff % 10000000;
        return (diff < 0) ? true : false;
    }

private:
    struct timeval tvBegin, tvEnd, tvDiff;

};

#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif
#define VECTOR_SIZE 10000

//OpenCL kernel which is run for every work item created.
const char* saxpy_kernel =
"__kernel                                   \n"
"void saxpy_kernel(float alpha,     \n"
"                  __global float *A,       \n"
"                  __global float *B,       \n"
"                  __global float *C)       \n"     
"{                                          \n"
"    //Get the index of the work-item       \n"
"    int index = get_local_id(0) + 2 ;          \n"
"    int i = get_group_id(0) + 2;          \n"

"    if(index * i <= get_global_size(0) / get_num_groups(0) + 2) { \n"
"       C[index * i - 3] = 1; "
"} \n"

"}                                     \n";

int main(void) {
    int i;
    // Allocate space for vectors A, B and C
    float alpha = 2.0;
    float* A = (float*)malloc(sizeof(float) * VECTOR_SIZE);
    float* B = (float*)malloc(sizeof(float) * VECTOR_SIZE);
    float* C = (float*)malloc(sizeof(float) * VECTOR_SIZE);
    for (i = 0; i < VECTOR_SIZE; i++)
    {
        A[i] = 1;

    }



    // Get platform and device information
    cl_platform_id* platforms = NULL;
    cl_uint     num_platforms;
    //Set up the Platform
    cl_int clStatus = clGetPlatformIDs(0, NULL, &num_platforms);
    platforms = (cl_platform_id*)
        malloc(sizeof(cl_platform_id) * num_platforms);
    clStatus = clGetPlatformIDs(num_platforms, platforms, NULL);

    //Get the devices list and choose the device you want to run on
    cl_device_id* device_list = NULL;
    cl_uint           num_devices;

    clStatus = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);
    device_list = (cl_device_id*)
        malloc(sizeof(cl_device_id) * num_devices);
    clStatus = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, num_devices, device_list, NULL);

    // Create one OpenCL context for each device in the platform
    cl_context context;
    context = clCreateContext(NULL, num_devices, device_list, NULL, NULL, &clStatus);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_list[0], 0, &clStatus);

    // Create memory buffers on the device for each vector
    cl_mem A_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY, VECTOR_SIZE * sizeof(float), NULL, &clStatus);
    cl_mem B_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY, VECTOR_SIZE * sizeof(float), NULL, &clStatus);
    cl_mem C_clmem = clCreateBuffer(context, CL_MEM_WRITE_ONLY, VECTOR_SIZE * sizeof(float), NULL, &clStatus);

    // Copy the Buffer A and B to the device
    clStatus = clEnqueueWriteBuffer(command_queue, A_clmem, CL_TRUE, 0, VECTOR_SIZE * sizeof(float), A, 0, NULL, NULL);
    clStatus = clEnqueueWriteBuffer(command_queue, B_clmem, CL_TRUE, 0, VECTOR_SIZE * sizeof(float), B, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&saxpy_kernel, NULL, &clStatus);

    // Build the program
    clStatus = clBuildProgram(program, 1, device_list, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "saxpy_kernel", &clStatus);

    // Set the arguments of the kernel
    clStatus = clSetKernelArg(kernel, 0, sizeof(float), (void*)&alpha);
    clStatus = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&A_clmem);
    clStatus = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&B_clmem);
    clStatus = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&C_clmem);

    // Execute the OpenCL kernel on the list
    float sq = floor(sqrt(VECTOR_SIZE));
    size_t global_size = (sq - 2) * (VECTOR_SIZE - 2); // Process the entire lists
    size_t local_size = VECTOR_SIZE - 2;           // Process one item at a time


    clStatus = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);

    // Read the cl memory C_clmem on device to the host variable C
    clStatus = clEnqueueReadBuffer(command_queue, C_clmem, CL_TRUE, 0, VECTOR_SIZE * sizeof(float), C, 0, NULL, NULL);

    // Clean up and wait for all the comands to complete.
    clStatus = clFlush(command_queue);
    clStatus = clFinish(command_queue);
    int test = 0;
    // Display the result to the screen
    for (i = 0; i < VECTOR_SIZE; i++)
        if (C[i] == 0 && i + 3 < VECTOR_SIZE)
            printf("%d ", i);

    // Finally release all OpenCL allocated objects and host buffers.
    clStatus = clReleaseKernel(kernel);
    clStatus = clReleaseProgram(program);
    clStatus = clReleaseMemObject(A_clmem);
    clStatus = clReleaseMemObject(B_clmem);
    clStatus = clReleaseMemObject(C_clmem);
    clStatus = clReleaseCommandQueue(command_queue);
    clStatus = clReleaseContext(context);
    free(A);
    free(B);
    free(C);
    free(platforms);
    free(device_list);
    return 0;
}