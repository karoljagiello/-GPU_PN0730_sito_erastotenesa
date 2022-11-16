__kernel                                   
void main_kernel(float alpha,     
                  __global float *A,       
                  __global float *B,       
                  __global float *C)            
{                                          
    //Get the index of the work-item       
    int index = get_local_id(0) + 2;          
    int i = get_group_id(0) + 2;          
    if(index * i < get_global_size(0) / get_num_groups(0) + 2) { 
     printf("%f", index * i ); 
       C[get_local_id(0) - 2] = 1;} 
}      