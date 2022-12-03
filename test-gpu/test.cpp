#define CL_USE_DEPRECATED_OPENCL_2_0_APIS

#include <CL/cl.hpp>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <array>
#include <cmath>
//int main()
//{
//	std::vector<cl::Platform> platforms;
//	cl::Platform::get(&platforms);
//
//	auto platform = platforms.front();
//	std::vector<cl::Device> devices;
//	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
//
//
//	auto device = devices.front(); //wybranie pierwszego urz�dzenia z listy
//
//
//	std::ifstream helloWorldFile("test.cl"); //zaladowanie strumienia pliku tekstowego
//	std::string src(std::istreambuf_iterator<char>(helloWorldFile), (std::istreambuf_iterator<char>())); //zaladowanie zawarto�ci do stringa
//
//	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1)); //?
//	
//	cl::Context context(device); //urz�dzenie mog�ce przetwarza� openCL
//
//	cl::Program program(context, sources); //stworzenie programu ze �r�d�a i contextu
//
//	auto err = program.build("-cl-std=CL1.2"); //budowanie, ewentualny error
//
//	char buf[16];
//
//	cl::Buffer memBuf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buf)); //stworzenie bufora pami�ci z flagami
//
//	cl::Kernel kernel(program, "test", &err); //stworzenie kernela, w stringu nazwa funkcji z pliku .cl
//	kernel.setArg(0, memBuf); //za�adowanie jako argumentu bufora pami�ci
//
//	cl::CommandQueue queue(context, device); //stworzenie komendy
//	queue.enqueueTask(kernel); //za�adowanie komendy
//	queue.enqueueReadBuffer(memBuf, GL_TRUE, 0, sizeof(buf), buf); //odczytanie bufora danych
//
//	std::cout << buf;
//	std::cin.get();
//} //kod prostego hello World

long long int read_QPC() //funkcja mierzenia czasu
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

//int main()
//{
//	long long int frequency, start, elapsed; //elementy do mierzenia czasu
//	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
//
//	std::vector<cl::Platform> platforms;
//	cl::Platform::get(&platforms);
//
//	auto platform = platforms.front();
//	std::vector<cl::Device> devices;
//	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
//
//
//	auto device = devices.front(); //wybranie pierwszego urz�dzenia z listy
//
//
//	std::ifstream helloWorldFile("processArray.cl"); //zaladowanie strumienia pliku tekstowego
//	std::string src(std::istreambuf_iterator<char>(helloWorldFile), (std::istreambuf_iterator<char>())); //zaladowanie zawarto�ci do stringa
//
//	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1)); //?
//	
//	cl::Context context(device); //urz�dzenie mog�ce przetwarza� openCL
//
//	cl::Program program(context, sources); //stworzenie programu ze �r�d�a i contextu
//
//	auto err = program.build("-cl-std=CL1.2"); //budowanie, ewentualny error
//	err = 0;
//	std::vector<int> vec(3000000, 1); //stworzenie wektora zape�nionego jedynkami
//
//	cl::Buffer inBuf(context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR, sizeof(int) * vec.size(), vec.data(), &err); //tworzenie buffora wej�ciowego, rozmiar int razy wielko�� wektora
//
//	cl::Buffer outBuf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(int) * vec.size(), nullptr, &err);
//	cl::Kernel kernel(program, "ProcessArray"); //tworzenie instancji kernela
//	err = kernel.setArg(0, inBuf); //przypisanie argument�w
//	err = kernel.setArg(1, outBuf);
//
//	cl::CommandQueue queue(context, device); //tworzenie kolejki z kontekstem i urz�dzeniem
//	err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(vec.size())); //tworzenie n- wymiarowej tablicy kerneli
//	start = read_QPC(); //start pomiaru czasu
//	err = queue.enqueueReadBuffer(outBuf, CL_FALSE, 0, sizeof(int) * vec.size(), vec.data()); //odczytanie bufowa wej�ciowego
//
//	cl::finish(); //czekanie a� sko�czy si� przetwarzanie danych
//	elapsed = read_QPC() - start; //koniec pomiaru czasu
//	std::cout << "Time [ms] = " <<std::fixed<< std::setprecision(3) << (1000.0 * elapsed) /
//		frequency << std::endl;
//	
//	std::fill(vec.begin(), vec.end(), 1);
//
//	start = read_QPC(); //start pomiaru czasu
//	for (int i = 0; i < vec.size(); i++)
//	{
//		vec[i] = vec[i] * 3;
//	}
//	elapsed = read_QPC() - start; //koniec pomiaru czasu
//	std::cout << "Time [ms] = " << std::setprecision(3) << (1000.0 * elapsed) /
//		frequency << std::endl;
//
//	std::cin.get();
//}

