#include "checkbox.hpp"
#include <cmath>
using namespace genv;
using namespace std;

// A magasságot (h) már nem kívülrõl kapja, hanem kiszámolja
CheckBox::CheckBox(Application *parent, int x, int y, int w, int h)
    : Widget(parent,x, y, w, h)
{
    _pressed = false;
    _player = false;
}

void CheckBox::draw() const{
    // Háttér és fókusz keret
    gout << move_to(_x, _y) << color(255, 255, 255) << box(_sx, _sy);
    gout << move_to(_x+5, _y+5) << color(0,0,0) << box(_sx-10, _sy-10);
    if (_pressed){
        if (_player){
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
            else{
                gout << color(255,255,255);
                gout << move_to(_x + 5, _y + 5) << line_to(_x + _sx - 5, _y + _sy - 5);
                gout << move_to(_x + _sx - 5, _y + 5) << line_to(_x + 5, _y + _sy - 5);
                }
            }
    }

void CheckBox::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        _pressed = true;
        _player = true;

    }

}
/*

string ListBox::value() const{
return _items[_selected_index];
}
*/
