#include<vector>
#include<string.h>
#include<iostream>

extern void test();

class Bigmemory{
    public:
        Bigmemory() : Bigmemory(0, nullptr) {}
        Bigmemory(int num) : Bigmemory(num, new char[num]) {}
        Bigmemory(int num, const char* str){
            num_ = num;
            str_ = new char[num];
            if(str!=0)
                strcpy(str_, str);
        }
        // Copy constructor
        Bigmemory(Bigmemory &pool){
            std::cout << "Calling the copy constructor" << std::endl; 
            num_ = pool.num_;
            str_ = new char[num_];
            if(str_ != 0)
                strcpy(str_, pool.str_);
        }
        // Move Constructor
        Bigmemory(Bigmemory &&pool) noexcept {
            std::cout << "Calling the move constructor" << std::endl; 
            num_ = pool.num_;
            str_ = pool.str_;
        }
        // Copy operator
        Bigmemory& operator =(Bigmemory &pool){
            std::cout << "Calling the copy operator" << std::endl;
            num_ = pool.num_;
            char* tmp = new char[num_];
            if(tmp != 0)
                strcpy(tmp, pool.str_);
            delete[] str_;
            str_ = tmp;
            return *this;
        }
        // Move operator
        Bigmemory&& operator = (Bigmemory &&pool){
            num_ = pool.num_;
            str_ = pool.str_;
            pool.str_ = nullptr;
            std::cout << "Calling the move operator" << std::endl;
        }
        ~Bigmemory(){
            delete []str_;
        }
    private:
        int num_;
        char* str_;
};