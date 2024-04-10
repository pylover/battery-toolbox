#ifndef SPLASH_H
#define SPLASH_H


class Dialog: public RotaryConsumer {
public:
    void wait();
    void pushed() override;
    int rotated(int amount) override;
protected:
    virtual void print();
private:
    volatile bool waiting;
};


class Splash: public Dialog {
public:
    static void show();
protected:
    void print() override;
};


#endif  // SPLASH_H
