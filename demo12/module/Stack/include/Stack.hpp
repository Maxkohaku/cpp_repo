#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <iostream>

template <typename T>
class Stack
{
public:
    Stack(int num = 64):m_capacity(num),m_stack(nullptr),m_top(-1)
    {
        m_stack = new T[num];
    }
    ~Stack()
    {
        delete [] m_stack;
    }
    void push(const T& val)
    {
        if(!full())
        {
            m_stack[++m_top] = val;
        }
    }
    T pop()
    {
        if(!empty())
        {
            return m_stack[m_top--];
        }
        return T();
    }
    T peek()
    {
        if(!empty())
        {
            return m_stack[m_top];
        }
        return T();
    }
    bool empty()
    {
        return m_top == -1;
    }
    bool full()
    {
        return m_top == m_capacity - 1;
    }
private:
    T* m_stack;
    int m_top;
    int m_capacity;
};


#endif /*_STACK_HPP_*/