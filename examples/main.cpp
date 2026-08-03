#include <iostream>
#include <memory>
#include "MarketData.hpp"
#include "Payoff.hpp"
#include "Option.hpp"
#include "BinomialTreeEngine.hpp"

int main() {
 
    MarketData market{
        100.0,  // S0: Prix Spot = 100€
        0.05,   // r: Taux sans risque = 5%
        0.02,   // q: Dividende continu = 2%
        0.20    // sigma: Volatilité = 20%
    };


    auto payoff = std::make_shared<PayoffCall>(100.0);
    Option americanCall(payoff, 1.0, ExerciseStyle::American);


    BinomialTreeEngine pricer(1000);


    PricingResult result = pricer.calculate(americanCall, market);

    std::cout << "=== Résultats de Valorisation ===" << std::endl;
    std::cout << "Prix (American Call) : " << result.price << " €" << std::endl;
    std::cout << "Delta (Δ)            : " << result.delta << std::endl;
    std::cout << "Gamma (Γ)            : " << result.gamma << std::endl;
    std::cout << "Theta (Θ)            : " << result.theta << " par an" << std::endl;

    return 0;
}