//int main()
//{
//	std::vector<cl::Platform> platforms;
//	cl::Platform::get(&platforms);
//
//	auto platform = platforms.front();
//	std::vector<cl::Device> devices;
//	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
//
//
//	auto device = devices.front(); //wybranie pierwszego urz�dzenia z listy
//
//
//	std::ifstream helloWorldFile("processArray.cl"); //zaladowanie strumienia pliku tekstowego
//	std::string src(std::istreambuf_iterator<char>(helloWorldFile), (std::istreambuf_iterator<char>())); //zaladowanie zawarto�ci do stringa
//
//	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1)); //?
//	
//	cl::Context context(device); //urz�dzenie mog�ce przetwarza� openCL
//
//	cl::Program program(context, sources); //stworzenie programu ze �r�d�a i contextu
//
//	auto err = program.build("-cl-std=CL1.2"); //budowanie, ewentualny error
//
//	err = 0;
//
//
//	const int rows = 3;
//	const int col = 2;
//	std::array<std::array<int, col>, rows> arr = { {{1,1},{2,2},{3,3}} };
//
//	cl::Buffer buf(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * rows * col, arr.data());
//
//	cl::Kernel kernel(program, "processMDArray");
//	err = kernel.setArg(0,buf);
//
//	cl::CommandQueue queue(context, device);
//
//	queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(col, rows));
//	queue.enqueueReadBuffer(buf, GL_TRUE, 0, sizeof(int) * rows * col, arr.data());
//
//
//	cl::finish();
//
//	std::cin.get();
//}
//void prototyp1(const cl_long N); //wszystko naraz, brak wykresliania
//void prototyp2(const cl_long N); //dzielniki po kolei, z wykreslaniem
void prototyp1(const cl_long N);
void prototyp2(const cl_long N);
void prototyp3(cl_long N);
long long int prototyp4(cl_long N); //wykreslanie dzielnikow, potem wszystko naraz
void arraytest(cl_long N);
void sizetest(cl_long N);
size_t closestDiv(long long int N);

int main()
{
	for (cl_long N = 10000000; N <= 200000000; N += 10000000)
	{
	std::cout << "Zakres do: " << N << std::endl;	
	long long int frequency;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	long long int time = 0;
		for (int i = 0; i < 5; i++)
		{
			//cl_long N = 10000000;
			//zakres od 0 do N 
			//prototyp1(N);
			//prototyp2(N);
			//prototyp3(N + 1);
			time += prototyp4(N + 1);
			//arraytest(N);
			//sizetest(N);
			//closestDiv(N);
		}
		time /= 5;
		std::cout << "Time [ms] = " << std::fixed << std::setprecision(3) << (1000.0 * time) / frequency << std::endl;
	}
}

