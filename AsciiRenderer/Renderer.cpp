#include "Renderer.h"

Renderer *Renderer::Instance = NULL;
Renderer::Renderer()
{

    Init();
}
Renderer::Renderer(uint_fast8_t camVerticalSize, uint_fast8_t camHorizontalSize)
{
    cameraVerticalSize = camVerticalSize;
    cameraHorizontalSize = camHorizontalSize;

    Init();
}
void Renderer::Init()
{
    if (Instance == NULL)
    {
        Instance = this;
    }
    CameraWorldPosition.x = 0; //float(cameraHorizontalSize) / 2.0f;
    CameraWorldPosition.y = 0; //float(cameraVerticalSize) / 2.0f;

#ifdef _WIN32
    bufScreen = new CHAR_INFO[cameraHorizontalSize * cameraVerticalSize];
    memset(bufScreen, 0, sizeof(CHAR_INFO) * cameraHorizontalSize * cameraVerticalSize);
    create_window_console(cameraHorizontalSize, cameraVerticalSize, 2, 2);
#endif
#ifdef __unix__

#endif
}

#ifdef _WIN32
void Renderer::create_window_console(int width, int height, int fontw, int fonth)
{
    rectWindow = {0, 0, 1, 1};
    SetConsoleWindowInfo(hConsole, TRUE, &rectWindow);

    COORD coord = {(short)cameraHorizontalSize, (short)cameraVerticalSize};
    SetConsoleScreenBufferSize(hConsole, coord);
    SetConsoleActiveScreenBuffer(hConsole);

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    short swidth = short(width - 1);
    short sheight = short(height - 1);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = fontw;
    cfi.dwFontSize.Y = fonth;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(hConsole, false, &cfi);

    rectWindow = {0, 0, swidth, sheight};
    SetConsoleWindowInfo(hConsole, TRUE, &rectWindow);

    SetConsoleMode(hConsole, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    CONSOLE_CURSOR_INFO ConCurInf;
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = false;
    SetConsoleCursorInfo(hConsole, &ConCurInf);

#pragma region Extra settings
    /*
    if (!SetConsoleScreenBufferSize(hConsole, coord))
    {
        std::cout << "SetConsoleScreenBufferSize Error!" << endl;
        __throw_system_error('a');
    }
    
    if (!SetConsoleActiveScreenBuffer(hConsole))
    {
        std::cout << "SetConsoleActiveScreenBuffer Error!" << endl;
        __throw_system_error('b');
    }
    
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = fontw;
    cfi.dwFontSize.Y = fonth;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    if (!SetCurrentConsoleFontEx(hConsole, false, &cfi))
    {
        std::cout << "SetCurrentConsoleFontEx Error!" << endl;
        __throw_system_error('c');
    }
    

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        std::cout << "GetConsoleScreenBufferInfo Error!" << endl;
        __throw_system_error('d');
    }
    if (height > csbi.dwMaximumWindowSize.Y)
    {
        std::cout << "Font Error!" << endl;
        __throw_system_error('e');
    }
    if (width > csbi.dwMaximumWindowSize.X)
    {
        std::cout << "Font Error!" << endl;
        __throw_system_error('f');
    }
    
    short sWidth = (short)(width - 1);
    short sHeight = (short)(height - 1);
    rectWindow = {0, 0, sWidth, sHeight};
    if (!SetConsoleWindowInfo(hConsole, TRUE, &rectWindow))
    {
        std::cout << "SetConsoleWindowInfo Error!" << endl;
        __throw_system_error('g');
    }
    if (!SetConsoleMode(hConsole, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
    {
        std::cout << "SetConsoleMode Error!" << endl;
        __throw_system_error('h');
    }
    */

    //bufScreen = new CHAR_INFO[width * height];
    //memset(bufScreen, 0, sizeof(CHAR_INFO) * width * height);
}
#endif
Renderer::~Renderer()
{
    delete[] bufScreen;
    screen_clear();
}
Renderer *Renderer::get_instance()
{
    return Instance;
}
void Renderer::render()
{
    for (int i = 0; i < toRenders.count(); i++)
    {
        toRenders[i]->on_draw();
        draw_quad_material(toRenders[i]->get_position(), toRenders[i]->get_material());
    }
#ifdef _WIN32
    WriteConsoleOutput(hConsole, bufScreen, {(short)cameraHorizontalSize, (short)cameraVerticalSize}, {0, 0}, &rectWindow);
#endif
}
void Renderer::screen_clear()
{
#ifdef _WIN32
    for (int i = 0; i < cameraVerticalSize * cameraHorizontalSize; i++)
    {
        bufScreen[i].Char.AsciiChar = ' ';
        bufScreen[i].Attributes = 0x000F;
    }
    WriteConsoleOutput(hConsole, bufScreen, {(short)cameraHorizontalSize, (short)cameraVerticalSize}, {0, 0}, &rectWindow);
#endif
#ifdef __unix__

#endif
}

void Renderer::set_camera_position(Vector2f pos)
{
    CameraWorldPosition = pos;
}
Vector2f Renderer::get_camera_position()
{
    return CameraWorldPosition;
}
void Renderer::add_rendereable_to_render_stack(Renderable *renderObject)
{
    if (toRenders.count() == 0)
    {
        toRenders.add(renderObject);
    }
    else
    {
        Renderable *previous = NULL;
        for (int i = 0; i < toRenders.count(); i++)
        {
            if (previous)
            {
                if (toRenders[i]->get_draw_order() >= renderObject->get_draw_order() && previous->get_draw_order() <= renderObject->get_draw_order())
                {
                    toRenders.insert_at(renderObject, i);
                }
            }
            else
            {
                if (toRenders[i]->get_draw_order() > renderObject->get_draw_order())
                {
                    toRenders.insert_at(renderObject, i);
                }
            }
            previous = toRenders[i];
        }
    }
}
void Renderer::draw_quad_material(Vector2f worldPosition, const Quad &toDraw)
{
    float xPos = toDraw.LocalSpacePosition.x + worldPosition.x - this->CameraWorldPosition.x;
    float yPos = toDraw.LocalSpacePosition.y + worldPosition.y - this->CameraWorldPosition.y;

    float xHalfExt = toDraw.HalfExtents.x;
    float yHalfExt = toDraw.HalfExtents.y;
    float xScale = toDraw.Scale.x;
    float yScale = toDraw.Scale.y;
    float scaledXOffset = (xHalfExt * xScale);
    float scaledYOffset = (yHalfExt * yScale);
    float xOutLineSize = toDraw.OutlineSize * xScale;
    float yOutLineSize = toDraw.OutlineSize * yScale;

    float leftBound = xPos - scaledXOffset;
    float rightBound = xPos + scaledXOffset;
    float upBound = yPos - scaledYOffset;
    float downBound = yPos + scaledYOffset;
    float leftBoundOutline = leftBound + xOutLineSize;
    float rightBoundOutline = rightBound - xOutLineSize;
    float upBoundOutline = leftBound + yOutLineSize;
    float downBoundOutline = downBound - yOutLineSize;

    for (float x = leftBound; x <= rightBound; x++)
    {
        for (float y = upBound; y <= downBound; y++)
        {
            int ix = roundf(x);
            int iy = roundf(y);
            if (x >= 0 && x < cameraHorizontalSize && y >= 0 && y < cameraVerticalSize)
            {
                if (x < leftBoundOutline || x > rightBoundOutline || y < upBoundOutline || y > downBoundOutline)
                {
                    if (toDraw.BorderStyle != ' ')
                    {
#ifdef _WIN32
                        bufScreen[iy * cameraHorizontalSize + ix].Char.AsciiChar = toDraw.BorderStyle;
                        bufScreen[iy * cameraHorizontalSize + ix].Attributes = 0x000F;
#endif
                    }
                }
                else
                {
                    if (toDraw.FillStyle != ' ')
                    {
#ifdef _WIN32
                        bufScreen[iy * cameraHorizontalSize + ix].Char.AsciiChar = toDraw.FillStyle;
                        bufScreen[iy * cameraHorizontalSize + ix].Attributes = 0x000F;
#endif
                    }
                }
            }
        }
    }
}