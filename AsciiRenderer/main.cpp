#include <iostream>
#include <vector>
#include "Renderer.h"
#include <unistd.h>

using namespace std;

class A : public Renderable
{
private:
    Vector2f position = Vector2f(16, 16);
    Quad mat = Quad(Vector2f::ZERO, Vector2f(4, 4), Vector2f::IDENTITY, '#', 1, '@');

public:
    A();
    void on_draw() override;
};

A::A()
{
    set_position(position);
    set_material(mat);
}
void A::on_draw()
{
}

int main()
{
    Renderer game(32, 64);
    A gameobject;

    //hideCursor();

    Vector2f camPos = game.get_camera_position();

    float timer = 0;
    for (int i = 0; i >= 0; i++)
    {
        game.screen_clear();
        game.render();
        camPos = Vector2f(camPos.x, sin(timer) * 5);
        game.set_camera_position(camPos);
        timer += 0.01f;
        usleep(3000);
    }

    //showCursor();
    return 0;
}