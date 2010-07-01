/**
 * Autor: Odilon Nelson Grisi Dantas
 * <odilon.nelson@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"
#include "exec.h"

int main(int argc, char *argv[]) {
  char* thisProg = argv[0];
  --argc; ++argv;
  /*in a 32-bit system, sizeof(long) == sizeof(int)
    printf("sizeof(long)=%d\n", sizeof(long));
    printf("sizeof(int)=%d\n", sizeof(int));*/
  /*do we have arguments?*/
  if (argc) { /*read from file.*/
    int ok = loadToRAM(argv[0]);
    MODE = STATUS_NORMAL;
    if (argc == 2 && (strcmp(argv[1], "--debug")==0 || strcmp(argv[1], "-d")==0)) {
      MODE = STATUS_DEBUG;
    }
    if (ok) {
      prepareM2JIT();
#ifdef TIMING
      clock_t start_clock = 0, end_clock = 0;
      double elapsed = 0;
      start_clock = clock();
#endif
      execM2();
#ifdef TIMING
      end_clock = clock();
      elapsed = ((double)(end_clock - start_clock))/CLOCKS_PER_SEC;
      printf("\nexecution time: %g\n", elapsed);
#endif
    }
    else { fprintf(stderr, "Cannot open \"%s\".\n", argv[0]); exit(-1); }
  }
  else { printf("Usage: %s <file.bin>\n", thisProg); exit(-2); }
  return 0;
}
