#ifndef APPLICATION_HPP
#define APPLICATION_HPP

class Widget;
#include <string>
#include <vector>

class Application
{
public:
    Application(int, int);
    virtual ~Application();

    void event_loop();
    void register_widget(Widget*);

    int get_width() const;
    int get_height() const;

    bool is_animation_on() const { return _animation_on; }
    void set_animation(bool status) { _animation_on = status; }

    virtual void action(std::string) = 0;

protected:
    std::vector<Widget*> _widgets;
    int _width, _height;
    bool _animation_on = false;
};

#endif // APPLICATION_HPP
