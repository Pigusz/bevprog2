#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include "application.hpp"
#include <string>

class CheckBox : public Widget {
protected:
    int _state; // 0 = empty, 1 = player, 2 = AI
    std::string _id;
    Application* _parent;
public:
    CheckBox(Application *parent, int x, int y, int w, int h, std::string id);
    virtual void draw() const override ;
    virtual void handle(genv::event ev) override;
    int getState() const;
    void setState(int s);
};

#endif // CHECKBOX_HPP_INCLUDED
