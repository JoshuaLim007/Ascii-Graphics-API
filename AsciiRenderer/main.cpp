#include <iostream>
#include <vector>
#include "Renderer.h"
//#include <unistd.h>

using namespace std;

class A : public Renderable
{
private:
    Vector2f position = Vector2f(16, 16);
    Sprite mat = Sprite(Vector2f::ZERO, Vector2f(4, 4), Vector2f::IDENTITY, '#', 1, '@');

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
    Renderer window(200, 300);

    while (true) {
        window.clear();
        window.render();
    }

    cin.get();
    return 0;
}