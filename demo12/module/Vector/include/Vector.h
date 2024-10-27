#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;
template <typename T>
class Vector
{
public:
    Vector(int size = 8);
    ~Vector();
    //在尾部添加元素
    void append(T val);
    //在尾部删除元素
    void popBack();
    //在某位置插入元素
    void insert(int pos, T val);
    //删除某位置元素
    void remove(int pos);
    //查询元素位置
    int find(T val); 
    //获取某位置元素值
    T value(int pos);
    //获取数组元素数量
    int size();
    //打印数组
    void show();
private:
    void expand(int size);
    T* m_vector; //数组的起始地址
    int m_capacity; //数组元素容量
    int m_size; //数组元素数量
};
#include "Vector.tpp"
#endif /*_VECTOR_H_*/