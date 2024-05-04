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


template<typename T, typename U>
class NumInput: public Dialog {
public:
    NumInput(char *title, U unit, T minval, T maxval, T initial, T step,
            int precision=0);
    int main();
    int rotated(int pos) override;
    static T show(char *title, U unit, T minval, T maxval, T initial, T step,
            int precision=0);
protected:
    volatile T pos;
    char *title;
    int precision;
    U unit;
    T minval;
    T maxval;
    T step;
    void update();
};


#endif  // DIALOG_H_
