#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class CheckBox : public Widget {
protected:
    bool _selected;
    bool _pressed;
    bool _player;
public:
    CheckBox(Application *parent,int x, int y, int w, int h);
    virtual void draw() const override ;
    virtual void handle(genv::event ev) override;
    //virtual bool is_selected(int mouse_x, int mouse_y) ;
};

#endif // CHECKBOX_HPP_INCLUDED
