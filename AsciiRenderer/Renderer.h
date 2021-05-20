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

class Renderer
{
private:
    static Renderer *Instance;
    std::vector<Renderable*> toRenders;

    uint_fast16_t m_scr_height = 800;
    uint_fast16_t m_scr_width = 800;
    Vector2f CameraWorldPosition = Vector2f::ZERO;

    CHAR_INFO *bufScreen;
    SMALL_RECT rectWindow;
    HANDLE hConsole;
    int create_window_console(int, int, int, int);
    void draw_sprite_material(Vector2f, const Sprite&);
    void Init();

public:
    static Renderer *get_instance();
    Renderer();
    ~Renderer();
    Renderer(uint_fast16_t, uint_fast16_t);
    std::vector<Renderable*>::iterator add_renderable_to_render_stack(Renderable *);
    void remove_renderable_to_render_stack(std::vector<Renderable*>::iterator);
    void render();
    void clear();
    void set_camera_position(const Vector2f&);
    Vector2f get_camera_position();
};

#endif