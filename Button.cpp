#include "button.hpp"

using namespace genv;

Button::Button(Application* parent, int x, int y, int w, int h, std::string text, std::string action_id)
    : Widget(parent, x, y, w, h), _text(text), _action_id(action_id), _is_hovered(false)
{}

void Button::draw() const {
    if (_is_hovered) {
        gout << color(100, 100, 100);
    } else {
        gout << color(50, 50, 50);
    }

    gout << move_to(_x, _y) << box(_sx, _sy);
    gout << move_to(_x, _y) << color(255, 255, 255) << line_to(_x + _sx, _y)
         << line_to(_x + _sx, _y + _sy) << line_to(_x, _y + _sy) << line_to(_x, _y);

    int text_w = gout.twidth(_text);
    int text_h = gout.cascent() + gout.cdescent();

    int text_x = _x + (_sx - text_w) / 2;
    int text_y = _y + (_sy - text_h) / 2 + gout.cascent();

    gout << move_to(text_x, text_y) << color(255, 255, 255) << text(_text);
}

void Button::handle(event ev) {
    if (ev.pos_x >= _x && ev.pos_x <= _x + _sx && ev.pos_y >= _y && ev.pos_y <= _y + _sy) {
        _is_hovered = true;

        if (ev.type == ev_mouse && ev.button == btn_left) {
            _parent->action(_action_id);
        }
    } else {
        _is_hovered = false;
    }
}
