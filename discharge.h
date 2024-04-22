#ifndef DISCHARGE_H_
#define DISCHARGE_H_


#define DISCHARGE_PWMPIN 9


class Discharge : public Window {
public:
    int execute() override;
    int rotated(int pos) override;
    void pushed() override;
    static int show() {
        Discharge *e = new Discharge();
        int status =e->showwait();
        delete e;
        return status;
    }
protected:
    volatile bool waiting;
    volatile int duty;
};


#endif  // DISCHARGE_H_
