#include "Sort.hpp"
// 显式实例化常用类型的模板函数，以便生成 .so 文件
template void bubbleSort<int>(Vector<int>&, std::function<bool(const int&, const int&)>);
template void bubbleSort<float>(Vector<float>&, std::function<bool(const float&, const float&)>);
template void bubbleSort<double>(Vector<double>&, std::function<bool(const double&, const double&)>);
// 如果有其他类型需要实例化，可以继续添加
