#include <stdio.h>
int main(void){
    long long int t = 1ULL<<19;
    unsigned long long j[t];
    for(long long int i = 0; i<t;i++){
        j[i] = i;
    }
    printf("%llu ",j[1ULL << 7]);
}