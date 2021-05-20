#include "Renderer.h"

Renderer *Renderer::Instance = NULL;
Renderer::Renderer()
{
    Init();
}
Renderer::Renderer(uint_fast16_t camVerticalSize, uint_fast16_t camHorizontalSize)
{
    m_scr_height = camVerticalSize;
    m_scr_width = camHorizontalSize;
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
    create_window_console(m_scr_width, m_scr_height, 4, 4);
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

    bufScreen = new CHAR_INFO[m_scr_width * m_scr_height];
    memset(bufScreen, 0, sizeof(CHAR_INFO) * m_scr_width * m_scr_height);

    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX); //prevent from being resized

    return 0;
}

Renderer::~Renderer()
{
    delete[] bufScreen;
    clear();
}
Renderer *Renderer::get_instance()
{
    return Instance;
}
void Renderer::render()
{
    for (auto it : toRenders) {
        it->on_draw();
    }
    WriteConsoleOutput(hConsole, bufScreen, {(short)m_scr_width, (short)m_scr_height}, {0, 0}, &rectWindow);
}
void Renderer::clear()
{
    for (int i = 0; i < m_scr_height * m_scr_width; i++)
    {
        bufScreen[i].Char.AsciiChar = ' ';
        bufScreen[i].Attributes = 0x000F;
    }
    //WriteConsoleOutput(hConsole, bufScreen, {(short)m_scr_width, (short)m_scr_height}, {0, 0}, &rectWindow);
}

void Renderer::set_camera_position(const Vector2f& pos)
{
    CameraWorldPosition = pos;
}
Vector2f Renderer::get_camera_position()
{
    return CameraWorldPosition;
}
std::vector<Renderable*>::iterator Renderer::add_renderable_to_render_stack(Renderable *renderObject)
{
    Renderable* last = NULL;
    auto end = toRenders.begin();
    for (int i = 0; end != toRenders.end(); end++) {
        if (*end != NULL) {
            if (renderObject->get_draw_order() <= (*end)->get_draw_order()) {
                auto itr = toRenders.insert(end, renderObject);
                return itr;
            }
        }
        else {
            auto itr = toRenders.insert(end, renderObject);
            return itr;
        }
    }
    //toRenders.insert(std::pair<int, Renderable*>(renderObject->get_draw_order(), renderObject));
}
void Renderer::remove_renderable_to_render_stack(std::vector<Renderable*>::iterator renderObject)
{
    toRenders.erase(renderObject);
    //toRenders.erase(renderObject->get_draw_order());
}
void Renderer::draw_sprite_material(Vector2f worldPosition, const Sprite &toDraw)
{














}