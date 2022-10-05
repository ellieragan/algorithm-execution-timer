//code to find average execution time of an algorithm

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> //for gettimeofday()
#include <stdbool.h>
#define MAKE "make PQCgenKAT_kem"
#define RUN "./PQCgenKAT_kem"

/* functions */ 
bool parseArgs(const int argc, char* argv[]);
void chdir();

int main(int argc, char *argv[]) {
  struct timeval start, end;
  int time = 0;
  int cur_runs = 0;
  int tot_runs;
  char* dir_name = argv[1];
  FILE* fp = fopen("all_files.out", "a+");

  if (fp == NULL) {
    printf("file can't be opened\n");
  }

  if (parseArgs(argc, argv)) {
    tot_runs = atoi(argv[2]);
  }
  else {
    tot_runs = 10;
  }

  chdir(dir_name);
  system(MAKE);
  //system("pwd");

  while (cur_runs < tot_runs) {
    //printf("PQCgenKAT_kem run #%d\n", (runs + 1));
    gettimeofday(&start, NULL);
    system(RUN);
    gettimeofday(&end, NULL);

    time += ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
    cur_runs += 1;
  }

  time = time / tot_runs;
  fprintf(fp, "%s execution time: %d microseconds\n", dir_name, time);
  fclose(fp);
  return 0;
}

bool parseArgs(const int argc, char* argv[])
{
  if (argc > 3 || argc < 2) {
    fprintf(stderr, "program takes 1 or 2 arguments\n");
    exit(1);
  }

  if (argc == 2) {
    return false;
  }

  else {
    return true;
  }
}
