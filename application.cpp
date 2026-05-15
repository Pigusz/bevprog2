#include "application.hpp"
#include "widgets.hpp"

using namespace genv;

Application::Application(int w, int h)
    : _width(w), _height(h)
{
    gout.open(_width, _height);
}

Application::~Application()
{
    for (Widget *w : _widgets)
    {
        delete w;
    }
}

void Application::register_widget(Widget *w)
{
    _widgets.push_back(w);
}

void Application::event_loop()
{
    event ev;
    int focus = -1;

    gout << move_to(0, 0) << color(0,0,0) << box(_width-1, _height-1);
    for (Widget *w : _widgets)
    {
        w->draw();
    }
    gout << refresh;

    // event loop
    while(gin >> ev && ev.keycode != key_escape)
    {
        if (ev.type == ev_mouse && ev.button == btn_left)
        {
            for (size_t i=0; i<_widgets.size(); ++i)
            {
                if (_widgets[i]->is_selected(ev.pos_x, ev.pos_y))
                {
                    focus = i;
                }
            }
        }

        // handle focus element
        if (focus != -1)
        {
            _widgets[focus]->handle(ev);
        }

        // draw widgets
        gout << move_to(0, 0) << color(0,0,0) << box(_width-1, _height-1);
        for (Widget *w : _widgets)
        {
            w->draw();
        }
        gout << refresh;

    }
}

int Application::get_width() const
{
    return _width;
}

int Application::get_height() const
{
    return _height;
}
