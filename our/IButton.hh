//
// Created by maud on 21/03/17.
//

#ifndef IBUTTON_HH
#define IBUTTON_HH

class IButton
{
protected:
    int x;
    int y;
    int color;
    int width;
    int height;
public:
    virtual void click() = 0;
    virtual void display() = 0;
};

#endif //IBUTTON_HH
