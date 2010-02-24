/**
 * Autor: Odilon Nelson Grisi Dantas
 * <odilon.nelson@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
      execM2();
    }
    else { fprintf(stderr, "Cannot open \"%s\".\n", argv[0]); exit(-1); }
  }
  else { printf("Usage: %s <file.bin>\n", thisProg); exit(-2); }
  return 0;
}
