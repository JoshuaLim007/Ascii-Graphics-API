#include "Renderer.h"
#include "InputManager.h"
#include <algorithm>

Renderer *Renderer::Instance = NULL;
Renderer::Renderer()
{
    Init();
}
Renderer::Renderer(uint_fast16_t camVerticalSize, uint_fast16_t camHorizontalSize, uint_fast8_t fontX, uint_fast8_t fontY)
{
    m_scr_height = camVerticalSize;
    m_scr_width = camHorizontalSize;
    x_fontSize = fontX;
    y_fontSize = fontY;
    Init();
}
void Renderer::Init()
{
    if (Instance == NULL)
    {
        Instance = this;
    }
    else {
        throw std::runtime_error("Renderer Instance Exists!");
        return;
    }
    create_window_console(m_scr_width, m_scr_height, x_fontSize, y_fontSize);
}

int Renderer::create_window_console(int width, int height, int fontw, int fonth)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    rectWindow = {0, 0, 1, 1};
    if (!SetConsoleWindowInfo(hConsole, TRUE, &rectWindow)) {
        throw std::runtime_error("SetConsoleWindowInfo");
        return -1;
    }

    COORD coord = {(short)m_scr_width, (short)m_scr_height};
    
    if (!SetConsoleScreenBufferSize(hConsole, coord)) {
        throw std::runtime_error("SetConsoleScreenBufferSize");
        return -1;
    }

    if (!SetConsoleActiveScreenBuffer(hConsole)) {
        throw std::runtime_error("SetConsoleActiveScreenBuffer");
        return -1;
    }

#pragma region Font
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = fontw;
    cfi.dwFontSize.Y = fonth;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    if (!SetCurrentConsoleFontEx(hConsole, false, &cfi)) {
        throw std::runtime_error("SetCurrentConsoleFontEx");
    }
#pragma endregion

#pragma region WindowSet
    rectWindow = { 0, 0, (short)m_scr_width - 1, (short)m_scr_height - 1 };
    if (!SetConsoleWindowInfo(hConsole, TRUE, &rectWindow)) {
        throw std::runtime_error("SetConsoleWindowInfo");
        return -1;
    }
    if (!SetConsoleMode(hConsole, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT)) {
        throw std::runtime_error("SetConsoleMode");
        return -1;
    }
#pragma endregion

#pragma region Cursor
    CONSOLE_CURSOR_INFO ConCurInf;
    ConCurInf.bVisible = false;
    ConCurInf.dwSize = 100;
    if (!SetConsoleCursorInfo(hConsole, &ConCurInf)) {
        throw std::runtime_error("SetConsoleCursorInfo");
        return -1;
    }
#pragma endregion

    render_buffer = new CHAR_INFO[m_scr_width * m_scr_height];
    render_buffer_depth = new unsigned int[m_scr_width * m_scr_height];
    //bufScreen = new CHAR_INFO[m_scr_width * m_scr_height];
    memset(render_buffer, 0, sizeof(CHAR_INFO) * m_scr_width * m_scr_height);
    memset(render_buffer_depth, 0, sizeof(unsigned int) * m_scr_width * m_scr_height);

    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX); //prevent from being resized

    return 0;
}

Renderer::~Renderer()
{
    delete[] render_buffer;
    delete[] render_buffer_depth;
    clear();
}
Renderer *Renderer::get_instance()
{
    return Instance;
}
void Renderer::render()
{
    setOutputTextPosition(1, 1);
    outputText(1/frameTime);
    outputText(" FPS");
    setOutputTextPosition(1, 2);
    outputText(frameTime);
    outputText(" MS");

    Input::Tick();
    for (auto it : toRenders) {
        it->on_preRender(frameTime);
        draw_sprite_material(*it);
    }

    WriteConsoleOutput(hConsole, render_buffer, {(short)m_scr_width, (short)m_scr_height}, {0, 0}, &rectWindow);
    end_time = std::chrono::high_resolution_clock::now();
    auto t = (end_time - start_time);
    frameTime = t.count() / 1000000000.0;

}
void Renderer::setOutputTextPosition(int x, int y) {
    currentTextX = x;
    currentTextY = y;
}
void Renderer::clear()
{   
    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < m_scr_height * m_scr_width; i++)
    {
        render_buffer[i].Char.AsciiChar = ' ';
        render_buffer[i].Attributes = 0x000F;
        render_buffer_depth[i] = 0;
    }
    //WriteConsoleOutput(hConsole, render_buffer, {(short)m_scr_width, (short)m_scr_height}, {0, 0}, &rectWindow);
}
void Renderer::set_camera_position(const Vector2f& pos)
{
    CameraWorldPosition = pos;
}
Vector2f Renderer::get_camera_position()
{
    return CameraWorldPosition;
}
void Renderer::add_renderable_to_render_stack(Renderable *renderObject)
{
    toRenders.push_back(renderObject);
}
void Renderer::remove_renderable_to_render_stack(Renderable* renderObject)
{   
    auto removed = std::remove(toRenders.begin(), toRenders.end(), renderObject);
    toRenders.erase(removed, toRenders.end());
}
char Renderer::translate_lc(float luminance) {
    luminance *= 10;
    if (luminance > 10) {
        luminance = 10;
    }
    else if (luminance < 0) {
        luminance = 0;
    }
    return shadeLookUp[(int)luminance];
}
void Renderer::draw_sprite_material(const Renderable& toDraw)
{
    //0 - 200
    //0 - 300
    
    //world space locations
    Vector2f wp(toDraw.WorldPosition.x, -toDraw.WorldPosition.y);
    Vector2f cp(CameraWorldPosition.x, -CameraWorldPosition.y);


    auto position = wp + toDraw.get_material().LocalSpacePosition - cp + Vector2f(m_scr_width * 0.5, m_scr_height * 0.5);
    float scalerX = toDraw.Scale.x * 0.5;
    float scalerY = toDraw.Scale.y * 0.5;

    float wsprite = toDraw.get_material().width();
    float hsprite = toDraw.get_material().height();
    int maxIndexSprite = wsprite * hsprite;

    float leftBound = position.x - wsprite * scalerX;
    float rightBound = position.x + wsprite * scalerX;
    float upBound = position.y - hsprite * scalerY;
    float downBound = position.y + hsprite * scalerY;

    float xDelta = wsprite / (rightBound - leftBound);
    float yDelta = hsprite / (downBound - upBound);
    
    auto texture = toDraw.get_material().get_texture();

    float sy = 0;
    for (int y = upBound; y < downBound; y++)
    {
        float sx = 0;
        for (int x = leftBound; x < rightBound; x++)
        {
            if (y >= 0 && y < m_scr_height && x >= 0 && x < m_scr_width) {
                int index = y * m_scr_width - x;
                int sindex = (int)sy * wsprite + (int)sx;
                if (render_buffer_depth[index] <= toDraw.get_draw_order()) {
                    if (sindex > maxIndexSprite) {
                        sindex = maxIndexSprite;
                    }
                    render_buffer[index].Char.AsciiChar = translate_lc(texture[sindex].l);
                    render_buffer[index].Attributes = 15;
                    render_buffer_depth[index] = toDraw.get_draw_order();
                }
            }
            sx += xDelta;
        }
        sy += yDelta;
    }
    
}