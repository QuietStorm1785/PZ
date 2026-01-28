#pragma once
#include <GL/glew.h>
// TODO: Implement OpenGL context abstraction if needed

#ifdef NINTENDO_SWITCH
#include <SDL2/SDL_opengl.h>
#else
#include <GL/gl.h>
#endif
