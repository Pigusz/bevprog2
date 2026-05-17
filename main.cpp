#include <iostream>
#include <string>
#include <vector>

#include "application.hpp"
#include "checkbox.hpp"
#include "widgets.hpp"
#include "GameLogic.hpp"
#include "TextBox.hpp"
#include "Button.hpp"

using namespace std;
using namespace genv;

int W = 600; // Grid Width
int H = 600; // Grid Height
int G = 15;  // 15x15 Grid cells
int STATUS_H = 40; // Dedicated space for text rendering at the bottom

class MyApp : public Application
{
public:
    MyApp(int width, int height)
        : Application(width, height + STATUS_H), logic(G), gameStatus("Your turn!")
    {
        int boxSize = W / G;

        // 1. Initialize and register
        for (int r = 0; r < G; r++) {
            vector<CheckBox*> sor;
            vector<int> occsor;
            for (int c = 0; c < G; c++) {
                int posX = c * boxSize;
                int posY = r * boxSize;
                occsor.push_back(0);

                string id = to_string(r) + "_" + to_string(c);
                CheckBox* cb = new CheckBox(this, posX, posY, boxSize, boxSize, id);
                sor.push_back(cb);
            }
            grid.push_back(sor);
            occupation.push_back(occsor);
        }

        // 2. Initialize the status display
        statusDisplay = new StatusWidget(this, 20, H + 12, W - 40, STATUS_H, gameStatus);
        // 3. Initialize Buttons
        bt1 = new Button(this, 300,600, 120, STATUS_H, "Animation on", "on");
        bt2 = new Button(this, 450, 600, 120, STATUS_H, "Animation off", "off");
    }


    void action(string id) override {
    if (id == "on") {
        set_animation(true);
        return;
    }
    if (id == "off") {
        set_animation(false);
        return;
    }

    size_t delimiterPos = id.find("_");
    if (delimiterPos != string::npos) {
        int r = stoi(id.substr(0, delimiterPos));
        int c = stoi(id.substr(delimiterPos + 1));
        handlePlayerMove(r, c);
    }
}

    void handlePlayerMove(int r, int c) {
        if (occupation[r][c] != 0) return; // Prevent overwriting cells
        if (logic.evaluate(occupation) != 0) return; // Stop if game is already won

        // 1. Record Player Move
        occupation[r][c] = 1;
        grid[r][c]->setState(1);

        if (logic.evaluate(occupation) == -1000) {
            gameStatus = "Player Wins!";
            return;
        }

        gameStatus = "AI is thinking...";

        // 2. Compute and Apply AI Counter-Move
        logic.findBestMove(occupation);
        if (logic.bestRow != -1 && logic.bestCol != -1) {
            occupation[logic.bestRow][logic.bestCol] = 2;
            grid[logic.bestRow][logic.bestCol]->setState(2);
            gameStatus = "Your turn!";
        }

        if (logic.evaluate(occupation) == 1000) {
            gameStatus = "AI Wins!";
        }
    }

protected:
    vector<vector<CheckBox*>> grid;
    vector<vector<int>> occupation;
    GameLogic logic;
    string gameStatus;
    StatusWidget* statusDisplay;
    Button* bt1;
    Button* bt2;
};

int main()
{
    MyApp app(W, H);
    app.event_loop();
    return 0;
}
