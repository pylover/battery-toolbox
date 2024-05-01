#ifndef DISCHARGE_H_
#define DISCHARGE_H_


#define DISCHARGE_PWMPIN 9


class Discharge: public Program<Discharge> {
public:
    int main() override;
    int rotated(int pos) override;
protected:
    volatile int duty;
};


#endif  // DISCHARGE_H_
