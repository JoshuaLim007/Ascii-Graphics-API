#include <iostream>
#include <vector>
#include "Renderer.h"

using namespace std;

class A : public Renderable
{
private:
    float y_vel = 0;
    int speed = 60;
public:
    A();
    A(int, int);
    void on_preRender(double) override;
};

A::A()
{
    Sprite temp;
    temp.set_texture("\TestBMP2.bmp");
    set_material(temp);
    set_draw_order(rand() % 10);
    Scale.x = .5;
    Scale.y = .5;
}
A::A(int x, int y)
{
    Sprite temp;
    temp.set_texture("\TestBMP2.bmp");
    set_material(temp);
    set_draw_order(rand() % 10);
    Scale.x = .05;
    Scale.y = .05;
    WorldPosition.x = x;
    WorldPosition.y = y;
}
void A::on_preRender(double delta)
{
    if (WorldPosition.y > -25) {
        y_vel -= 120 * delta;
    }
    else{
        if (y_vel < 0) {
            y_vel = 0;
        }
    }
    if (Input::GetKey('D')) {
        WorldPosition.x += speed * delta;
    }
    if (Input::GetKeyDown(' ')) {
        y_vel = speed;
    }
    if (Input::GetKey('A')) {
        WorldPosition.x -= speed * delta;
    }
    if (Input::GetKey('I')) {
        auto d = Renderer::get_instance()->get_camera_position();
        d.y += speed * delta;
        Renderer::get_instance()->set_camera_position(d);
    }
    if (Input::GetKey('J')) {
        auto d = Renderer::get_instance()->get_camera_position();
        d.x -= speed * delta;
        Renderer::get_instance()->set_camera_position(d);
    }
    if (Input::GetKey('L')) {
        auto d = Renderer::get_instance()->get_camera_position();
        d.x += speed * delta;
        Renderer::get_instance()->set_camera_position(d);
    }
    if (Input::GetKey('K')) {
        auto d = Renderer::get_instance()->get_camera_position();
        d.y -= speed * delta;
        Renderer::get_instance()->set_camera_position(d);
    }
    if (Input::GetKey(VK_RIGHT)) {
        Scale.x += delta;
        Scale.y += delta;

    }
    if (Input::GetKey(VK_LEFT)) {
        Scale.x += -delta;
        Scale.y += -delta;
    }
    WorldPosition.y += y_vel * delta;
}

int main()
{
    srand(10);
    int scaler = 2;
    Renderer window(64 * scaler, 128 * scaler, 8, 8);
    A testClass;

    while (true) {
        window.clear();
        window.render();
    }

    cin.get();
    return 0;
}