#include "customize.h"
#include "graphics.h"
#include "config.h"

void customize::update()
{
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    spaceship = false;
    spaceship1 = false;
    spaceship2 = false;

    if (ms.cur_pos_x > CANVAS_WIDTH /3 + 5 - 50 && ms.cur_pos_x < CANVAS_WIDTH / 3+ 5 + 50
        && ms.cur_pos_y > CANVAS_HEIGHT / 2 - 40 && ms.cur_pos_y < CANVAS_HEIGHT / 2 + 60)
    {
        spaceship1 = true;
        if (ms.button_left_released)
        {
            spaceship_num = 1;
        }
    }
    if (ms.cur_pos_x > CANVAS_WIDTH / 2 + 5 - 50 && ms.cur_pos_x < CANVAS_WIDTH / 2 + 5 + 50
        && ms.cur_pos_y > CANVAS_HEIGHT / 2 - 40 && ms.cur_pos_y < CANVAS_HEIGHT / 2 +60)
    {
        spaceship = true;
        if (ms.button_left_released)
        {
            spaceship_num = 2;
        }
    }
    if (ms.cur_pos_x > CANVAS_WIDTH / 2 + 5 +80 && ms.cur_pos_x < CANVAS_WIDTH / 2 + 5 + 180
        && ms.cur_pos_y > CANVAS_HEIGHT / 2 - 40 && ms.cur_pos_y < CANVAS_HEIGHT / 2 + 60)
    {
        spaceship2 = true;
        if (ms.button_left_released)
        {
            spaceship_num = 3;
        }
    }
}

void customize::draw()
{
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    br.fill_opacity = 1.0f;
    br.texture = std::string(ASSET_PATH) + "canon2.png";
    graphics::drawRect(CANVAS_WIDTH /3+10, CANVAS_HEIGHT/2 , 100, 100, br);

    br.texture = std::string(ASSET_PATH) + "spaceship.png";
    graphics::drawRect(CANVAS_WIDTH /2 +15, CANVAS_HEIGHT / 2, 100, 100, br);

    br.texture = std::string(ASSET_PATH) + "spaceship1.png";
    graphics::drawRect(CANVAS_WIDTH / 2 + 155, CANVAS_HEIGHT / 2, 80, 90, br);
    
    if (spaceship1)
    {
        br.texture = std::string(ASSET_PATH) + "shadow_of_cannon2.png";
        br.fill_color[0] = 0.3f;
        br.fill_color[1] = 0.1f;
        br.fill_color[2] = 1.0f;
        br.fill_opacity = 0.4f;
        graphics::drawRect(CANVAS_WIDTH / 3 + 10, CANVAS_HEIGHT / 2, 100,100, br);
    }
    if (spaceship)
    {
        br.texture = std::string(ASSET_PATH) + "shadow_of_cannon2.png";
        br.fill_color[0] = 0.3f;
        br.fill_color[1] = 0.1f;
        br.fill_color[2] = 1.0f;
        br.fill_opacity = 0.4f;
        graphics::drawRect(CANVAS_WIDTH / 2 + 15, CANVAS_HEIGHT / 2, 100, 100, br);
    }
    if (spaceship2)
    {
        br.texture = std::string(ASSET_PATH) + "shadow_of_cannon2.png";
        br.fill_color[0] = 0.3f;
        br.fill_color[1] = 0.1f;
        br.fill_color[2] = 1.0f;
        br.fill_opacity = 0.4f;
        graphics::drawRect(CANVAS_WIDTH / 2 + 155, CANVAS_HEIGHT / 2, 100, 100, br);
    }
}

void customize::init()
{
}
int customize::get_spaceship() const
{
    return spaceship_num;
}
customize::customize(){}
