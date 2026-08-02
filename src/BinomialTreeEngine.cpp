#include "BinomialTreeEngine.hpp"
#include <cmath>

PricingResult BinomialTreeEngine::calculate(const Option &option,
                                            const MarketData &data) const
{

    double delta_t = option.maturity() / steps_;

    double u = std::exp(data.sigma * std::sqrt(delta_t));
    double d = 1 / u;

    double d_f = std::exp(-data.r * delta_t);

    double p = (std::exp(data.r - data.q) - d) / (u - d);

    double tab[steps_ + 1];

    for (int j = 0; j < steps_ + 1; ++j)
    {

        double S = data.S0 * std::pow(u, j) * std::pow(d, steps_ - j);
        tab[j] = option.payoff(S);
    }

    for (int i = steps_; i >= 0; --i)
    {
        double V2_2 = 0.0, V2_1=0.0, V2_0=0.0, V1_1=0.0, V1_0=0.0;
        double S2_2=0.0, S2_1=0.0, S2_0=0.0;
        double gamma=0.0, theta=0.0, delta=0.0;

        S2_2 = data.S0 * std::pow(u, 2);
        S2_1 = data.S0;
        S2_0 = data.S0 * std::pow(d, 2);

        double V_cont = 0;
        for (int j = 0; j <= i; ++j)
        {

            V_cont = d_f * (p * tab[j + 1] + (1 - p) * tab[j]);

            if (option.style() == ExerciseStyle.European)
            {
                tab[j] = V_cont;
            }

            if (option.style() == ExerciseStyle.American)
            {
                double S_i_j = data.S0 * std::pow(u, i) * std::pow(d, i - j);
                tab[j] = std::max(V_cont, option.payoff(S_i_j));
            }
        }

           if (i == 2)
            {
                V2_2 = tab[2];
                V2_1 = tab[1];
                V2_0 = tab[0];

                gamma= ((V2_2-V2_1)/(S2_2-S2_1) - (V2_1-V2_0)/(S2_1-S2_0))/(0.5* (S2_2-S2_0));
                
            }
            if(i==0){
                theta = (V2_1- tab[0])/(2*delta_t);
                delta = 
            }
    }
}