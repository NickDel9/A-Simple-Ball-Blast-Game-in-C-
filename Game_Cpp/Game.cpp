#include "Game.h"
#include "graphics.h"
#include "config.h"


void Game::check_level()
{
    if (level_status == 1) { ball_points = 300; game_backround = "LEVEL1.png"; }

    if (level_status == 2) { ball_points = 400; game_backround = "LEVEL2.png"; }

    if (level_status == 3) { ball_points = 500; game_backround = "LEVEL3.png"; }

    if (level_status == 4) { ball_points = 600; game_backround = "LEVEL4.png"; }

    if (level_status == 5) { ball_points = 700; game_backround = "LEVEL5.png"; }

}

void Game::level_up()
{
    if (level_status == 1) { player->PlusLEvel(0.09f);  }
    else if (level_status == 2) { player->PlusLEvel(0.08f); }
    else if (level_status == 3) { player->PlusLEvel(0.06f); }
    else if (level_status == 4) { player->PlusLEvel(0.04f); }
    else { player->PlusLEvel(0.02f); }
}


Game::Game()
{
}

Game::~Game()
{
    if (player)
    {
        delete player;
        player = nullptr;
    }
    if (enemy)
    {
        delete enemy;
        enemy = nullptr;
    }
}

// this method spawns the main balls
void Game::OpenEnemy()
{
        for (size_t i = 0; i < 2; i++)
        {
            enemy = new Enemy(*this, (float)i*200+CANVAS_WIDTH/2 , 200 ,200, random<float>(0.1f, 0.5f), (i > 0) ? 2.0f : -2.0f, (i > 0) ? -2.0f : 2.0f);
            enemy->set_points(ball_points);
            enemylist.push_back(enemy);   
            enemy = nullptr;
        }
        enemy_list_size = enemylist.size();
        start = true;
}   

// this method spawns the children of current balls
void Game::spawnEnemy()
{   
    if (enemy_list_size > enemylist.size())
    {
        if (enemy_size == 200)
        {
            size_t s = enemylist.size();
            for (size_t i = s; i < (s+ 2); i++)
            {
                enemy = new Enemy(*this, killed_enemy_pos_x, (float)CANVAS_HEIGHT / 3 + 100, 100.0f, random<float>(0.1f, 0.5f), (i == s) ? 2.0f : -2.0f, (i == s) ? -2.0f : 2.0f);
                enemylist.push_back(enemy);
                enemylist[i]->set_points(ball_points/2);
                enemy = nullptr;
            }
        }
        else if (enemy_size == 100)
        {
            size_t s = enemylist.size();
            for (size_t i = s; i < (s+ 2); i++)
            {
                enemy = new Enemy(*this, killed_enemy_pos_x, (float)CANVAS_HEIGHT/2+75 , 75.0f , random<float>(0.1f, 0.5f), (i == s) ? 2.0f : -2.0f, (i == s) ? -2.0f : 2.0f);
                enemylist.push_back(enemy);
                enemylist[i]->set_points(ball_points /4);
                enemy = nullptr;
            }
        }
        enemy_list_size = enemylist.size();
    } 
}

// check collision between player and enemy ball
void Game::checkCollision()
{
    for (size_t i = 0; i < enemylist.size(); i++) {
        if (!player || !enemylist[i])
        {
            continue;
        }
        else {
            
            Disk d1 = player->getCollisionHull();
            Disk d2 = enemylist[i]->getCollisionHull();

            float dx = d1.cx - d2.cx;
            float dy = d1.cy - d2.cy;
            
            if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
            {
                player->set_life_condition(true);
            }
        }
    }
}

// check collision between player's bullet and enemy ball
bool Game::checkCollisionBulletvsEnemy()
{
   if (!player || !enemy)
   {
       return false;
   }
   Disk ball = player->getCollisionBullet(player_s_bullet);
   Disk d2 = enemy->getCollisionHull();

   float ballx = ball.cx - d2.cx;
   float bally = ball.cy - d2.cy;
   if (sqrt(ballx * ballx + bally * bally) < ball.radius + d2.radius)
   {
       enemy->set_points(enemy->get_points() - 1);
       score++;
       return true;
   }   
    return false;
}

