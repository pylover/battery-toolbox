#ifndef DIALOG_H_
#define DIALOG_H_


class Dialog: public RotaryConsumer {
public:
    virtual void pushed() override;
    virtual int rotated(int pos) override;
    virtual int main();
protected:
    volatile bool active;
    static int modal(class Dialog *dialog);
};


template <class T>
class Program: public Dialog {
public:
    static int show();
};


class Message: public Dialog {
public:
    Message(char *title, char *description, struct note *melody);
    int main() override;
    static void show(char *title, char *description, struct note *melody);
protected:
    char *title;
    char *description;
    struct note *melody;
};


class NumInput: public Dialog {
public:
    NumInput(char *title, char unit, float minval, float maxval,
            float initial, float step, int precision=0);
    int main();
    int rotated(int pos) override;
    static float show(char *title, char unit, float minval, float maxval,
            float initial, float step, int precision=0);
protected:
    volatile int pos;
    char *title;
    int precision;
    char unit;
    float minval;
    float maxval;
    float step;
    void update();
};


#endif  // DIALOG_H_
