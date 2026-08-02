#pragma once

#include "MarketData.hpp"
#include "Option.hpp"
#include <vector>


struct PricingResult {
    double price;
    double delta;
    double gamma;
    double theta;
};

class BinomialTreeEngine{

    public:
        explicit BinomialTreeEngine(int steps);
        [[nodiscard]] PricingResult calculate(const Option& option, const MarketData& data) const;

    private:
        int steps_;    
};