void Game::updateStartScreen()
{
    graphics::MouseState ms;
    graphics::getMouseState(ms);
    mp = true;
    color_button_play = false;
    color_button_customize = false;
    help_button = false;
    sound_button = false;
    quit_button = false;

        //update play button
    if (ms.cur_pos_x > CANVAS_WIDTH / 2 + 5 - 95 && ms.cur_pos_x < CANVAS_WIDTH / 2 + 5 + 95
        && ms.cur_pos_y > CANVAS_HEIGHT / 2 - 60 && ms.cur_pos_y < CANVAS_HEIGHT / 2  + 40)
    {
        color_button_play = true;
        if (ms.button_left_released)
        {
            status = GAME_STATUS_PLAYING;
        }  
    }   
        // update customize button
    if (ms.cur_pos_x > CANVAS_WIDTH / 2 + 5 - 95 && ms.cur_pos_x < CANVAS_WIDTH / 2 + 5 + 95
        && ms.cur_pos_y > CANVAS_HEIGHT / 3 - 60 && ms.cur_pos_y < CANVAS_HEIGHT / 3 + 40)
     {
        color_button_customize = true;
        if (ms.button_left_released)
        {
            status = GAME_STATUS_CUSTOMIZE;
        }
    }

        // update help button
    if (ms.cur_pos_x > CANVAS_WIDTH / 2 + 5 - 95 && ms.cur_pos_x < CANVAS_WIDTH / 2 + 5 + 95
        && ms.cur_pos_y > CANVAS_HEIGHT / 2 + 90 && ms.cur_pos_y < CANVAS_HEIGHT / 2 + 195)
    {
        help_button = true;
        if (ms.button_left_released)
        {
            status = GAME_STATUS_HELP;   
        }
    }

    //update sound button
    if (ms.cur_pos_x > CANVAS_WIDTH  - 120 && ms.cur_pos_x < CANVAS_WIDTH -20
        && ms.cur_pos_y > CANVAS_HEIGHT - 120 && ms.cur_pos_y < CANVAS_HEIGHT -20)
    {
        sound_button = true;
        if (ms.button_left_released)
        {
            set_sound_status((_sound_status==true) ? false : true);
        }
    }

    //update quit button
    if (ms.cur_pos_x > CANVAS_WIDTH / 2 + 5 - 95 && ms.cur_pos_x < CANVAS_WIDTH / 2 + 5 + 95
        && ms.cur_pos_y > CANVAS_HEIGHT - 210 && ms.cur_pos_y < CANVAS_HEIGHT - 110)
    {
        quit_button = true;
        if (ms.button_left_released)
        {
            graphics::destroyWindow();
            exit(0);
        }
    }
}

void Game::updateLevelScreen()
{
    _win = false;
    color_button_play = false;
    color_button_customize = false;

    if (!player_initialized)
    {
        player = new Player(*this);
        player_initialized = true;
    }

    if (player)
    {
        player->update();
        if (player->get_bulletlist().size() > 0) // if player is attacking
        {
            for (size_t i = 0; i < player->get_bulletlist().size(); i++)
            {
                player->get_bulletlist()[i].set_pos_y(player->get_bulletlist()[i].get_pos_y() - player->get_bulletlist()[i].get_speed() * graphics::getDeltaTime());
             
                for (size_t j = 0; j < enemylist.size(); j++) 
                {
                        enemy = enemylist[j];
                        player_s_bullet = player->get_bulletlist()[i];
                        if (checkCollisionBulletvsEnemy())// if there is collision between a bullet and an enemy ball
                        {
                            if (enemylist[j]->get_points() <= 0) // if an enemy's life is zero then the enemy is dead
                            {
                                level_up();
                                enemy_size = enemylist[j]->get_size(); //keep the size of most recent killed enemy
                                killed_enemy_pos_x = enemylist[j]->get_pos_x(); //keep the width position of most recent killed enemy
                                delete enemylist[j];
                                enemylist[j] = nullptr;
                                enemylist.erase(enemylist.begin() + j);
                            }
                            player->get_bulletlist()[i].set_delete(true);
                        }
                        enemy = nullptr;
                }     
                if (player->get_bulletlist()[i].get_pos_y() < CANVAS_HEIGHT / 3 - 150 || player->get_bulletlist()[i].get_delete())
                {
                    player->get_bulletlist().erase(player->get_bulletlist().begin() + i);
                }                     
            }
        }
    }

    if (!start) { OpenEnemy(); }

    spawnEnemy(); // if an enemy died spawn his kids

    if (player)
    {
        if (player->getLevelState() >= 1.0f )
        {
            if (enemylist.size() == 0) 
            {
                _win = true;
                status = GAME_STATUS_END;
                delete player;
                player = nullptr;
            }
            else
            {
                final_ball = true;
            }
        }
    }

    if (player) {
        if (enemy_size == 75 && enemylist.size() == 0)
        {
            OpenEnemy();
        }
    }

    if (enemylist.size() > 0)
    {
        for (size_t i = 0; i < enemylist.size(); i++) {
            enemylist[i]->update();
        }
    }

    if (!player && graphics::getGlobalTime() > 1000)
    {
        status = GAME_STATUS_END;
        player_initialized = false;
    }

    checkCollision();

    if (player) 
    {
        if (player->get_life_condition()) {
            delete player;
            player = nullptr;
            for (size_t i = 0; i < enemylist.size(); i++) {
                delete enemylist[i];
                enemylist[i] = nullptr;
            }
            enemylist.clear();
        }
    }
}

