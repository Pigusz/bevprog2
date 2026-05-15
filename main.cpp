#include <iostream>

#include "application.hpp"
#include "menu.hpp"
#include "checkbox.hpp"


using namespace std;
using namespace genv;

int W = 600;//szelesseg
int H = 600;//magassag
int G = 15;//GxG grid

class MyApp : public Application
{
public:
    MyApp(int width, int height)
        : Application(width,height)
    {
        int boxSize = W / G;

        for (int r = 0; r < G; r++) {
        vector<CheckBox*> sor;
        for (int c = 0; c < G; c++) {
            int posX = c * boxSize;
            int posY = r * boxSize;

            sor.push_back(new CheckBox(this, posX, posY, boxSize, boxSize));
        }
        grid.push_back(sor);
    }
       // bt1 = new Button(this, 100, 320, 120, 60, "Kiesik", [=](){kiesik(); update();});
       // bt2 = new Button(this, 420, 320, 120, 60, "Följut", [=](){feljut(); update();});
    }

    void action(string id)
    {

    }


    void update()
    {

    }

protected:
    vector<vector<CheckBox*>> grid;
};

int main()
{
    MyApp app(W, H);

    app.event_loop();

    return 0;
}