void prototyp1(const cl_long N) //nie ma usuwania elementow, wszystkie od 2 do sqrt(N) dzielniki s� liczone
{
	std::cout << "PROTOTYP 1: ----------" << std::endl;
	long long int frequency, start, elapsed; //elementy do mierzenia czasu
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);


	//ustalenie paramter�w i tablicy
	int rootN = pow(N, 0.5);
	std::vector<int> EratosVec(N, 1);



	//ustawienia pod openCL
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	auto platform = platforms.front();
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);


	auto device = devices.front(); //wybranie pierwszego urz�dzenia z listy


	std::ifstream kernelFile("Eratostenes.cl"); //zaladowanie strumienia pliku tekstowego
	std::string src(std::istreambuf_iterator<char>(kernelFile), (std::istreambuf_iterator<char>())); //zaladowanie zawarto�ci do stringa

	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1)); //?

	cl::Context context(device); //urz�dzenie mog�ce przetwarza� openCL

	cl::Program program(context, sources); //stworzenie programu ze �r�d�a i contextu

	auto err = program.build("-cl-std=CL2.0"); //budowanie, ewentualny error
	err = 0;

	cl::Buffer Buf(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * EratosVec.size(), EratosVec.data(), &err); //tworzenie buffora wej�ciowego, rozmiar int razy wielko�� wektora

	cl::Kernel kernel(program, "prototyp11");
	err = kernel.setArg(0, Buf);
	kernel.setArg(1, N);
	kernel.setArg(2, rootN-1);
	cl::CommandQueue queue(context, device, 0, &err);
	long long int count = ((rootN - 1) * (N - 1));
	long long D = pow(count, 0.5) + 1;
	//queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(rootN+1));
	//queue.enqueueReadBuffer(Buf, CL_FALSE, 0, sizeof(int) * EratosVec.size(), EratosVec.data());
	//queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange((rootN-1)*N), cl::NDRange(N-1)); 
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(D,D));

	start = read_QPC(); //start pomiaru czasu

	queue.enqueueReadBuffer(Buf, CL_TRUE, 0, sizeof(int) * EratosVec.size(), EratosVec.data());

	cl::finish();

	elapsed = read_QPC() - start; //koniec pomiaru czasu
	std::cout << "Time [ms] = " << std::fixed << std::setprecision(3) << (1000.0 * elapsed) / frequency << std::endl;


	int liczba = 0;

	for (long int i = 2; i < N; i++)
	{
		if (EratosVec[i] == 1) liczba++;
	}
	std::cout << liczba << " <- tyle liczb pierwszych w zakresie" << std::endl;
	//std::cout << (rootN - 1) * N << "<- tyle w sumie jest work-itemow" << std::endl;
	//std::cin.get();

	//for (int index = 2; index <= rootN; index++)
	//{
	//	for (int i = 0; i < N; i++)
	//	{
	//		if (EratosVec[i] < 0)
	//		{
	//			EratosVec[i] = EratosVec[i] - 1;
	//		}
	//		else
	//		{
	//			if (i == index)
	//			{
	//				continue;
	//			}
	//			if (i % index != 0)
	//			{
	//				continue;
	//			}
	//			else
	//			{
	//				EratosVec[i] = -1;
	//			}
	//		}
	//	}
	//}

} //

