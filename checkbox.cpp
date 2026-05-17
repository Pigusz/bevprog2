#include "checkbox.hpp"
#include <cmath>
#include <fstream>
#include <sstream>

using namespace genv;
using namespace std;

CheckBox::CheckBox(Application *parent, int x, int y, int w, int h, std::string id)
    : Widget(parent, x, y, w, h), _state(0), _id(id), _parent(parent)
{
}

void CheckBox::draw() const {
    // 1. Check if custom asset animations are active
    if (_parent && _parent->is_animation_on()) {
        std::string filename = "plain.rgbszovegfajl";
        if (_state == 1) filename = "p6.rgbszovegfajl"; // Player asset
        if (_state == 2) filename = "a6.rgbszovegfajl";     // AI asset

        std::ifstream file(filename);
        if (file.is_open()) {
            int r, g, b;
            int pixel_y = 0;
            std::string line;


            while (std::getline(file, line)) {
                std::stringstream ss(line);
                int pixel_x = 0;


                while (ss >> r >> g >> b) {

                    if (pixel_x < _sx && pixel_y < _sy) {
                        gout << move_to(_x + pixel_x, _y + pixel_y)
                             << color(r, g, b) << dot;
                    }
                    pixel_x++;
                }
                if (pixel_x > 0) {
                    pixel_y++;
                }
            }
            file.close();
            return;
        }
    }

    // 2. Fallback Default Drawing
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

void CheckBox::handle(genv::event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        if (_state == 0) {
            _parent->action(_id);
        }
    }
}


void CheckBox::setState(int s) { _state = s; }
int CheckBox::getState() const { return _state; }
