#include "widgets.hpp"
#include "application.hpp"
#include "graphics.hpp"
using namespace genv;

Widget::Widget(Application *parent,
               int x, int y, int sx, int sy)
    : _parent(parent), _x(x), _y(y), _sx(sx), _sy(sy)
{

    if (_parent)
    {
        _parent->register_widget(this);
    }
}

Widget::~Widget()
{

}

bool Widget::is_selected(int mx, int my)
{
    return _x < mx && mx < _x+_sx &&
           _y < my && my < _y+_sy ;
}
