#include "TextBox.hpp"

using namespace genv;
using namespace std;

StatusWidget::StatusWidget(Application *parent, int x, int y, int w, int h, const string& textRef)
    : Widget(parent, x, y, w, h), _textRef(textRef)
{
}

void StatusWidget::draw() const {
    gout << move_to(_x, _y) << color(255, 255, 0) << text(_textRef);
}

void StatusWidget::handle(event ev) {
    // Static text doesn't need to respond to input events
}
