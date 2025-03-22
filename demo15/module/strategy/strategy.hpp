#ifndef _STRATEGY_HPP_
#define _STRATEGY_HPP_
#include <iostream>
#include <memory>

class PaymentStrategy
{
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() = default;
};

class PayPalPayment : public PaymentStrategy
{
public:
    void pay(double amount) override
    {
        std::cout << "pay by PayPal : " << amount << std::endl;
    }
};

class AlipayPayment : public PaymentStrategy
{
public:
    void pay(double amount) override
    {
        std::cout << "pay by Alipay : " << amount << std::endl;
    }  
};

class WechatPayment : public PaymentStrategy
{
public:
    void pay(double amount) override
    {
        std::cout << "pay by Wechat : " << amount << std::endl;
    } 
};

class Order
{
public:
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> paymentStrategy)
    {
        _paymentStrategy = std::move(paymentStrategy);
    }

    void checkout(double amount)
    {
        if(_paymentStrategy)
        {
            _paymentStrategy->pay(amount);
        }
        else
        {
            std::cout << "no Payment Strategy" << std::endl;
        }
    }

private:
    std::unique_ptr<PaymentStrategy> _paymentStrategy;
};

void strategy()
{
    Order order;
    double amount = 200;
    order.setPaymentStrategy(std::make_unique<PayPalPayment>());
    order.checkout(amount);
    order.setPaymentStrategy(std::make_unique<AlipayPayment>());
    order.checkout(amount);
    order.setPaymentStrategy(std::make_unique<WechatPayment>());
    order.checkout(amount);
}

#endif /*_STRATEGY_HPP_*/