void prototyp2(const cl_long N) //liczenie dzielnik�w po kolei, pomijaj�c usuni�te
{
	std::cout << "PROTOTYP 2: ----------" << std::endl;
	long long int frequency, start, elapsed; //elementy do mierzenia czasu
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);


	//ustalenie paramter�w i tablicy
	int rootN = pow(N, 0.5);
	std::vector<int> EratosVec(N, 1);



	//ustawienia pod openCL
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	auto platform = platforms.front();
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);


	auto device = devices.front(); //wybranie pierwszego urz�dzenia z listy


	std::ifstream kernelFile("Eratostenes.cl"); //zaladowanie strumienia pliku tekstowego
	std::string src(std::istreambuf_iterator<char>(kernelFile), (std::istreambuf_iterator<char>())); //zaladowanie zawarto�ci do stringa

	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1)); //?

	cl::Context context(device); //urz�dzenie mog�ce przetwarza� openCL

	cl::Program program(context, sources); //stworzenie programu ze �r�d�a i contextu

	auto err = program.build("-cl-std=CL2.0"); //budowanie, ewentualny error
	err = 0;

	std::vector<int> dividers;
	
	start = read_QPC(); //start pomiaru czasu
	cl::Buffer Buf(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * EratosVec.size(), EratosVec.data(), &err); //tworzenie buffora wej�ciowego, rozmiar int razy wielko�� wektora
	cl::Kernel kernel(program, "prototyp2");
	err = kernel.setArg(0, Buf);
	for (int i = 2; i <= rootN; i++)
	{
	
	//int i = 2;
		
		if (EratosVec[i] < 0) continue;
		else
		{
			dividers.push_back(i);
		}
		//std::cout << i << std::endl;
		
		
		kernel.setArg(1, i);
		cl::CommandQueue queue(context, device, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, &err);
		queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(N-2));
		queue.enqueueReadBuffer(Buf, CL_FALSE, 0, sizeof(int) * EratosVec.size(), EratosVec.data());
		cl::finish();
	}

	
	
	

	//queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(rootN+1));
	//queue.enqueueReadBuffer(Buf, CL_FALSE, 0, sizeof(int) * EratosVec.size(), EratosVec.data());
	//queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange((rootN-1)*N), cl::NDRange(N-1)); 

	

	

	elapsed = read_QPC() - start; //koniec pomiaru czasu
	std::cout << "Time [ms] = " << std::fixed << std::setprecision(3) << (1000.0 * elapsed) / frequency << std::endl;


	int liczba = 0;

	for (long int i = 2; i < N; i++)
	{
		if (EratosVec[i] == 1) liczba++;
	}
	std::cout << liczba << " <- tyle liczb pierwszych w zakresie" << std::endl;
	//std::cout << (rootN - 1) * N << "<- tyle w sumie jest work-itemow" << std::endl;
	

	//for (int i = 0; i < dividers.size(); i++)
	//{
	//	std::cout << dividers[i] << std::endl;
	//}
	//for (int index = 2; index <= rootN; index++)
	//{
	//	for (int i = 0; i < N; i++)
	//	{
	//		if (EratosVec[i] < 0)
	//		{
	//			EratosVec[i] = EratosVec[i] - 1;
	//		}
	//		else
	//		{
	//			if (i == index)
	//			{
	//				continue;
	//			}
	//			if (i % index != 0)
	//			{
	//				continue;
	//			}
	//			else
	//			{
	//				EratosVec[i] = -1;
	//			}
	//		}
	//	}
	//}

}

