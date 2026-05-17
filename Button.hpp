#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include <string>

class Button : public Widget {
protected:
    std::string _text;
    std::string _action_id;
    bool _is_hovered;

public:
    Button(Application* parent, int x, int y, int w, int h, std::string text, std::string action_id);

    virtual void draw() const override;
    virtual void handle(genv::event ev) override;
};

#endif // BUTTON_HPP_INCLUDED
