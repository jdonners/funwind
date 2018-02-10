       #define UNW_LOCAL_ONLY
       #define MAXPROCLEN 40
       #include <libunwind.h>
       #include <stdio.h>

       void show_backtrace (void) {
         unw_cursor_t cursor; unw_context_t uc;
         unw_word_t offp;
         char proc[MAXPROCLEN];

         unw_getcontext(&uc);
         unw_init_local(&cursor, &uc);
         while (unw_step(&cursor) > 0) {
           unw_get_proc_name(&cursor, proc, MAXPROCLEN, &offp);
           printf ("name = %-40s  offp = %lx\n", proc, (long) offp);
         }
       }