void prototyp3(cl_long N) //liczenie dzielnik�w po kolei, pomijaj�c usuni�te
{
	std::cout << "PROTOTYP 3: ----------" << std::endl;
	long long int frequency, start, elapsed; //elementy do mierzenia czasu
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);


	//ustalenie paramter�w i tablicy
	int rootN = pow(N, 0.5);
	int rootrootN = pow(rootN, 0.5);



	//ustawienia pod openCL
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	auto platform = platforms.front();
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);


	auto device = devices.front(); //wybranie pierwszego urz�dzenia z listy


	std::ifstream kernelFile("Eratostenes.cl"); //zaladowanie strumienia pliku tekstowego
	std::string src(std::istreambuf_iterator<char>(kernelFile), (std::istreambuf_iterator<char>())); //zaladowanie zawarto�ci do stringa

	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1)); //?

	cl::Context context(device); //urz�dzenie mog�ce przetwarza� openCL

	cl::Program program(context, sources); //stworzenie programu ze �r�d�a i contextu

	auto err = program.build("-cl-std=CL2.0"); //budowanie, ewentualny error
	err = 0;

	std::vector<cl_char> dividers(rootN+1, 1); //zamienic na boole

	start = read_QPC(); //start pomiaru czasu

	cl::Buffer Buf1(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_char) * dividers.size(), dividers.data(), &err); //tworzenie buffora wej�ciowego, rozmiar int razy wielko�� wektora

		//std::cout << i << std::endl;
	int element;
	int dzielnik;
	int index;
	int b = rootrootN - 1;
	//for (int i = 0; i < (rootN - 1) * (rootrootN - 1); i++)
	//{
	//	index = i;
	//	element = index / b;
	//	element += 2;
	//	dzielnik = index % b;
	//	dzielnik += 2;
	//	std::cout << "element: " << element << ", dzielnik: " << dzielnik << std::endl;
	//}

	cl::Kernel kernel(program, "prototyp11");
	err = kernel.setArg(0, Buf1);
	kernel.setArg(1, rootN); //do wywalenia
	kernel.setArg(2, rootrootN-1);
	cl::CommandQueue queue(context, device, CL_QUEUE_PROFILING_ENABLE, &err);
	err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange((rootN - 1) * (rootrootN - 1)));
	err = queue.enqueueReadBuffer(Buf1, CL_TRUE, 0, sizeof(cl_char) * dividers.size(), dividers.data());
	cl::finish();
	

	std::vector<int> divs;
	for (int i = 2; i <=rootN; i++)
	{
		if (dividers[i] > 0) divs.push_back(i);
	} //do zoptymalizowania


	//for (int i = 0; i < N * divs.size() - 2*divs.size(); i++)
	//{
	//	index = i;
	//	element = index / divs.size();
	//	element += 2;
	//	dzielnik = index % divs.size();
	//	std::cout << "element: " <<element << ", dzielnik: " << dzielnik << std::endl;
	//}
	long long int count = N * divs.size() - 2 * divs.size();
	std::vector<cl_char> results(N,1); //zamienic na boole

	cl::Buffer Buf2(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_char) * results.size(), results.data(), &err); //tworzenie buffora wej�ciowego, rozmiar int razy wielko�� wektora
	cl::Buffer Buf3(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * divs.size(), divs.data(), &err); //zamienic na tylko do odczytu

	err = queue.enqueueWriteBuffer(Buf3, true, 0, sizeof(int) * divs.size(), divs.data());

	cl::Kernel kernel2(program, "p12");
	err = kernel2.setArg(0, Buf2);
	err = kernel2.setArg(1, Buf3);
	int dSize = divs.size();
	err = kernel2.setArg(2, dSize);
	//size_t D = closestDiv(count); //do zoptymalizowania
	size_t D = dSize;
	size_t D2 = size_t(count / D); //do zmiany na n-2
	err = queue.enqueueNDRangeKernel(kernel2, cl::NullRange, cl::NDRange(D,D2), cl::NDRange(8,8));
	queue.finish();
	//elapsed = read_QPC() - start; //koniec pomiaru czasu
	//std::cout << "Time [ms] = " << std::fixed << std::setprecision(3) << (1000.0 * elapsed) / frequency << std::endl;
	//start = read_QPC();
	err = queue.enqueueReadBuffer(Buf2, CL_TRUE, 0, sizeof(cl_char) * results.size(), results.data());
	queue.finish();
	//err = queue.enqueueReadBuffer(Buf3, CL_FALSE, 0, sizeof(int) * divs.size(), divs.data());

	


	elapsed = read_QPC() - start; //koniec pomiaru czasu
	std::cout << "Time [ms] = " << std::fixed << std::setprecision(3) << (1000.0 * elapsed) / frequency << std::endl;


	int liczba = 0;

	for (long int i = 2; i < N; i++)
	{
		if (results[i] == 1) liczba++;
	}
	std::cout << liczba << " <- tyle liczb pierwszych w zakresie" << std::endl;
	//std::cout << (rootN - 1) * N << "<- tyle w sumie jest work-itemow" << std::endl;

	//std::cout << D << " <- dzielnik" << std::endl;
	//std::cout << D * D2 << " <- tyle itemow uruchomionych naraz 2" << std::endl;
	//std::cout << D * D2 - count << " <- liczba nadmiarowych w�tk�w" << std::endl;
	long long int lli = INT_MAX;
	//std::cout << lli * 2 << " <- tyle size_t max" << std::endl;
	std::cout<< "---------------" << std::endl;
	

	//std::cin.get();
}

