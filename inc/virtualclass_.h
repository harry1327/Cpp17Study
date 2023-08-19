#include<iostream>
extern void test_virtualclass();

class Base{
    virtual void A(){
        std::cout << "This is Base Class A's virtual function" << std::endl;
    }
    virtual void B(){
        std::cout << "This is Base Class B's virtual function" << std::endl;
    }
};

class Derived_1: public Base{
    void A(){
        std::cout << "This is Derived class A's function" << std::endl;
    }
    virtual void C(){
        std::cout << "This is Derived class C's virtual function" << std::endl;
    }
};