funwind_lib: funwind.mod libfunwind.so

funwind.mod: funwind.f90
	gfortran -c funwind.f90

libfunwind.so: trace.c
	gcc trace.c -shared -olibfunwind.so -fpic -lunwind

