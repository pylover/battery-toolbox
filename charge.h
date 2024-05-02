#ifndef CHARGE_H_
#define CHARGE_H_


#define DISCHARGE_PWMPIN 9


class Charge: public Program<Charge> {
public:
    int main() override;
    int rotated(int pos) override;
protected:
    volatile int duty;
};


#endif  // CHARGE_H_
