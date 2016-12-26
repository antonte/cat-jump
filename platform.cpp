#include "platform.hpp"
#include "consts.hpp"

using namespace SDL2pp;

Platform::Platform(Renderer &renderer, Texture &texture, Texture &brokenTexture, float &scroll, float x, float y):
  renderer(&renderer),
  texture(&texture),
  brokenTexture(&brokenTexture),
  scroll(&scroll),
  x(x),
  y(y)
{}

void Platform::draw()
{
  renderer->Copy(!isBroken ? *texture : *brokenTexture, NullOpt, Rect(x - 64, Height - Height / 10 - y + *scroll - 16, 128, 32));
}
