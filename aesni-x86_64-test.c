#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "aesni-x86_64.h"

typedef unsigned char byte;

int main(int argc, char* argv[])
{
    const unsigned int STEPS = 128;
    byte* buf = (byte*)malloc(STEPS*16+16);
    memset(buf, 0x00, 16);

    AES_KEY ekey;
    (void)aesni_set_encrypt_key(buf, 16*8, &ekey);

    double elapsed = 0.0;
    size_t total = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

    do
    {
        size_t idx = 0;
        for (unsigned int i=0; i<STEPS; ++i)
            aesni_encrypt(&buf[idx+i], &buf[idx+i+1], &ekey);
        total += 16*STEPS;
        
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        elapsed = (end.tv_sec-start.tv_sec);
    }
    while (elapsed < 3 /* seconds */);

    /* Increase precision of elapsed time */
    elapsed = ((double)end.tv_sec-start.tv_sec) +
              ((double)end.tv_nsec-start.tv_nsec) / 1000 / 1000 / 1000;

    /* CPU freq of 3300 MHz */
    const double cpuFreq = 3300.0*1000*1000;

    const double bytes = total;
    const double ghz = cpuFreq / 1000 / 1000 / 1000;
    const double mbs = bytes / elapsed / 1024 / 1024;
    const double cpb = elapsed * cpuFreq / bytes;
    
    printf("%.0f bytes\n", bytes);
    printf("%.02f mbs\n", mbs);
    printf("%.02f cpb\n", cpb);
    
    free(buf);
    
    return 0;
}