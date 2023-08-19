#include"../inc/strvec.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
std::allocator<std::string> StrVec::alloc;
void StrVec::push_back(const std::string &s){
    chk_n_alloc();
    alloc.construct(first_free++, s);
}
//重新开辟空间
void StrVec::reallocate(){
    string* NewData = nullptr;
    // When there is no element in the vector.
    if(elements == nullptr || cap == nullptr || first_free == nullptr){
        // Create a new memory space 1 that can store the member.
        NewData = alloc.allocate(1);
        elements = NewData;
        first_free = NewData;
        // cap will point to the end space of the
        // new data.
        cap = NewData + 1;
        return;
    }
    // Every time double the vector size.
    NewData = alloc.allocate(size() * 2);
    // Using the uninitialized_copt to copy
    // the elements to the NewData.
    // uninitialized_copy(elements, cap, NewData);
    auto dest = NewData;
    auto src = elements;
    for(size_t i=0; i<size(); i++){
        alloc.construct(dest++, std::move(*src++));
    }
    // clear the memery.
    free();
    elements = NewData;
    first_free = dest;
    cap = elements + size() * 2;
}

//释放操作
void StrVec::free(){
    if(elements == nullptr) return;
    auto Delete = elements;
    for(size_t i; i< size(); i++){
        alloc.destroy(Delete++);
    }
    alloc.deallocate(elements, elements - cap);
    elements = nullptr;
    cap = nullptr;
    first_free = nullptr;
}

// copy指定范围的元素到新的内存中,返回新元素的地址和第一个空闲元素地址的pair
std::pair<std::string *, std::string *> StrVec::alloc_n_copy(
    const std::string *b, const std::string *e){
    string* NewData = alloc.allocate(e - b);
    string* FirstFree = uninitialized_copy(b,e,NewData);
    return {FirstFree, NewData};
}

//拷贝构造函数
StrVec::StrVec(const StrVec &strtmp){
    auto resp = alloc_n_copy(strtmp.begin(), strtmp.end());
    elements = resp.first;
    first_free = resp.first;
    cap = resp.second;
}

//拷贝赋值运算符
StrVec &StrVec::operator=(const StrVec &strtmp){
    if(this == &strtmp)
        return *this;
    auto resp = alloc_n_copy(strtmp.begin(), strtmp.end());
    //free();
    elements = resp.first;
    first_free = resp.first;
    cap = resp.second;
    return *this;
}
//析构
StrVec::~StrVec()
{
    free();
}

//抛出元素
void StrVec::pop_back(std::string &s)
{
    if (first_free == nullptr)
    {
        return;
    }

    if (size() == 1)
    {
        s = *elements;
        alloc.destroy(elements);
        first_free = nullptr;
        elements = nullptr;
        return;
    }

    s = *(--first_free);
    alloc.destroy(first_free);
}

//抛出尾部元素
void StrVec::pop_back(){
    if(elements == nullptr)
        return;
    if(size() == 1){
        alloc.destroy(elements);
        elements = nullptr;
        first_free = nullptr;
        return;
    }
    alloc.destroy(first_free--);
}

void test_strvec_old()
{
    auto str1 = StrVec();
    str1.push_back("hello zack");
    StrVec str2(str1);
    str2.push_back("hello rolin");
    StrVec str3 = str1;
    string strtmp = "k";
    str3.pop_back(strtmp);
    str3.pop_back(strtmp);
    str3.pop_back(strtmp);
}

void test_strvec()
{
    StrVec v1, v2;
    //左值赋值
    v1 = v2;
    //函数返回的是右值，
    //右值赋值会调用移动赋值
    v2 = get_vec_str();
}

//移动赋值运算符
StrVec &StrVec::operator=(StrVec &&src){
    if(this != &src){
        //释放自己的内存空间
        free();
        //接管对方的资源空间
        this->elements = src.elements;
        this->cap = src.cap;
        this->first_free = src.first_free;
        //reset the source StrVec to nullptr.
        //take over their memory.
        src.elements = src.cap = src.first_free = nullptr;
    }
    return *this;
}

StrVec get_vec_str()
{
    return StrVec();
}
