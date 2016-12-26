#pragma once
#include <SDL2pp/SDL2pp.hh>

class Cat
{
public:
  Cat(SDL2pp::Renderer &renderer);
  void draw();
  void tick();
  void jump();
  float x = 0;
  float y = 0;
private:
  float vy = 0;
  SDL2pp::Renderer &renderer;
  SDL2pp::Texture texture;
};
