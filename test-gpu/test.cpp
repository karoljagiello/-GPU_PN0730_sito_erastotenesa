#define CL_USE_DEPRECATED_OPENCL_2_0_APIS

#include <CL/cl.hpp>
#include <iostream>
#include <fstream>
int main()
{
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	auto platform = platforms.front();
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);


	auto device = devices.front(); //wybranie pierwszego urz¹dzenia z listy


	std::ifstream helloWorldFile("test.cl"); //zaladowanie strumienia pliku tekstowego
	std::string src(std::istreambuf_iterator<char>(helloWorldFile), (std::istreambuf_iterator<char>())); //zaladowanie zawartoœci do stringa

	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1)); //?
	
	cl::Context context(device); //urz¹dzenie mog¹ce przetwarzaæ openCL

	cl::Program program(context, sources); //stworzenie programu ze Ÿród³a i contextu

	auto err = program.build("-cl-std=CL1.2"); //budowanie, ewentualny error

	char buf[16];

	cl::Buffer memBuf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buf)); //stworzenie bufora pamiêci z flagami

	cl::Kernel kernel(program, "test", &err); //stworzenie kernela, w stringu nazwa funkcji z pliku .cl
	kernel.setArg(0, memBuf); //za³adowanie jako argumentu bufora pamiêci

	cl::CommandQueue queue(context, device); //stworzenie komendy
	queue.enqueueTask(kernel); //za³adowanie komendy
	queue.enqueueReadBuffer(memBuf, GL_TRUE, 0, sizeof(buf), buf); //odczytanie bufora danych

	std::cout << buf;
	std::cin.get();
}