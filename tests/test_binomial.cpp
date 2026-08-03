#include <iostream>
#include <cassert>
#include <cmath>
#include <memory>
#include "MarketData.hpp"
#include "Payoff.hpp"
#include "Option.hpp"
#include "BinomialTreeEngine.hpp"


void testHullExample() {
    MarketData data{20.0, 0.05, 0.0, 0.20};
    auto payoff = std::make_shared<PayoffCall>(21.0);
    Option call(payoff, 0.25, ExerciseStyle::European);

    BinomialTreeEngine engine(2); 
    PricingResult res = engine.calculate(call, data);

 
    assert(res.price > 0.0);
    std::cout << "[OK] testHullExample validé - Prix Call: " << res.price << " €\n";
}


void testPutCallParity() {
    MarketData data{100.0, 0.05, 0.02, 0.20};
    double strike = 100.0;
    double T = 1.0;

    auto callPayoff = std::make_shared<PayoffCall>(strike);
    auto putPayoff = std::make_shared<PayoffPut>(strike);

    Option call(callPayoff, T, ExerciseStyle::European);
    Option put(putPayoff, T, ExerciseStyle::European);

    BinomialTreeEngine engine(500);
    double callPrice = engine.calculate(call, data).price;
    double putPrice = engine.calculate(put, data).price;

    double lhs = callPrice - putPrice;
    double rhs = data.S0 * std::exp(-data.q * T) - strike * std::exp(-data.r * T);

   
    assert(std::abs(lhs - rhs) < 1e-3);
    std::cout << "[OK] testPutCallParity validé (c - p = S*e^(-qT) - K*e^(-rT))\n";
}

int main() {
    std::cout << "=== Exécution des tests unitaires Binomial Tree ===" << std::endl;
    
    testHullExample();
    testPutCallParity();
    
    std::cout << "=== Tous les tests sont passés avec succès ! ===" << std::endl;
    return 0;
}