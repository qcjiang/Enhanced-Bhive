#include <stdio.h>
#include <stdint.h>


int add(int i, int j)
{
    int res = 0;
    asm volatile ("ADD %[result], %[input_i], %[input_j]"
      : [result] "=r" (res)
      : [input_i] "r" (i), [input_j] "r" (j)
    );
    return res;
}

void loop(int n){
	while(n)--n;
}

static inline uint64_t
read_pmccntr(void)
{
	uint64_t val;
	asm volatile("mrs %0, pmccntr_el0" : "=r"(val));
	return val;
}

static inline uint64_t
read_pmccntr_event(void)
{
	uint64_t val;
	asm volatile("mrs %0, pmevcntr0_el0" : "=r" (val));
	return val;
}

int main(void)
{
    uint64_t start, end = 0;
	
	start = read_pmccntr_event();
    loop(1000);
	end = read_pmccntr_event();

    printf("start is %lu, end is %lu, end - start is %lu\n",start,end,end - start);
}
