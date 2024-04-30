#ifndef DISCHARGE_H_
#define DISCHARGE_H_


#define DISCHARGE_PWMPIN 9


class Discharge: public Dialog<Discharge> {
public:
    int main() override;
    int rotated(int pos) override;
protected:
    volatile int duty;
private:
    int dutyloc;
};


#endif  // DISCHARGE_H_
