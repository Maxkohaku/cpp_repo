#include "Search.h"
int binarySearchNorecursive(const Vector<int>& vec, int target)
{
    DEBUG_LOG("call binarySearchRecursive");
    int left = 0;
    int right = vec.size() - 1;
    while(left <= right)
    {
        int mid = (left + right) / 2;
        if( target == vec[mid])
        {
            return mid;
        }
        else if (target < vec[mid])
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
        
    }
    return -1;
}

int binarySearchRecursive(const Vector<int>& vec, int left, int right, int target)
{
    DEBUG_LOG("call binarySearchRecursive");
    int mid = (left + right) / 2;
    if( target == vec[mid])
    {
        return mid;
    }
    else if (target < vec[mid])
    {
        return binarySearchRecursive(vec, left, mid -1, target);
    }
    else
    {
        return binarySearchRecursive(vec, mid + 1,right, target);
    }
    return -1;
}