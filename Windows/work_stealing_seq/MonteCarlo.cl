__kernel void initializeSize(__global int* input, __global int* output)
{
	size_t id = get_global_id(0);
	output[id] = input[id]*2;
}