void Game::updateEndScreen()
{
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    final_ball = false;

    if (enemylist.size() > 0)
    {
        for (size_t i = 0; i < enemylist.size(); i++)
        {
            delete enemylist[i];
            enemylist[i] = nullptr;
        }
        enemylist.clear();
    }

    //update main menu button
    end_to_main_menu = false;
    if (ms.cur_pos_x > CANVAS_WIDTH / 2  - 155 && ms.cur_pos_x < CANVAS_WIDTH / 2 + 155
        && ms.cur_pos_y > CANVAS_HEIGHT - 255  && ms.cur_pos_y < CANVAS_HEIGHT - 190)
    {
        end_to_main_menu = true;
        if (ms.button_left_released)
        {
            start = false;
            score = 0;
            init();
        }
    }
    //update retry button
    retry_button = false;
    end_to_customize_ = false;
    if (ms.cur_pos_x > CANVAS_WIDTH / 2 - 155 && ms.cur_pos_x < CANVAS_WIDTH / 2 + 155
        && ms.cur_pos_y > CANVAS_HEIGHT - 345 && ms.cur_pos_y < CANVAS_HEIGHT - 270)
    {
        retry_button = true;
        if (ms.button_left_released)
        {
            start = false;
            score = 0;
            status = GAME_STATUS_CUSTOMIZE;
            end_to_customize_ = true;
        }
    }
    //update continue button
    continue_button = false;
    if (ms.cur_pos_x > CANVAS_WIDTH / 2 - 155 && ms.cur_pos_x < CANVAS_WIDTH / 2 + 155
        && ms.cur_pos_y > CANVAS_HEIGHT - 155 && ms.cur_pos_y < CANVAS_HEIGHT - 90)
    {
        if (_win) {
            continue_button = true;
        }
        if (ms.button_left_released)
        {
            if (_win)
            {
                level_status++;
                if (level_status == 6)
                {
                    level_status = 1;
                }
                start = false;
                status = GAME_STATUS_PLAYING;
            }
        }
    }
}

void Game::updateHelpScreen()
{
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    help = false;
    if (ms.cur_pos_x > CANVAS_WIDTH / 2 - 35 && ms.cur_pos_x < CANVAS_WIDTH / 2 + 35
        && ms.cur_pos_y > CANVAS_HEIGHT - 150 && ms.cur_pos_y < CANVAS_HEIGHT - 60)
    {
        help = true;
        if (ms.button_left_released)
        {
            status = GAME_STATUS_START;
        }
    }
}

