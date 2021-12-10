#include <stdio.h>
void int_to_bin_digit(unsigned int in, int count, int* out)
{
    unsigned int mask = 1U << (count-1);
    // 100000 ... - cont zeros
    int i;
    for (i = 0; i < count; i++) {
        //100000            //100000
        //101110 &          //011100 
        // = 100000 > 0     // = 000000 = 0
        out[i] = (in & mask) ? 1 : 0; // if (in & mask)!=0 : 1 else 0
        in <<= 1;
    }
}