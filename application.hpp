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

        virtual void action(std::string) = 0;

protected:
    std::vector<Widget*> _widgets;
    int _width, _height;
};

#endif // APPLICATION_HPP