long long int prototyp4(cl_long N) //liczenie dzielnik�w po kolei, pomijaj�c usuni�te
{
	//std::cout << "PROTOTYP 4: ---------- ";
	long long int frequency, start, elapsed; //elementy do mierzenia czasu


	//ustalenie paramter�w i tablicy
	int rootN = pow(N, 0.5); //pierwiastek z zakresu
	int rootrootN = pow(rootN, 0.5); //pierwiastek z pierwiastka z zakresu



	//ustawienia pod openCL
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	auto platform = platforms.front();
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices); //pobranie urz�dze� obs�uguj�cych GPU


	auto device = devices.front(); //wybranie pierwszego urz�dzenia z listy


	std::ifstream kernelFile("Eratostenes.cl"); //zaladowanie strumienia pliku tekstowego
	std::string src(std::istreambuf_iterator<char>(kernelFile), (std::istreambuf_iterator<char>())); //zaladowanie zawarto�ci do stringa

	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1)); //?

	cl::Context context(device); //urz�dzenie mog�ce przetwarza� openCL

	cl::Program program(context, sources); //stworzenie programu ze �r�d�a i contextu

	auto err = program.build("-cl-std=CL2.0"); //budowanie, ewentualny error
	err = 0;

	std::vector<cl_char> dividers(rootN+1, 1); //stworzenie wektora na dzielniki

	start = read_QPC(); //start pomiaru czasu

	cl::Buffer Buf1(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_char) * dividers.size(), dividers.data(), &err); //tworzenie buffora wyj�ciowego, zawieraj�cego sito do pierwiastka z zakresu

	cl::Kernel kernel(program, "prototyp11"); //nazwa funkcji z pierwszym sitem
	err = kernel.setArg(0, Buf1); //argument 1 - bufor
	kernel.setArg(1, rootrootN-1); //argument 2 - pierwiastek z pierwiastka z zakresu - 1
	cl::CommandQueue queue(context, device, 0, &err); //stworzenie kolejki
	err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange((rootN - 1) * (rootrootN - 1))); //uruchomienie kernela do obliczenia dzielnik�w do pierwiastka z zakresu (pierwiastek - 1, czyli zakres do kt�rego liczymy potrzebujemy dzielnik�w) * (pierwiastek z pierwiastka z zakresu - 1, czyli dzielniki przez kt�re podzielimy liczby do pierwiastka)
	err = queue.enqueueReadBuffer(Buf1, CL_TRUE, 0, sizeof(cl_char) * dividers.size(), dividers.data()); //odczytanie sita
	cl::finish();
	
	//elapsed = read_QPC() - start; //koniec pomiaru czasu
	//std::cout << "Time [ms] = " << std::fixed << std::setprecision(3) << (1000.0 * elapsed) / frequency << std::endl;


	std::vector<int> divs;
	for (int i = 2; i <=rootN; i++) //odczytanie wszystkich liczb pierwszych ze stworzonego sita i zapisanie ich do wektora divs
	{
		if (dividers[i] > 0) divs.push_back(i);
	} 

	std::vector<cl_char> results(N,1);  //wektor z sitem koncowym

	cl::Buffer Buf2(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_char) * results.size(), results.data(), &err); //bufor wyjsciowy
	cl::Buffer Buf3(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * divs.size(), divs.data(), &err); //bufor wej�ciowy, tablica liczb pierwszych-dzielnikow do pierwiastka z N

	err = queue.enqueueWriteBuffer(Buf3, true, 0, sizeof(int) * divs.size(), divs.data()); //zapisanie buforu wejsciowego

	cl::Kernel kernel2(program, "wersja1"); //kernel z sitem, gdy posiadamy ju� dzielniki
	err = kernel2.setArg(0, Buf2); //bufor wyj�ciowy - sito
	err = kernel2.setArg(1, Buf3); //bufor wej�ciowy - dzielniki
	int dSize = divs.size();
	int rootNeven = rootN - rootN % 2; //zmienienie pierwiastka na liczb� parzyst�, w celu zachowania (nie)parzysto�ci
	err = kernel2.setArg(2, dSize); //liczba dzielnikow-liczb pierwszych do pierwiastka z N
	err = kernel2.setArg(3, rootNeven); //pierwiastek z N
	err = queue.enqueueNDRangeKernel(kernel2, cl::NullRange, cl::NDRange((N-rootN+1)/2)); //liczba kerneli - N - rootN, poniewa� pierwiastki do rootN mamy ju� policzone, nie ma sensu liczy� ich ponownie
	err = queue.enqueueReadBuffer(Buf2, CL_TRUE, 0, sizeof(cl_char) * results.size(), results.data()); //odczytanie sita
	queue.finish();

	elapsed = read_QPC() - start; //koniec pomiaru czasu
	//std::cout << "Time [ms] = " << std::fixed << std::setprecision(3) << (1000.0 * elapsed) / frequency << std::endl;


	int liczba = 0;

	for (long int i = rootNeven+1 + 2*(rootN%2); i < N; i+=2) //sprawdzamy liczby od pierwiastka z N +1 (bo od do tego zakresu ju� sprawdzili�my, +2, je�li liczba jest nieparzysta (�eby nie zliczy� dwa razy tego samego elementu co w dzielnikach)
	{
		if (results[i] == 1)
		{
			liczba++;
			//std::cout << i << std::endl;
		}//zliczenie liczb pierwszych od pierwiastka z N, do N
	}
	//std::cout << liczba+dSize << std::endl; //suma liczb pierwszych do pierwiastka z N, i od pierwiastka z N do N

	return elapsed; //zwrot czasu 
	//std::cin.get();
}

