#include "checkbox.hpp"
#include <cmath>

using namespace genv;
using namespace std;

CheckBox::CheckBox(Application *parent, int x, int y, int w, int h, std::string id)
    : Widget(parent, x, y, w, h), _state(0), _id(id), _parent(parent)
{
}

void CheckBox::draw() const {
    gout << move_to(_x, _y) << color(255, 255, 255) << box(_sx, _sy);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_sx-4, _sy-4);

    if (_state == 1) { // Player (Circle)
        gout << color(255, 255, 255);
        int centerX = _x + _sx / 2;
        int centerY = _y + _sy / 2;
        int radius = _sx / 3;

        for (double t = 0; t < 2 * 3.1415; t += 0.01) {
            int px = centerX + radius * cos(t);
            int py = centerY + radius * sin(t);
            gout << move_to(px, py) << dot;
        }
    }
    else if (_state == 2) { // AI (Cross)
        gout << color(255,255,255);
        gout << move_to(_x + 5, _y + 5) << line_to(_x + _sx - 5, _y + _sy - 5);
        gout << move_to(_x + _sx - 5, _y + 5) << line_to(_x + 5, _y + _sy - 5);
    }
}

void CheckBox::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left && _state == 0) {
        _parent->action(_id); // Trigger the application action
    }
}

void CheckBox::setState(int s) { _state = s; }
int CheckBox::getState() const { return _state; }
