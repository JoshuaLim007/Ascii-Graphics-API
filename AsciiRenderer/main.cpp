#include <iostream>
#include <vector>
#include "Renderer.h"

using namespace std;
Vector2f resolution;

class A : public Renderable
{
private:
    float y_vel = 0;
    int speed = 60;
    Vector2f velocity;
public:
    A();
    A(int, int);
    void on_preRender(double) override;
};

A::A()
{
    Sprite temp;
    temp.set_texture("\dvd_logo.bmp");
    set_material(temp);
    set_draw_order(rand() % 10);
    Scale.x = .2;
    Scale.y = .2;
    velocity = Vector2f(15, 15);

}
A::A(int x, int y)
{
    Sprite temp;
    temp.set_texture("\dvd_logo.bmp");
    set_material(temp);
    set_draw_order(rand() % 10);
    Scale.x = .5;
    Scale.y = .5;
    WorldPosition.x = x;
    WorldPosition.y = y;
    velocity = Vector2f(-15, -15);

}
void A::on_preRender(double delta)
{

    WorldPosition += (velocity * delta);
    auto t = get_screen_position();
    auto instance = Renderer::get_instance();
    auto heightRes = instance->get_screen_height();
    auto widthRes = instance->get_screen_width();


    Vector2f normal;
    if (t.x < 0) {
        normal = Vector2f::RIGHT;
    }
    else if (t.x > widthRes) {
        normal = Vector2f::LEFT;
    }
    else if (t.y < 0) {
        normal = Vector2f::DOWN;
    }
    else if (t.y > heightRes) {
        normal = Vector2f::UP;
    }
    velocity = Vector2f::reflect(velocity, normal);




}
int main()
{
    srand(10);
    int scaler = 2;
    Renderer window(64 * scaler, 128 * scaler, 8 / scaler, 8 / scaler);
    resolution.x = 64 * scaler;
    resolution.y = 128 * scaler;
    A testClass;

    while (true) {
        window.clear();
        window.render();
    }

    cin.get();
    return 0;
}