void arraytest(cl_long N)
{
	std::cout << "TEST 1: ----------" << std::endl;
	long long int frequency, start, elapsed; //elementy do mierzenia czasu
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);


	//ustalenie paramter�w i tablicy
	std::vector<int> v1(N, 1);
	std::vector<int> v2(N, 2);



	//ustawienia pod openCL
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	auto platform = platforms.front();
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);


	auto device = devices.front(); //wybranie pierwszego urz�dzenia z listy


	std::ifstream kernelFile("Eratostenes.cl"); //zaladowanie strumienia pliku tekstowego
	std::string src(std::istreambuf_iterator<char>(kernelFile), (std::istreambuf_iterator<char>())); //zaladowanie zawarto�ci do stringa

	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1)); //?

	cl::Context context(device); //urz�dzenie mog�ce przetwarza� openCL

	
	auto err = 0;
	cl::Program program(context, sources); //stworzenie programu ze �r�d�a i contextu

	err = program.build("-cl-std=CL2.0"); //budowanie, ewentualny error

	cl::Buffer Buf(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * v1.size(), v1.data(), &err); //tworzenie buffora wej�ciowego, rozmiar int razy wielko�� wektora
	cl::Buffer Buf2(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int) * v2.size(), v2.data(), &err); //tworzenie buffora wej�ciowego, rozmiar int razy wielko�� wektora
	cl::CommandQueue queue(context, device, 0, &err);
	queue.enqueueWriteBuffer(Buf2, CL_TRUE, 0, sizeof(int) * v2.size(), v2.data());

	cl::Kernel kernel(program, "test1");

	err = kernel.setArg(0, Buf);
	err = kernel.setArg(1, Buf2);

	
 
	queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(N), cl::NDRange(32));
	//queue.enqueueReadBuffer(Buf2, CL_TRUE, 0, sizeof(int) * v2.size(), v2.data());
	queue.enqueueReadBuffer(Buf, CL_TRUE, 0, sizeof(int) * v1.size(), v1.data());
	cl::finish();

	std::vector<int> v3(N, 3);
	std::vector<int> v4(N, 5);

	cl::Buffer Buf3(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * v3.size(), v3.data(), &err); //tworzenie buffora wej�ciowego, rozmiar int razy wielko�� wektora
	cl::Buffer Buf4(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * v4.size(), v4.data(), &err);

	cl::Kernel kernel2(program, "test2");
	err = kernel2.setArg(0, Buf3);
	err = kernel2.setArg(1, Buf4);
	//err = kernel2.setArg(2, divs.size());


	err = queue.enqueueNDRangeKernel(kernel2, cl::NullRange, cl::NDRange(N), cl::NDRange(32));
	err = queue.enqueueReadBuffer(Buf3, CL_TRUE, 0, sizeof(int) * v3.size(), v3.data());
	//err = queue.enqueueReadBuffer(Buf3, CL_FALSE, 0, sizeof(int) * divs.size(), divs.data());

	cl::finish();

	std::cin.get();

}

