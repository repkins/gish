#pragma once

#ifdef __LINUX__
#define LINUX 1
#endif

#ifdef _WIN32
#define WINDOWS 1
#endif

#ifdef __APPLE__
#define MAC 1
#endif

#ifdef MAC
#define __MACOSX__
#endif

#include <stdio.h>
#include <SDL.h>

#ifdef WINDOWS
#define INLINE _inline
#else
#define INLINE inline
#endif

extern int debugit;
extern char versiontext[];

extern const SDL_VideoInfo* sdlvideoinfo;
extern SDL_PixelFormat* sdlpixelformat;

