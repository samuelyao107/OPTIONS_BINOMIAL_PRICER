#pragma once

#include "Payoff.hpp"
#include <memory>

enum class ExerciseStyle{
    European,
    American
};

class Option {

    public:
        Option(std::shared_ptr<Payoff> payoff,
             double maturity, ExerciseStyle style);
        
        [[nodiscard]] double payoff(double spot) const;
        [[nodiscard]] double maturity() const;
        [[nodiscard]] ExerciseStyle style() const;

    private:
            std::shared_ptr<Payoff> payoff_;
            double maturity_;
            ExerciseStyle style_;
};