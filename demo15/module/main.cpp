#include "singleton.hpp"
#include "factory.hpp"
#include "strategy.hpp"
#include "observer.hpp"
#include "proxy.hpp"
#include "adapter.hpp"
#include "decorator.hpp"
int main()
{
    singleton();
    factoryNew();
    strategy();
    observer();
    proxy();
    adapter();
    decorator();
    return 0;
}