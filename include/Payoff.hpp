#pragma once


class Payoff{

    public:
        virtual ~Payoff()=default;
        [[nodiscard]] virtual double operator()(double spot) const =0;
};

class PayoffCall: public Payoff{
    public:
        explicit PayoffCall(double strike);
        [[nodiscard]] double operator()(double spot) const override;
    private:
        double strike_;

};

class PayoffPut: public Payoff{
    public:
        explicit PayoffPut(double strike);
        [[nodiscard]] double operator()(double spot) const override;

    private:
        double strike_;    
};