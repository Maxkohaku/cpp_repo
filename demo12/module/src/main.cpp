#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Vector.hpp"
#include "Stack.hpp"
#include "Point.hpp"
#include "BinaryTree.hpp"
using namespace std;
void test_vec()
{
    Vector<int> vec;
    for(int i = 0; i < 30; ++i)
    {
        vec.append(i);
    }
    vec.show();
    cout << "Vec size = " << vec.size() << endl;
    cout << "find pos = " << vec.find(15) << endl;
}

void test_stack()
{
    Stack<int> stack;
    for(int i = 0; i < 10; ++i)
    {
        stack.push(i);
    }
    for(int i = 0; i < 10; ++i)
    {
        cout  << stack.peek() << " ";
    }
    cout << endl;
    for(int i = 0; i < 10; ++i)
    {
        cout << stack.pop() << " ";
    }
    cout << endl;
}

void test_tree()
{
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);

    tree.preOrderTraversal();
    tree.inOrderTraversal();
    tree.postOrderTraversal();
    tree.levelOrderTraveral();

    bool flag = tree.search(5);
    LOG_INFO("是否找到元素:", flag);
}

int main(int argc, char * argv[])
{
    test_tree();
    return 0;
}