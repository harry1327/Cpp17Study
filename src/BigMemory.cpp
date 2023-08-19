#include"../inc/BigMemory.h"

void test(){
    // Test copy constructor
    Bigmemory A(10, "hello!");
    Bigmemory B(A);
    // Bigmemory C = A;
    //Test copy operator
    Bigmemory D(20, "hello world!");
    D = A;
    //Test move constructor
    Bigmemory E(static_cast<Bigmemory &&> (A));
    Bigmemory G(std::move(D));
    G.~Bigmemory();
    //Test move operator
    Bigmemory F;
    F = static_cast<Bigmemory &&> (B);
    return;
}

int main(){
    test();
}