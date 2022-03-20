#include "harness.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char **argv) {
   measure_results_t res;
   int count = 100;

   int byte_size = strlen(argv[1]) / 2;
   char *pos = argv[1];
   uint64_t raw_event = (uint64_t)strtol(argv[2], NULL, 16);

   char *add_code_tsv110 = (char *)malloc(sizeof(char) * byte_size);

   for (size_t count = 0; count < byte_size; count++) {
     sscanf(pos, "%2hhx", &add_code_tsv110[count]);
     pos += 2;
   }
   if(argc >= 4){
       count = atoi(argv[3]);
   }

  measure(add_code_tsv110, byte_size, count, &res, raw_event);
}