void sizetest(cl_long N)
{
	std::cout << "TEST 1: ----------" << std::endl;
	long long int frequency, start, elapsed; //elementy do mierzenia czasu
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);


	//ustalenie paramter�w i tablicy
	std::vector<int> v1(N, 1);
	std::vector<int> v2(N, 2);
	int rootN = sqrt(N);


	//ustawienia pod openCL
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	auto platform = platforms.front();
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);


	auto device = devices.front(); //wybranie pierwszego urz�dzenia z listy


	std::ifstream kernelFile("Eratostenes.cl"); //zaladowanie strumienia pliku tekstowego
	std::string src(std::istreambuf_iterator<char>(kernelFile), (std::istreambuf_iterator<char>())); //zaladowanie zawarto�ci do stringa

	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1)); //?

	cl::Context context(device); //urz�dzenie mog�ce przetwarza� openCL

	cl::Program program(context, sources); //stworzenie programu ze �r�d�a i contextu

	auto err = program.build("-cl-std=CL2.0"); //budowanie, ewentualny error
	err = 0;

	cl::Buffer Buf(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * v1.size(), v1.data(), &err); //tworzenie buffora wej�ciowego, rozmiar int razy wielko�� wektora
	cl::Buffer Buf2(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * v2.size(), v2.data(), &err); //tworzenie buffora wej�ciowego, rozmiar int razy wielko�� wektora

	cl::Kernel kernel(program, "test1");

	err = kernel.setArg(0, Buf);
	err = kernel.setArg(1, Buf2);

	cl::CommandQueue queue(context, device, 0, &err);

	queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(rootN+1,rootN+1));
	queue.enqueueReadBuffer(Buf2, CL_TRUE, 0, sizeof(int) * v2.size(), v2.data());
	queue.enqueueReadBuffer(Buf, CL_TRUE, 0, sizeof(int) * v1.size(), v1.data());

	cl::finish();
	std::cout << "najwyzszy index/wartosc:" <<N - 1 <<"/"<<v2[N-1]<< std::endl;

	std::cout << ((rootN+1) * (rootN*1)) << " <- tyle itemow uruchomionych naraz" << std::endl;
	long long int lli = INT_MAX;
	std::cout << lli * 2 << " <- tyle size_t max" << std::endl;

	std::cin.get();
}

size_t closestDiv(long long int N)
{
	int root = sqrt(N);
	while (root>1)
	{
		if (N % root == 0) break;
		else root--;
	}
	size_t r = N / root;
	//std::cout << "znaleziono: " <<N<< ":"<<root<< "="<<r<<  std::endl;
	return r;
}