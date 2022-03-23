#pragma once

#include "player.h"
#include "enemy.h"
#include "customize.h"


class Game 
{
    typedef enum { GAME_STATUS_START, GAME_STATUS_PLAYING , GAME_STATUS_CUSTOMIZE , GAME_STATUS_HELP, GAME_STATUS_END} status_t;
    bool start = false;
    bool _win = false;
    bool delete_bull = false;
    graphics::Brush br;
    Player* player = nullptr;
    customize custom;
    Enemy* enemy = nullptr;
    bullet player_s_bullet;
    Brush_Buttons BR;
    bool player_initialized = false;
    bool threat_initialized = false;
    bool debug_mode = false;
    float enemy_size = 0.0f;
    size_t enemy_list_size = 0;
    float killed_enemy_pos_x = 0.0f;
    void OpenEnemy();
    void spawnEnemy();
    void checkCollision();
    bool checkCollisionBulletvsEnemy();
    status_t status = GAME_STATUS_START;
    void updateStartScreen();
    void updateLevelScreen();
    void updateEndScreen();
    void updateHelpScreen();
    bool end_to_customize_ = false;
    void updateCustomizeScreen();
    void drawStartScreen();
    bool let = false;
    void drawCustomizeScreen();
    void drawHelpScreen();
    void drawLevelScreen();
    void drawLEndScreen();
    unsigned int window_width = WINDOW_WIDTH
        , window_height = WINDOW_HEIGHT;
    std::vector<Enemy*> enemylist; // a vector for enemy* elements
    unsigned int level_status = 1; // here u can change the level status to go to the stage u want
    bool continue_button = false;
    bool mp = false;
    bool help = false;
    bool color_button_play = false;
    bool color_button_customize = false;
    bool color_button_from_customize_to_start = false;
    bool end_to_main_menu = false;
    bool retry_button = false;
    bool help_button = false;
    bool _button_sound = false;
    bool _sound_status = false;
    bool sound_button = false;
    bool killed_enemy = false;
    int score = 0;
    void check_level();
    bool final_ball = false;
    void level_up();
    std::string game_backround;
    unsigned int ball_points =0;
    unsigned int lifes = 3;
    bool quit_button = false;
public:
    bool get_sound_status() const{ return _sound_status; }
    void set_sound_status(bool status) { _sound_status = status; }
    void set_debug_mode(bool deb) { debug_mode = deb; };
    bool get_debug_mode() const { return debug_mode; }
    Game();
    ~Game();
    int get_ball_points() const { return ball_points; }
    void update(); 
    void draw();
    void init();
    unsigned int getWindowWidth() const{ return window_width; }
    unsigned int getWindowHeight() const { return window_height; }
    float windowtoCanvasX(float x);
    float windowtoCanvasY(float y);
    void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h; }
    
};