void Game::updateCustomizeScreen()
{
    player = new Player(*this);

    player_initialized = true;

    custom.update();

    if (custom.get_spaceship() == 1)
    {
        player->set_player_vector("canon2.png");
    }
    else if (custom.get_spaceship() == 2)
    {
        player->set_player_vector("spaceship.png");
    }
    else
        player->set_player_vector("spaceship1.png");

    graphics::MouseState ms;
    graphics::getMouseState(ms);

    color_button_from_customize_to_start = false;
    if (ms.cur_pos_x > CANVAS_WIDTH / 2 + 5 - 75 && ms.cur_pos_x < CANVAS_WIDTH / 2 + 5 + 75
        && ms.cur_pos_y > CANVAS_HEIGHT -250 && ms.cur_pos_y < CANVAS_HEIGHT -200 + 40)
    {
        color_button_from_customize_to_start = true;
        if (ms.button_left_released)
        {
            if (end_to_customize_) 
            {
                status = GAME_STATUS_PLAYING;
            }
            else
                status = GAME_STATUS_START;
        }
    }
}

void Game::drawStartScreen()
{
    graphics::Brush bru;
    bru.texture = std::string(ASSET_PATH) + "start_back.png";
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, bru);
    
    // play button 
    graphics::Brush brush;
    brush = BR.declare_brush_color(brush);

    // text "Play" color 
    graphics::Brush play_brush;
    play_brush = BR.declare_brush_text(play_brush);
    char inf[40];
   
    //redraw the button if pressed 
    if (color_button_play)
    {
        play_brush = BR.change_brush_text(play_brush);
        brush = BR.change_brush_color(brush);
    }
    sprintf_s(inf, "Play");
    graphics::drawText(CANVAS_WIDTH / 2 - 30, CANVAS_HEIGHT / 2 + 5, 45, inf, play_brush);

    graphics::drawRect(CANVAS_WIDTH / 2+5, CANVAS_HEIGHT / 2 - 10, 200, 100, brush);
    
    //customize cannon button 
    graphics::Brush br;
    br = BR.declare_brush_color(br);

    //text "Collection" color brush
    graphics::Brush _collection_br;
    _collection_br = BR.declare_brush_text(_collection_br);

    //redraw the button if pressed 
    if (color_button_customize)
    {
        _collection_br = BR.change_brush_text(_collection_br);
        br = BR.change_brush_color(br);
    }
    sprintf_s(inf, "Collection");
    graphics::drawText(CANVAS_WIDTH / 2 - 80, CANVAS_HEIGHT / 3 + 5, 45, inf, _collection_br);

    graphics::drawRect(CANVAS_WIDTH / 2 + 5, CANVAS_HEIGHT / 3 - 10, 200, 100, br);

    //help button
    graphics::Brush _help_button_br;
    _help_button_br = BR.declare_brush_color(_help_button_br);

    // draw text "Help" color
    graphics::Brush _help_br;
    _help_br = BR.declare_brush_text(_help_br);

    if (help_button)
    {
        _help_br = BR.change_brush_text(_help_br);
        _help_button_br = BR.change_brush_color(_help_button_br);
    }
    sprintf_s(inf, "Help");
    graphics::drawText(CANVAS_WIDTH / 2 - 30, CANVAS_HEIGHT / 2 + 160, 45, inf, _help_br);

    graphics::drawRect(CANVAS_WIDTH / 2 + 5, CANVAS_HEIGHT / 2 + 140, 200, 100, _help_button_br);


    //sound button
    graphics::Brush _sound_button_br;
    _sound_button_br = BR.declare_brush_color(_sound_button_br);

    graphics::Brush sound_br;
    sound_br.texture = std::string(ASSET_PATH) + "sound.png";
    sound_br.outline_opacity = 0.0f;
    sound_br = BR.declare_brush_text(sound_br);

    if (sound_button)
    {
        sound_br = BR.change_brush_text(sound_br);
        _sound_button_br = BR.change_brush_color(_sound_button_br);
    }

    if (get_sound_status())
    {
        sprintf_s(inf, "Enabled");
    }
    else {
        sprintf_s(inf, "Disabled");
    }

    graphics::drawText(CANVAS_WIDTH - 95, CANVAS_HEIGHT - 125, 20, inf, sound_br);

    graphics::drawRect(CANVAS_WIDTH - 70, CANVAS_HEIGHT - 70, 100, 100, _sound_button_br);

    graphics::drawRect(CANVAS_WIDTH - 70, CANVAS_HEIGHT - 70, 60, 60, sound_br);

    //quit button
    graphics::Brush _quit_button_br;
    _quit_button_br = BR.declare_brush_color(_quit_button_br);

    graphics::Brush quit_br;
    quit_br = BR.declare_brush_text(quit_br);

    if (quit_button)
    {
        quit_br = BR.change_brush_text(quit_br);
        _quit_button_br = BR.change_brush_color(_quit_button_br);
    }
    sprintf_s(inf, "Quit");
    graphics::drawText(CANVAS_WIDTH / 2 -27, CANVAS_HEIGHT - 150, 45, inf, quit_br);

    graphics::drawRect(CANVAS_WIDTH /2 +5 , CANVAS_HEIGHT - 160, 200, 100, _quit_button_br);
}

