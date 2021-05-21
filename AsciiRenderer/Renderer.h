#pragma once
#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>
#include <iostream>
#include "Renderable.h"
#include <map>
#include <cstdint>
#include <math.h>
#include <Windows.h>
#include <chrono>
#include <ctime>

class Renderer
{
private:
    static Renderer *Instance;
    std::vector<Renderable*> toRenders;

    uint_fast16_t m_scr_height = 200;
    uint_fast16_t m_scr_width = 300;
    uint_fast8_t x_fontSize = 4;
    uint_fast8_t y_fontSize = 4;
    Vector2f CameraWorldPosition = Vector2f::ZERO;

    std::chrono::steady_clock::time_point start_time, end_time;
    double frameTime = 0.01;

    CHAR_INFO* render_buffer = NULL;
    unsigned int* render_buffer_depth = NULL;
    int currentTextX = 0;
    int currentTextY = 0;


    SMALL_RECT rectWindow;
    HANDLE hConsole;
    int create_window_console(int, int, int, int);
    void draw_sprite_material(const Renderable& toDraw);
    void Init();

public:
    static Renderer *get_instance();
    Renderer();
    ~Renderer();
    Renderer(uint_fast16_t, uint_fast16_t, uint_fast8_t, uint_fast8_t);
    void add_renderable_to_render_stack(Renderable*);
    
    void remove_renderable_to_render_stack(Renderable*);

    void setOutputTextPosition(int, int);
    template<class T>
    void outputText(T text) {
        std::ostringstream ss;
        ss << text;
        std::string s(ss.str());

        int i = 0;
        for (i = 0; i < s.size(); i++)
        {
            render_buffer[currentTextY * m_scr_width + currentTextX + i].Char.AsciiChar = s[i];
            render_buffer_depth[currentTextY * m_scr_width + currentTextX + i] = 255;
        }
        currentTextX += i;
    }

    void render();
    void clear();
    void set_camera_position(const Vector2f&);
    Vector2f get_camera_position();
};

#endif