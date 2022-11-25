_kernel void ProcessArray(_global int* data, _global int* outData)
{
    outData[get_global_id(0)] = data[get_global_id(0)] * 2;
}