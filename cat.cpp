#include "cat.hpp"
#include "consts.hpp"
using namespace SDL2pp;

Cat::Cat(Renderer &renderer):
  renderer(renderer),
  texture(renderer, Surface("cat.bmp"))
{}

void Cat::draw()
{
  renderer.Copy(texture, NullOpt, Rect(x - 64, Height - 128 - Height / 10, 128, 128));
}

void Cat::tick()
{
  int xx;
  int yy; 
  SDL_GetMouseState(&xx, &yy);
  x = xx;
  vy -= 0.002;
  vy *= 0.997;
  y += vy;
}

void Cat::jump()
{
  vy += 2.0f;
}
