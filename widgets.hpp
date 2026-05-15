#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"

#include "application.hpp"

class Widget
{
public:
    Widget(Application*, int, int, int, int);
    virtual ~Widget();

    virtual bool is_selected(int, int);
    virtual void draw() const = 0;
    virtual void handle(genv::event) = 0;
protected:
    Application *_parent;
    int _x, _y, _sx, _sy;
};

#endif // WIDGET_HPP