void Game::drawCustomizeScreen()
{
    graphics::Brush bru;
    bru.texture = std::string(ASSET_PATH) + "back2.png";
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, bru);
    char inf[40];
    sprintf_s(inf, "CHOOSE YOUR SPACESHIP");

    graphics::Brush bru1;
    bru1.texture = "";
    bru1.fill_color[0] = 0.0f;
    bru1.fill_color[1] = 0.0f;
    bru1.fill_color[2] = 0.0f;
    bru1.fill_secondary_color[0] = 0.4f;
    bru1.fill_secondary_color[1] = 0.3f;
    bru1.fill_secondary_color[2] = 0.7f;
    bru1.fill_opacity = 1.0f;
    bru1.outline_opacity = 0.0f;
    bru1.gradient = true;
    graphics::drawText(CANVAS_WIDTH / 2 - 175, CANVAS_HEIGHT / 3, 55, inf, bru1);

    custom.draw();

    
    graphics::Brush bru2;
    bru2.fill_color[0] = 0.0f;
    bru2.fill_color[1] = 0.0f;
    bru2.fill_color[2] = 0.0f;
    sprintf_s(inf, "current");
    
    if (custom.get_spaceship() == 1)
    {
        graphics::drawText(CANVAS_WIDTH / 3 - 20, CANVAS_HEIGHT / 2 - 55, 25, inf, bru2);
    }
    if (custom.get_spaceship() == 2)
    {
        graphics::drawText(CANVAS_WIDTH / 2 - 15, CANVAS_HEIGHT / 2 - 55, 25, inf, bru2);
    }
    if (custom.get_spaceship() == 3)
    {
        graphics::drawText(CANVAS_WIDTH / 2 + 125, CANVAS_HEIGHT / 2 - 55, 25, inf, bru2);
    }

    graphics::Brush br;
    br.texture = "";
    br.fill_color[0] = 0.0f;
    br.fill_color[1] = 0.0f;
    br.fill_color[2] = 0.0f;
    br.fill_secondary_color[0] = 0.4f;
    br.fill_secondary_color[1] = 0.3f;
    br.fill_secondary_color[2] = 0.7f;
    br.fill_opacity = 1.0f;
    br.outline_opacity = 0.0f;
    br.gradient = true;

    if (color_button_from_customize_to_start)
    {
        br.fill_secondary_color[0] = 0.0f;
        br.fill_secondary_color[1] = 0.0f;
        br.fill_secondary_color[2] = 0.0f;
        br.fill_opacity = 0.3f;
        br.outline_opacity = 1.0f;
    }
    if (end_to_customize_)
    {
        sprintf_s(inf, "PLAY");
        graphics::drawText(CANVAS_WIDTH / 2 - 55, CANVAS_HEIGHT - 200 + 20, 100, inf, br);
    }
    else
    {
        sprintf_s(inf, "OK");
        graphics::drawText(CANVAS_WIDTH / 2 - 25, CANVAS_HEIGHT - 200 + 20, 100, inf, br);
    }
}

void Game::drawHelpScreen()
{
    graphics::Brush bru;
    bru.texture = std::string(ASSET_PATH) + "help.png";
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, bru);

    graphics::Brush br;
    br = BR.declare_brush_color(br);

    if (help)
    {
        br = BR.change_brush_color(br);
    }
    char inf[40];
    sprintf_s(inf, "OK");
    graphics::drawText(CANVAS_WIDTH / 2 - 20 , CANVAS_HEIGHT - 100 +20, 50, inf, bru);

    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT -100, 70, 70, br);

}

