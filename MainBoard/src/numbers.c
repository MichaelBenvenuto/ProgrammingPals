#include "numbers.h"

int nLength(int n){
    int c;
    for(int i = n, c = 0; i != 0; i /= 10, c++);
    return c;
}