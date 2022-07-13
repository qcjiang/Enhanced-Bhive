#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>

static int fddev = -1;
//__attribute__((constructor)) static void
//init(void)
//{
//	printf("init...\n");
//	static struct perf_event_attr attr;
////	attr.type = PERF_TYPE_HARDWARE;
////	attr.config = PERF_COUNT_HW_CPU_CYCLES;
//	attr.type = PERF_TYPE_RAW;
//	attr.config = 0x2004;
//	fddev = syscall(__NR_perf_event_open, &attr, 0, -1, -1, 0);
//}
//
//__attribute__((destructor)) static void
//fini(void)
//{
//	printf("fini...\n");
//	close(fddev);
//}

static void
init(void)
{
	printf("init...\n");
	static struct perf_event_attr attr;
//	attr.type = PERF_TYPE_HARDWARE;
//	attr.config = PERF_COUNT_HW_CPU_CYCLES;
	attr.type = PERF_TYPE_RAW;
	attr.config = 0x0011;
    attr.exclude_kernel = 1;
    attr.exclude_hv = 1;
//    attr.precise_ip = 2;  // want to using PEBS 
	fddev = syscall(__NR_perf_event_open, &attr, 0, -1, -1, 0);
}

static void
fini(void)
{
	printf("fini...\n");
	close(fddev);
}

static inline long long
cpucycles(void)
{
	long long result = 0;
	if (read(fddev, &result, sizeof(result)) < sizeof(result)) return 0;
	return result;
}

/* Simple loop body to keep things interested. Make sure it gets inlined. */
static inline int
loop(int* __restrict__ a, int* __restrict__ b, int n)
{
    unsigned sum = 0;
    for (int i = 1; i < n; ++i)
        if(a[i] > b[i])
            sum += a[i] + 5;
    return sum;
}

void loop_n(int n){
	while(n)--n;
}

int
main(int ac, char **av)
{
    long long time_start = 0;
    long long time_end   = 0;

    int *a  = NULL;
    int *b  = NULL;
    int len = 0;
	int sum = 0;

    if (ac != 2) return -1;
    len = atoi(av[1]);
	printf("%s: len = %d\n", av[0], len);

    a = (int*)malloc(len*sizeof(*a));
    b = (int*)malloc(len*sizeof(*b));


    for (int i = 0; i < len; ++i) {
        a[i] = i+128;
        b[i] = i+64;
    }

    printf("%s: beginning loop\n", av[0]);

	init();
    time_start = cpucycles();
//    sum = loop(a, b, len);
	loop_n(10000);
    time_end   = cpucycles();
	fini();

	printf("start is %llu, end is %llu\n",time_start,time_end);
    printf("%s: done. sum = %d; time delta = %llu\n", av[0], sum, time_end - time_start);

    free(a); free(b);
    return 0;
}
