#pragma once
#include <SDL2pp/SDL2pp.hh>

class Platform
{
public:
  Platform(SDL2pp::Renderer &renderer, SDL2pp::Texture &texture, SDL2pp::Texture &brokenTexture, float &scroll, float x, float y);
  void draw();
private:
  SDL2pp::Renderer *renderer;
  SDL2pp::Texture *texture;
  SDL2pp::Texture *brokenTexture;
  float *scroll;
public:
  float x;
  float y;
  bool isBroken = false;
};
