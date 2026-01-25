#pragma once

#ifdef NINTENDO_SWITCH
#include <SDL2/SDL.h>
#else
#include <stdexcept>
#include "../../glus/GL/glus.h"
#endif

namespace GraphicsWrapper {


class Display {
public:
#ifdef NINTENDO_SWITCH
    static bool initialized;
    static SDL_Window* window;
    static SDL_GLContext glContext;

    static void init(const char* title = "Project Zomboid", int width = 800, int height = 600) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            throw std::runtime_error("SDL could not initialize!");
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (!window)
            throw std::runtime_error("Window could not be created!");
        glContext = SDL_GL_CreateContext(window);
        if (!glContext)
            throw std::runtime_error("OpenGL context could not be created!");
        initialized = true;
    }

    static void update(bool swap = true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                initialized = false;
            }
        }
        if (swap && window && glContext)
            SDL_GL_SwapWindow(window);
    }

    static bool isCloseRequested() {
        return !initialized;
    }

    static void destroy() {
        if (glContext) {
            SDL_GL_DeleteContext(glContext);
            glContext = nullptr;
        }
        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        SDL_Quit();
        initialized = false;
    }

    // Static member definitions
    inline static bool initialized = false;
    inline static SDL_Window* window = nullptr;
    inline static SDL_GLContext glContext = nullptr;
#else
    static bool initialized;

    static void init(const char* title = "Project Zomboid", int width = 800, int height = 600) {
        // GLUS window creation
        if (!glusWindowCreate(title, width, height, GLUS_WINDOW_RGBA | GLUS_WINDOW_DEPTH | GLUS_WINDOW_DOUBLEBUFFER))
            throw std::runtime_error("GLUS window could not be created!");
        initialized = true;
    }

    static void update(bool swap = true) {
        glusWindowCheck();
        if (swap)
            glusSwapBuffers();
    }

    static bool isCloseRequested() {
        return !glusWindowIsOpen();
    }

    static void destroy() {
        glusWindowClose();
        initialized = false;
    }

    // Static member definition
    inline static bool initialized = false;
#endif
};

} // namespace GraphicsWrapper
