#include "cat.hpp"
#include "consts.hpp"
#include "platform.hpp"
#include <SDL2pp/SDL2pp.hh>
#include <vector>

int main(int argc, char **argv)
{
  using namespace SDL2pp;
  SDL sdl(SDL_INIT_EVERYTHING);
  Window window("Cat Jump", 65, 126, Width, Height, SDL_WINDOW_BORDERLESS);
  Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
  Cat cat(renderer);
  Texture platformTexture(renderer, Surface("platform.bmp"));
  Texture platformBrokenTexture(renderer, Surface("platform-broken.bmp"));
  std::vector<Platform> platformList;
  for (auto i = 0; i < 1000; ++i)
    platformList.emplace_back(renderer, platformTexture, platformBrokenTexture, cat.y, rand() % Width, i * 200);
  auto currentTime = SDL_GetTicks();
  
  for (auto done = false; !done;)
  {
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
      case SDL_MOUSEBUTTONDOWN:
        cat.jump();
        break;
      case SDL_QUIT:
        done = true;
        break;
      }
    }
    auto oldTime = currentTime;
    currentTime = SDL_GetTicks();
    auto oldCatX = cat.x;
    auto oldCatY = cat.y;
    for (;oldTime < currentTime; ++oldTime)
      cat.tick();
    auto catx1 = std::min(oldCatX, cat.x) - 64;
    auto caty1 = std::min(oldCatY, cat.y);
    auto catx2 = std::max(oldCatX, cat.x) + 64;
    auto caty2 = std::max(oldCatY, cat.y);
    for (auto &p: platformList)
    {
      if (p.isBroken)
        continue;
      if ((p.y - caty1) * (p.y - caty2) > 0)
        continue;
      auto x1 = p.x - 64;
      auto x2 = p.x + 64;
      if ((x1 - catx1) * (x1 - catx2) > 0 &&
          (x2 - catx1) * (x2 - catx2) > 0)
        continue;
      p.isBroken = true;
      cat.jump();
    }
    platformList.erase(std::remove_if(std::begin(platformList),
                                      std::end(platformList),
                                      [&cat](Platform &platform)
                                      {
                                        return platform.y < cat.y - 400;
                                      }),
                       std::end(platformList));
    renderer.SetDrawColor(0x00, 0x80, 0xff, 0xff);
    renderer.Clear();
    for (auto &platform: platformList)
      platform.draw();
    cat.draw();
    renderer.Present();
  }
  
}
