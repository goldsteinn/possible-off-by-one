#define BENCH_ATTR __attribute__((noinline, noclone, aligned(4096)))

#define COMPILER_OOE_BARRIER() asm volatile("lfence" : : : "memory")

#define _CAT(X, Y) X##Y
#define CAT(X, Y) _CAT(X, Y)


static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}


#define make_bench(func)                                                    \
    uint64_t BENCH_ATTR CAT(bench_, func)(uint32_t * start, uint32_t * end) \
    {                                                                       \
        uint64_t tstart = rdtsc();                                         \
        COMPILER_OOE_BARRIER();                                             \
        for (; start != end; start += TEST_SIZE) {                          \
            func(start, TEST_SIZE);                                         \
        }                                                                   \
        COMPILER_OOE_BARRIER();                                             \
        uint64_t tend = rdtsc();                                           \
        return tend - tstart;                                               \
    }
