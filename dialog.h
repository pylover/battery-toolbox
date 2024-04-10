#ifndef DIALOG_H
#define DIALOG_H


class Dialog: public RotaryConsumer {
public:
    void wait();
    void pushed() override;
    int rotated(int amount) override;
protected:
    virtual void render();
private:
    volatile bool waiting;
};


class Splash: public Dialog {
public:
    static void show();
protected:
    void render() override;
};


#endif  // DIALOG_H
