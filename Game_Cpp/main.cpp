#include "graphics.h"
#include "Game.h"
#include "config.h"

void resize(int w , int h)
{
    Game* game = reinterpret_cast<Game *>(graphics::getUserData());
    game->setWindowDimensions((unsigned int)w, (unsigned int)h);
}

void update(float ms)
{
    Game* game = reinterpret_cast<Game *>(graphics::getUserData());
    game->update();
}

// The window content drawing function.
void draw()
{
    Game* game = reinterpret_cast<Game *>(graphics::getUserData());
    game->draw();
}

int main()
{
    Game game;

    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bouncing Balls");

    graphics::setUserData(&game);

    graphics::setDrawFunction(draw);

    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);

    game.init();
    game.set_debug_mode(false); // ENABLE OR DISABLE DEBUG MODE

    graphics::startMessageLoop();

    return 0;
}