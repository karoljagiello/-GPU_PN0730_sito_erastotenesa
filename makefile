serial_cpu:
	g++ -o serial_cpu serial_cpu.cpp
	./serial_cpu -n 10000000 -silent
parallel_cpu:
	mpicc -o parallel_cpu parallel_cpu.c -lm
	mpirun -np 4 ./parallel_cpu -n 10000000
