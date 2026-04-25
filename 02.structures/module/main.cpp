#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cassert>
#include "yLog.h"
#include "Vector.hpp"
#include "Stack.hpp"
#include "LinkList.hpp"
#include "Queue.hpp"
#include "GeneralBinaryTree.hpp"
#include "CompleteBinaryTree.hpp"
#include "AVLTree.hpp"
using namespace Structures;
void funcCallVector()
{
    logger(DEBUG) << "[call_func]|" << "funcCallVector()";
    Vector<int> vec(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.show();
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);
    vec.push_back(7);
    vec.show();
    vec.pop_back();
    vec.clear();
    vec.show();
}
void funcCallStack()
{
    logger(DEBUG) << "[call_func]|" << "funcCallStack()";
    Stack<int> st(5);
    st.push(1);
    st.push(2);
    st.push(3);
    st.top();
    st.pop();
    st.top();
    st.pop();
    st.top();
    st.pop();
    // st.top();
}

void funcCallLinkList()
{
    logger(DEBUG) << "[call_func]|" << "funcCallLinkList()";
    LinkList<int> link;
    link.insertHead(1);
    link.insertHead(2);
    link.insertHead(3);
    link.show();
    link.insertTail(4);
    link.insertTail(5);
    link.insertTail(6);
    link.show();
    link.insert(0,3);
    link.show();
    link.deleteByPos(3);
    link.show();
    link.head();
}

void funcCallQueue()
{
    logger(DEBUG) << "[call_func]|" << "funcCallQueue()";
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.front();
    q.dequeue();
    q.front();
    q.dequeue();
    q.front();
    q.dequeue();
    q.front();

}

void funcCallGeneralBinaryTree()
{
    logger(DEBUG) << "[call_func]|" << "funcCallGeneralBinaryTree()";
    GeneralBinaryTree<int> gbt;
    gbt.insert(1);
    gbt.insert(2, false);
    gbt.insert(3);
    gbt.preOrder();
    gbt.inOrder();
    gbt.postOrder();
    gbt.levelOrder();
    logger(INFO) << "height:" << gbt.height();
}

void funcCallCompleteBinaryTree()
{
    logger(DEBUG) << "[call_func]|" << "funcCallCompleteBinaryTree()";
    CompleteBinaryTree<int> cbt;
    cbt.insert(1);
    cbt.insert(2);
    cbt.insert(3);
    cbt.insert(4);
    cbt.insert(5);
    logger(INFO) << "height:" << cbt.height();
    logger(INFO) << "isComplete:" << cbt.isComplete();
    cbt.preOrder();
    cbt.inOrder();
    cbt.postOrder();
}

void funcCallAVLTree()
{
    logger(DEBUG) << "[call_func]|" << "funcCallAVLTree()";
    AVLTree<int> avl;
    assert(avl.empty());
    avl.insert(8);
    avl.insert(5);
    avl.insert(10);
    avl.insert(3);
    avl.insert(13);
    assert(avl.isBalanced());
    avl.levelOrder();
    avl.remove(3);
    avl.levelOrder();  
    assert(avl.search(8));
}

int main(int argc, char *argv[])
{
    Logger::createInstance().initLogConfig(INFO);
    // funcCallVector();
    // funcCallStack();
    // funcCallLinkList();
    // funcCallQueue();
    // funcCallGeneralBinaryTree();
    // funcCallCompleteBinaryTree();
    funcCallAVLTree();
    return 0;
}