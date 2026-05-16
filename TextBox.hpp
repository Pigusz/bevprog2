#ifndef STATUSWIDGET_HPP_INCLUDED
#define STATUSWIDGET_HPP_INCLUDED

#include "widgets.hpp"
#include "graphics.hpp"
#include <string>

class StatusWidget : public Widget {
protected:
    const std::string& _textRef;
public:
    StatusWidget(Application *parent, int x, int y, int w, int h, const std::string& textRef);
    virtual void draw() const override;
    virtual void handle(genv::event ev) override;
};

#endif // STATUSWIDGET_HPP_INCLUDED
