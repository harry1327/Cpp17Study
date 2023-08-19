#include"../inc/virtualclass_.h"
#include<iostream>

typedef void(*func_pointer)(void);

void PrintVFTable(func_pointer* table){
	for (int i = 0; table[i] != nullptr; ++i)
	{
		printf("[%d]:%p->", i, table[i]);
		func_pointer f = table[i];
		f();
	}
	std::cout << std::endl;
}

void test_virtualclass(){
    Base base;
    std::cout<< "*********Base class*********"<<std::endl;
    std::cout<< "****************************"<<std::endl;
    std::cout<< "****************************"<<std::endl;
    std::cout<< &base << std::endl;
    // Print the first address for the virtual table.
    std::cout<< "****Base class address******"<<std::endl;
    std::cout<< (int*) &base << std::endl;
    std::cout<< (int*)*(int*) &base + 0 << std::endl;
    std::cout<< (int*)*(int*) &base + 2 << std::endl;
    std::cout<< *(int*)*(int*) &base + 4 << std::endl;
    std::cout<< "****Base class function*****"<<std::endl;
    // PrintVFTable(*(func_pointer**)&base);
    func_pointer fp = NULL;
    fp = (func_pointer)*((int*)*(int*) &base + 0);
    fp();
    fp = (func_pointer)*((int*)*(int*) &base + 2);
    fp();

    // fp = (func_pointer)*((int*)*(int*) &base + 1);
    // fp();

    Derived_1 dereved;
    std::cout<< "*********Derived class******"<<std::endl;
    std::cout<< "****************************"<<std::endl;
    std::cout<< "****************************"<<std::endl;
    std::cout<< &dereved << std::endl;
    // Print the first address for the virtual table.
    std::cout<< "****Derived class address***"<<std::endl;
    std::cout<< (int*) &dereved << std::endl;
    std::cout<< (int*)*(int*) &dereved + 0 << std::endl;
    std::cout<< (int*)*(int*) &dereved + 2 << std::endl;
    std::cout<< (int*)*(int*) &dereved + 4 << std::endl;
    std::cout<< *(int*)*(int*) &dereved + 6 << std::endl;
    std::cout<< "****Derived class function***"<<std::endl;
    // PrintVFTable(*(func_pointer**)&dereved);
    fp = (func_pointer)*((int*)*(int*) &dereved + 0);
    fp();
    fp = (func_pointer)*((int*)*(int*) &dereved + 2);
    fp();
    fp = (func_pointer)*((int*)*(int*) &dereved + 4);
    fp();
    // print_message(base);
    // print_message(dereved_);
}

