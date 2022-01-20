#pragma once

#ifdef WINDOWS
#define INLINE _inline
#else
#define INLINE inline
#endif

typedef struct {
  int resolutionx;
  int resolutiony;
  int bitsperpixel;
  int depthbits;
  int stencilbits;
  int fullscreen;
  int sound;
  int music;
  int joystick;
} Config;
extern Config config;
