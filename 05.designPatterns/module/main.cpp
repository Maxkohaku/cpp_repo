/**
 * 单一职责：一事一类
 * 开闭原则：加新不改旧
 * 里氏替换：子类替父类
 * 依赖倒置：依赖抽象不依赖细节
 * 接口隔离：小接口，不冗余
 * 迪米特：少耦合，少暴露
 */ 
#include "singleton.hpp"
#include "factory.hpp"
#include "strategy.hpp"
#include "observer.hpp"
#include "proxy.hpp"
#include "adapter.hpp"
#include "decorator.hpp"
int main()
{
    // singleton();     //单例模式：👉 全局「唯一实例」，全局共享资源
    // observer();      //观察者模式：👉 一对多「事件通知」，一方变动，自动通知所有依赖方
    // factory();    //工厂模式：👉 专门「造对象」，统一生产，隐藏创建细节
    // strategy();      //策略模式：👉 切换「算法 / 行为」，同功能多方案自由替换
    decorator();     //装饰器模式：👉 层层「加功能」，不改原类，动态叠加增强
    // proxy();         //代理模式：👉 控制「访问权限 / 加载」，隔离本体，做拦截管控
    // adapter();       //适配器模式：👉 转换「接口格式」，解决新旧代码不兼容
    return 0;
}