void Game::drawLevelScreen()
{
    graphics::setFont(std::string(ASSET_PATH) + "Napolitana.otf");

    graphics::Brush br;
    br.texture = std::string(ASSET_PATH) + game_backround;
    br.outline_opacity = 0;

    //draw score
    graphics::Brush score_br;
    score_br.fill_color[0] = 1.0f;
    score_br.fill_color[1] = 1.0f;
    score_br.fill_color[2] = 1.0f;
    score_br.fill_secondary_color[0] = 0.4f;
    score_br.fill_secondary_color[1] = 1.3f;
    score_br.fill_secondary_color[2] = 0.7f;
    score_br.fill_opacity = 1.0f;
    score_br.outline_opacity = 0.0f;
    score_br.gradient = true;
    
    char inf[40];
    sprintf_s(inf, "SCORE : %d", score);
    graphics::drawText(CANVAS_WIDTH / 2 - 50, 80, 40, inf, score_br);

    //float offset = CANVAS_HEIGHT * sinf(graphics::getGlobalTime()/150.0f) / 4;

    //draw backround
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

    //draw player
    if (player)
    {
        player->draw();
    }

    //draw enemies
    if (enemylist.size() > 0)
    {
        for (int i = 0; i < enemylist.size(); i++) {
            enemylist[i]->draw();
        }
    }

    if (player)
    {
        player->set_Attack(false);
    }

    //info layer
    if (player && get_debug_mode())
    {
        char inf[40];
        sprintf_s(inf, "(%0.2f, %0.2f)", player->get_pos_x(), player->get_pos_y());
        graphics::drawText(50, 50, 40, inf, br);
    }
    //level bar
    if (final_ball) {
        sprintf_s(inf, "FINAL BALL");
        graphics::drawText(CANVAS_WIDTH / 2 - 70, 40, 40, inf, br);
    }
    else {
        graphics::Brush b;
        b.fill_color[0] = 0.0f;
        b.fill_color[1] = 0.0f;
        b.fill_color[2] = 0.0f;
        b.fill_opacity = 1.0f;

        float player_level_state = player ? player->getLevelState() : 0.0f;

        br.outline_opacity = 0.0f;
        br.fill_color[0] = 1.0f;
        br.fill_color[1] = 0.2f;
        br.fill_color[2] = 0.2f;
        br.texture = "";
        br.fill_secondary_color[0] = 1.0f * (player_level_state)+player_level_state * 0.2f;
        br.fill_secondary_color[1] = 0.2f;
        br.fill_secondary_color[2] = 0.2f * (player_level_state)+player_level_state * 1.0f;
        br.gradient = true;
        br.gradient_dir_u = 1.0f;
        br.gradient_dir_v = 0.0f;
        graphics::drawRect(CANVAS_WIDTH / 2+15 - ((1.0f - player_level_state) * 120 / 2), 30, player_level_state * 120, 20, br);

        br.outline_opacity = 1.0f;
        br.gradient = false;
        br.fill_opacity = 0.0f;
        graphics::drawRect(CANVAS_WIDTH / 2 + 15, 30, 120, 20, br);
    
        char inf2[40];
        sprintf_s(inf2,"%d", level_status);
        graphics::drawText(CANVAS_WIDTH / 2 - 65, 43, 35, inf2, b);

        if (level_status == 5) {
            sprintf_s(inf2, "END");
            graphics::drawText(CANVAS_WIDTH / 2 + 80, 43, 35, inf2, b);
        }
        else {
            sprintf_s(inf2, "%d", level_status + 1);
            graphics::drawText(CANVAS_WIDTH / 2 + 95, 43, 35, inf2, b);
        }
    }
}

