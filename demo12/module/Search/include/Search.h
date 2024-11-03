#ifndef _SEARCH_H_
#define _SEARCH_H_
#include <iostream>
#include "Vector.hpp"
#if DEBUG
    #define DEBUG_LOG(msg) std::cout << msg << std::endl
#else
    #define DEBUG_LOG(msg)
#endif
using namespace std;
template class Vector<int>;
int binarySearchNorecursive(const Vector<int>& vec, int target);
int binarySearchRecursive(const Vector<int>& vec, int left, int right, int target);

#endif /*_SEARCH_H_*/