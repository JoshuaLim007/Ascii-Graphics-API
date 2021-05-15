#pragma once
#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>
#include <iostream>
#include "Renderable.h"
#include "List.h"
#include <cstdint>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __unix__
#include <ncurses.h>
#endif

//#define showCursor() printf("\e[?25h")
//#define hideCursor() printf("\e[?25l")
//#define clear() printf("\e[1;1H\e[2J")
//#define gotoxy(x, y) printf("\033[%d;%dH", (y + 1), (x + 1))

using namespace std;

class Renderer
{
private:
    static Renderer *Instance;
    List<Renderable *> toRenders;
    uint_fast8_t cameraVerticalSize = 16;
    uint_fast8_t cameraHorizontalSize = 16;
    Vector2f CameraWorldPosition;

#ifdef _WIN32
    CHAR_INFO *bufScreen;
    SMALL_RECT rectWindow;
    HANDLE hConsole;
    void create_window_console(int, int, int, int);
#endif
#ifdef __unix__
#endif
    void draw_quad_material(Vector2f, const Quad &);
    void Init();

public:
    static Renderer *get_instance();
    Renderer();
    ~Renderer();
    Renderer(uint_fast8_t, uint_fast8_t);
    void add_rendereable_to_render_stack(Renderable *);
    void render();
    void screen_clear();
    void set_camera_position(Vector2f);
    Vector2f get_camera_position();
};

#endif