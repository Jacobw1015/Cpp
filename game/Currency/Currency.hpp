#pragma once
#include "../DataTypes/types.hpp"
#include <iostream>


class Currency{
private:
    currencytype Money = 0;

public:
    Currency(){}
    currencytype getMoney() { return Money; }
    currencytype gainMoney(currencytype amt) { this->Money+=amt;return this->Money;}
    currencytype spendMoney(currencytype amt)
    {
        this->Money -= amt;
        if (this->Money < 0)
        {
            this->Money = 0;
        }
        return this->Money;
    }
};