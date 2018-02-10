funwind
=======
funwind is a Fortran routine to print a stack trace.
It uses the libunwind library for this functionality.
It defines the interface in a Fortran module, see funwind.f90.
It could be easier to copy the interface definition to your
source file, since the module file is compiler & version dependent.

A backtrace can be printed from your Fortran program with the call:

```Fortran
  call show_backtrace
```

and compile your program with the funwind library, e.g.

```
gfortran -L{location of libfunwind.so} -lfunwind
```

Here's some example output:

```
name = __gabriel_MOD_error                       offp = db
name = __gabriel_MOD_distribution_halo_box       offp = 1d8
name = __gabriel_MOD_distribution_halo           offp = 5a
name = MAIN__                                    offp = 16f3
name = main                                      offp = 34
name = __libc_start_main                         offp = f0
name = _start                                    offp = 29
name =                                           offp = 29
```

you can then debug your code with gdb:

```bash
donners@donners-Latitude-E7240:~/Software/gabriel$ gdb .libs/bandwidth 
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
...
Reading symbols from .libs/bandwidth...done.
(gdb) list *(MAIN__ + 0x16f3)
0x402bf9 is in ex (bandwidth.f90:68).
64	  call gabriel_init
65	  
66	  call bo%init(a,(/hor*s,ver*s+1,1/),(/hor*s+s-1,ver*s+s,s/),MPI_COMM_WORLD,periodic=(/.true.,.true.,.true./))
67	  call d%halo(bo)
68	  if(vars.ge.2) then
```

Note that gdb might not indicate the exact line with the call, depending
on optimization. In the above example the call is on line 67. This executable
was compiled using gfortran 5.4 with the flags `-g -O0`.
