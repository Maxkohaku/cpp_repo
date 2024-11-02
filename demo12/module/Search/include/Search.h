#ifndef _SEARCH_H_
#define _SEARCH_H_
#include <iostream>
#include "Vector.h"
using namespace std;

int binarySearchNorecursive(const Vector<int>& vec, int target);
int binarySearchRecursive(const Vector<int>& vec, int left, int right, int target);

#endif /*_SEARCH_H_*/