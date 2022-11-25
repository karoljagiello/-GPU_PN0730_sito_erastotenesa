__kernel void prototyp1(__global int* data, int size, int rootSize)
{
    size_t Gindex = get_global_id(0);
    int element = Gindex%size;
    element +=1;
    int dzielnik = Gindex / size;
    dzielnik +=1;
    if(dzielnik == 1) 
    {
        data[1] = get_local_size(0);
        return;
    }
    if(element == dzielnik) return;
    else if(element%dzielnik == 0)
    {
        data[element] = -1;
    }
    //data[element] = element;
}

__kernel void prototyp11(__global int* data, int size, int rootSize)
{
    long int index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
    int element = index/rootSize;
    element +=2;
    int dzielnik = index % rootSize;
    dzielnik +=2;
    if(element == dzielnik) return;
    else if(element%dzielnik == 0)
    {
        data[element] = -1;
    }
    //data[element] = element;
}

 __kernel void p12(__global int* data, __global int* data2, int divN)
{
    long int index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
    int element = index/divN;
    element +=2;
    int dzielnik = index % divN;
    if(element == data2[dzielnik]) return;
    else if(element%data2[dzielnik] == 0)
    {
        data[element] = -1;
    }
    //data[element] = divN;
}


__kernel void prototyp2(__global int* data, int div)
{
    size_t index = get_global_id(0);
    index +=2;
    if(index == div) return;
    else if(index%div == 0)
    {
        data[index] = -1;
    }
    //data[index] = index;
}

__kernel void test1(__global int* data,__global int* data2)
{
    long long int index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
    data[index] = index;
    data2[index] = index;
}

__kernel void test2(__global int* data3, __global int* data4)
{
    size_t index = get_global_id(0);
    data3[index] = index;
}
