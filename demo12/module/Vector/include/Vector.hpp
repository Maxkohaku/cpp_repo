#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_
#include <iostream>
#include <cstring>
#include <cassert>
#if DEBUG
    #define DEBUG_LOG(msg) std::cout << msg << std::endl
#else
    #define DEBUG_LOG(msg)
#endif
using namespace std;
template <typename T>
class Vector
{
public:
    Vector(int size = 8);
    ~Vector();
    //重载[]
    T& operator[](int pos) const;
    T& operator[](int pos);
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
    int size() const;
    //打印数组
    void show();
private:
    void expand(int size);
    T* m_vector; //数组的起始地址
    int m_capacity; //数组元素容量
    int m_size; //数组元素数量
};
template <typename T>
Vector<T>::Vector(int size):m_capacity(size), m_size(0), m_vector(new T[size]())
{ 
    DEBUG_LOG("call Vector");
}

template <typename T>
Vector<T>::~Vector()
{
   DEBUG_LOG("call ~Vector");
    delete [] m_vector;
    m_vector = nullptr;
}

template <typename T>
T& Vector<T>::operator[](int pos) const
{
   DEBUG_LOG("call operator[] const");
    if(pos < 0 || pos >= m_size)
    {
        cout << "插入数据失败，输入是pos无效" << endl;
        throw std::out_of_range("索引超出范围");
    }
    return m_vector[pos];
}

template <typename T>
T&  Vector<T>::operator[](int pos)
{
   DEBUG_LOG("call operator[]");
    if(pos < 0 || pos >= m_size)
    {
        cout << "插入数据失败，输入是pos无效" << endl;
        throw std::out_of_range("索引超出范围");
    }
    return m_vector[pos];
}

template <typename T>
void Vector<T>::expand(int size)
{
   DEBUG_LOG("call expand");
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
   DEBUG_LOG("call append");
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
   DEBUG_LOG("call popBack");
    if(m_size > 0)
    {
        --m_size; //尾部元素不可访问
    }
    return;
}

//在某位置插入元素
template <typename T>
void Vector<T>::insert(int pos, T val)
{
   DEBUG_LOG("call insert");
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
   DEBUG_LOG("call remove");
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
   DEBUG_LOG("call find");
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
   DEBUG_LOG("call value");
    assert(pos >= 0 && pos < m_size);
    if(m_size)
    {
        return m_vector[pos];
    }
    return T();  
}

//获取数组元素数量
template <typename T>
int Vector<T>::size() const
{
   DEBUG_LOG("call size");
    return m_size;
}

//打印数组
template <typename T>
void Vector<T>::show()
{
   DEBUG_LOG("call show");
    for(int i = 0; i < m_size; ++i)
    {
        cout << m_vector[i] << " ";
    }
    cout << endl;  
}
#endif /*_VECTOR_HPP_*/