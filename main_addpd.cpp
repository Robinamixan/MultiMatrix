#include <iostream>
#include <emmintrin.h>
#include <unistd.h>
#include <math.h>
#include <emmintrin.h>
#include <x86intrin.h>
#include <chrono>

using namespace std;

uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t) hi << 32) | lo;
}

int main() {

    double* matr1 = new double[2];
    double* matr2 = new double[2];
    for (int i = 0; i < 2; ++i) {
        matr1[i] = i;
        matr2[i] = 0;
    }

    int counts = 100000;

    __m128d a = _mm_load_pd(&matr1[0]);
    __m128d b = _mm_load_pd(&matr1[0]);
    __m128d c;
    auto start = rdtsc();

//    asm ("mov %0, %%r8" : : "r"(matr1));
//    asm ("movhpd (%%r8), %%xmm0" :);
//    asm ("movhpd (%%r8), %%xmm1" :);
//    asm ("addpd %%xmm1, %%xmm0" :);
//    asm ("movhpd %%xmm0, (%0)" : : "r"(matr2) : "memory", "%r8", "%xmm0", "%xmm1");
//
//    double  ret;
//
//    asm("mov %0, %%r8" : : "r"(matr1[2]));
//    asm("movlpd (%%r8), %%xmm0" :);
//    asm("movlpd (%%r8), %%xmm1" :);
//    asm("addpd %%xmm1, %%xmm0" :);
//    asm("movlpd %%xmm0, %0" : "=m"(ret) : : "memory", "%r8", "%xmm0", "%xmm1");


//    movapd	-368(%rbp), %xmm0
//    movaps	%xmm0, -64(%rbp)
//    movapd	-352(%rbp), %xmm0
//    movaps	%xmm0, -48(%rbp)
//    movapd	-64(%rbp), %xmm0
//    addpd	-48(%rbp), %xmm0
//    movaps	%xmm0, -336(%rbp)

//    for (int i = 0; i < counts; i++) {
//
//        c = _mm_add_pd(a, b);
//        c = _mm_add_pd(a, b);
//        c = _mm_add_pd(a, b);
//        c = _mm_add_pd(a, b);
//        c = _mm_add_pd(a, b);
//        c = _mm_add_pd(a, b);
//        c = _mm_add_pd(a, b);
//        c = _mm_add_pd(a, b);
//        c = _mm_add_pd(a, b);
//        c = _mm_add_pd(a, b);
//    }

    uint32_t a,b=5;
    asm("movl %[arg_b],%%eax\n\t"
            "incl %%eax\n\t"
    :"=a"(a):[arg_b]"m"(b)
    :"cc");
    printf("a=%d\n",int(a));

//    for (int i = 0; i < counts; ++i) {
//        c = _mm_add_pd(a, b);
//        c = _mm_add_pd(c, b);
//        c = _mm_add_pd(c, b);
//        c = _mm_add_pd(c, b);
//        c = _mm_add_pd(c, b);
//        c = _mm_add_pd(c, b);
//        c = _mm_add_pd(c, b);
//        c = _mm_add_pd(c, b);
//        c = _mm_add_pd(c, b);
//        c = _mm_add_pd(c, b);
//    }

    auto end = rdtsc();

    auto time = end-start;

    cout << "runtime = " << (float)time / counts / 10<< endl;
    return 0;
}




