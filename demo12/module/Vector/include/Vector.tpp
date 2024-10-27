#ifndef _VECTOR_TPP_
#define _VECTOR_TPP_
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

template <typename T>
Vector<T>::Vector(int size):m_capacity(size), m_size(0), m_vector(new T[size]())
{ 
    #if DEBUG
        cout << "call Vector" << endl;
    #endif
}

template <typename T>
Vector<T>::~Vector()
{
    #if DEBUG
        cout << "call ~Vector" << endl;
    #endif
    delete [] m_vector;
    m_vector = nullptr;
}

template <typename T>
void Vector<T>::expand(int size)
{
    #if DEBUG
        cout << "call expand" << endl;
    #endif
    //申请一块新内存
    T* ptr = new T[size]();
    //将旧数据拷贝到新申请的内存中
    memcpy(ptr, m_vector, sizeof(T) * m_capacity);
    //更新数组起始地址
    delete [] m_vector;
    m_vector = ptr;
    m_capacity = size;
}

//在尾部添加元素
template <typename T>
void Vector<T>::append(T val)
{
    #if DEBUG
        cout << "call append" << endl;
    #endif
    if(m_size == m_capacity)
    {
        expand(m_capacity * 2);
    }
    m_vector[m_size++] = val; 
}

//在尾部删除元素
template <typename T>
void Vector<T>::popBack()
{
    #if DEBUG
        cout << "call popBack" << endl;
    #endif
    if(!m_size)
    {
        m_size --; //尾部元素不可访问
    }
    return;
}

//在某位置插入元素
template <typename T>
void Vector<T>::insert(int pos, T val)
{
    #if DEBUG
        cout << "call insert" << endl;
    #endif
    if(pos < 0 || pos > m_size)
    {
        cout << "插入数据失败，输入是pos无效" << endl;
        return;
    }
    if(m_size == m_capacity)
    {
        expand(m_capacity * 2);
    }
    //移动元素
    for(int i = m_size - 1; i >= pos; --i)
    {
        m_vector[i+1] = m_vector[i];
    }
    m_vector[pos] = val;
    m_size++;
}

//删除某位置元素
template <typename T>
void Vector<T>::remove(int pos)
{
    #if DEBUG
        cout << "call remove" << endl;
    #endif
    if(pos < 0 || pos > m_size)
    {
        cout << "删除数据失败，输入是pos无效" << endl;
    }
    if(m_size)
    {
        for(int i = pos + 1; i < m_size; ++i)
        {
            m_vector[i-1] = m_vector[i];
        }
        m_size--;
    }
    return; 
}

//查询元素位置
template <typename T>
int Vector<T>::find(T val)
{
    #if DEBUG
        cout << "call find" << endl;
    #endif
    for(int i = 0; i < m_size; ++i)
    {
        if(m_vector[i] == val)
        {
            return i;
        }
    }
    return -1;
} 

//获取某位置元素值
template <typename T>
T Vector<T>::value(int pos)
{
    #if DEBUG
        cout << "call value" << endl;
    #endif
    assert(pos >= 0 && pos < m_size);
    if(m_size)
    {
        return m_vector[pos];
    }
    return T();  
}

//获取数组元素数量
template <typename T>
int Vector<T>::size()
{
    #if DEBUG
        cout << "call size" << endl;
    #endif
    return m_size;
}

//打印数组
template <typename T>
void Vector<T>::show()
{
    #if DEBUG
        cout << "call show" << endl;
    #endif
    for(int i = 0; i < m_size; ++i)
    {
        cout << m_vector[i] << " ";
    }
    cout << endl;
    
}
#endif /*_VECTOR_TPP_*/