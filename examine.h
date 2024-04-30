#ifndef EXAMINE_H_
#define EXAMINE_H_


class Examine : public Window {
public:
    void show() override;
    int wait() override;
    int rotated(int pos) override;
    void pushed() override;
    static int modal() {
        Examine *e = new Examine();
        int status =e->showwait();
        delete e;
        return status;
    }
protected:
    volatile bool waiting;
};


#endif  // EXAMINE_H_
