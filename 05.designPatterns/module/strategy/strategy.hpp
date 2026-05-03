#pragma once
#ifndef _STRATEGY_HPP_
#define _STRATEGY_HPP_
#include <iostream>
#include <string>
#include <memory>
using namespace std;
class Payment {
public:
    Payment() = default;
    virtual ~Payment() = default;
    virtual void pay(double amount) = 0;
private:
    string _name = "none";
};
class PayPal : public Payment {
public:
    void pay(double amount) override {
        cout << "pay for " << amount << " by " << _name << endl; 
    }
private:
    string _name = "PayPal";
};
class WechatPay : public Payment {
public:
    void pay(double amount) override {
        cout << "pay for " << amount << " by " << _name << endl; 
    }
private:
    string _name = "WechatPay";
};
class AliPay : public Payment {
public:
    void pay(double amount) override {
        cout << "pay for " << amount << " by " << _name << endl; 
    }
private:
    string _name = "AliPay";
};
class PayStrategy {
public:
    using PaymentStrategy = unique_ptr<Payment>;
    virtual ~PayStrategy() = default;
    void setPayment(PaymentStrategy strategy) {
        _strategy = move(strategy);
    }
    void checkout(double amount) {
        if (_strategy == nullptr)
             throw std::invalid_argument("_strategy is nullptr");
        _strategy->pay(amount);
    }
protected:
    PaymentStrategy _strategy;
};
void strategy() {
    PayStrategy payStrategy;
    double amount = 200;

    payStrategy.setPayment(make_unique<PayPal>());
    payStrategy.checkout(200);
    payStrategy.setPayment(make_unique<AliPay>());
    payStrategy.checkout(200);
    payStrategy.setPayment(make_unique<WechatPay>());
    payStrategy.checkout(200);
}
#endif /*_STRATEGY_HPP_*/