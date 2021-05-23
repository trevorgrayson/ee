// use pytest for testing?
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>


void testOne() {
    assert(1==1);
}

int main() {
    srand(time(0));
    printf("%d\n", rand());
    testOne();
}
