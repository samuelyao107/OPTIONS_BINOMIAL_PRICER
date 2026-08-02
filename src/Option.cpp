#include "Option.hpp"


Option::Option(std::shared_ptr<Payoff> payoff,
             double maturity, ExerciseStyle style):payoff_(std::move(payoff)), 
                                    maturity_(maturity),style_(style){}

double Option::payoff(double spot) const {
    return (*payoff_)(spot);
}      

double Option::maturity()const {
    return maturity_;
}

ExerciseStyle Option::style() const{
    return style_;
}