void Game::drawLEndScreen()
{
    graphics::setFont(std::string(ASSET_PATH) + "end_screen.otf");

    graphics::Brush br;
    br.texture = std::string(ASSET_PATH) + "back2.png";
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

    char inf[40];
    br.fill_color[0] = 0.1f;
    br.fill_color[1] = 0.9f;
    br.fill_color[2] = 0.2f;
    br.fill_opacity =0.5f;
    sprintf_s(inf, " SCORE : %d " , score);
    graphics::drawText(CANVAS_WIDTH / 2 - 55, CANVAS_HEIGHT / 3+40, 40, inf, br);

    if (_win)
    {
        sprintf_s(inf, " You Won ! ");
    }
    else 
    {  
        // if lost draw text with red color 
        br.fill_color[0] = 1.0f;
        br.fill_color[1] = 0.0f;
        br.fill_color[2] = 0.0f;
        sprintf_s(inf, " You lost ");
    }   
    graphics::drawText(CANVAS_WIDTH / 2 - 120, CANVAS_HEIGHT / 2, 80, inf, br);

    graphics::Brush br1;
    br1 = BR.declare_brush_color(br1);
     
    graphics::Brush main_menu_br;
    main_menu_br = BR.declare_brush_text(main_menu_br);
    
    graphics::Brush _retry_br;
    _retry_br = BR.declare_brush_text(_retry_br);

    graphics::Brush _Continue_br;
    _Continue_br = BR.declare_brush_text(_Continue_br);
    
    graphics::Brush brush_Continue_button;
    brush_Continue_button = BR.declare_brush_color(brush_Continue_button);
 
    graphics::Brush brush_retry_button;
    brush_retry_button = BR.declare_brush_color(brush_retry_button);

    if (retry_button)
    {
        _retry_br = BR.change_brush_text(_retry_br);
        brush_retry_button = BR.change_brush_color(brush_retry_button);
    }

    sprintf_s(inf, "RETRY");
    graphics::drawText(CANVAS_WIDTH / 2 - 30, CANVAS_HEIGHT - 300, 40, inf, _retry_br);
    graphics::drawRect(CANVAS_WIDTH / 2 + 10, CANVAS_HEIGHT - 315, 300, 60, brush_retry_button);

    if (end_to_main_menu)
    {
        main_menu_br = BR.change_brush_text(main_menu_br);
        br1 = BR.change_brush_color(br1);
    }
    sprintf_s(inf, "MAIN MENU");
    graphics::drawText(CANVAS_WIDTH / 2 - 55, CANVAS_HEIGHT - 200, 40, inf, main_menu_br);
    graphics::drawRect(CANVAS_WIDTH / 2 + 10, CANVAS_HEIGHT - 215, 300, 60, br1);

    if (continue_button)
    {
        _Continue_br = BR.change_brush_text(_Continue_br);
        brush_Continue_button = BR.change_brush_color(brush_Continue_button);
    }

    sprintf_s(inf, "CONTINUE");
    graphics::drawText(CANVAS_WIDTH / 2 - 55, CANVAS_HEIGHT - 100, 40, inf, _Continue_br);
    graphics::drawRect(CANVAS_WIDTH / 2 + 10, CANVAS_HEIGHT - 115, 300, 60, brush_Continue_button);
}

void Game::update()
{
    check_level();
    if (status == GAME_STATUS_START)
    { 
        updateStartScreen();
    }
    else if (status == GAME_STATUS_PLAYING)
    {
        updateLevelScreen();
    }
    else if (status == GAME_STATUS_END) {
        updateEndScreen();
    }
    else if (status == GAME_STATUS_CUSTOMIZE) {
        updateCustomizeScreen();
    }
    else
        updateHelpScreen();
     
}

void Game::draw()
{
    if (status == GAME_STATUS_START)
    {
        drawStartScreen();
    }
    else if (status == GAME_STATUS_PLAYING)
    {
        drawLevelScreen();
    }
    else  if (status == GAME_STATUS_END) {
        drawLEndScreen();
    }
    else if (status == GAME_STATUS_CUSTOMIZE){
        drawCustomizeScreen();
    }
    else
        drawHelpScreen();
}

void Game::init()
{
    status = GAME_STATUS_START;
    graphics::setFont(std::string(ASSET_PATH) + "end_screen.otf");
}

float Game::windowtoCanvasX(float x)
{
    return x * CANVAS_WIDTH/(float)window_width;
}

float Game::windowtoCanvasY(float y)
{
    return y * CANVAS_HEIGHT / (float)window_height;
}