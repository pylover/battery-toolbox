#ifndef EXAMINE_H_
#define EXAMINE_H_


class Examine : public Dialog<Examine> {
public:
    int main() override;
protected:
    volatile bool waiting;
};


#endif  // EXAMINE_H_
