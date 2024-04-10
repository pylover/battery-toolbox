#ifndef SPLASH_H
#define SPLASH_H


class Splash: public RotaryConsumer {
public:
    void wait();
    void pushed() override;
    int rotated(int amount) override;
private:
    volatile bool waiting;
};


#endif  // SPLASH_H
