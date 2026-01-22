#pragma once

#include <SDL2/SDL.h>
// GLUS headers (from src/glus/GLUS)
#include "glus_axisalignedbox.h"
#include "glus_clib.h"
#include "glus_complex.h"
#include "glus_define.h"
#include "glus_define_color.h"
#include "glus_define_color_channel.h"
#include "glus_define_color_channel_es.h"
#include "glus_define_color_channel_vg.h"
#include "glus_define_color_vg.h"
#include "glus_define_shader.h"
#include "glus_define_shader_es.h"
#include "glus_define_shader_es31.h"
#include "glus_define_uint.h"
#include "glus_define_ushort.h"
#include "glus_egl.h"
#include "glus_extension.h"
#include "glus_file.h"
#include "glus_file_binary.h"
#include "glus_file_text.h"
#include "glus_fourier.h"
#include "glus_function.h"
#include "glus_glfw_es.h"
#include "glus_image.h"
#include "glus_image_hdr.h"
#include "glus_image_pkm.h"
#include "glus_image_tga.h"
#include "glus_intersect.h"
#include "glus_line.h"
#include "glus_line_wavefront.h"
#include "glus_log.h"
#include "glus_math.h"
#include "glus_matrix.h"
#include "glus_matrix_planar.h"
#include "glus_matrix_viewprojection.h"
#include "glus_memory.h"
#include "glus_orientedbox.h"
#include "glus_padding.h"
#include "glus_perlin.h"
#include "glus_plane.h"
#include "glus_point.h"
#include "glus_profile.h"
#include "glus_program.h"
#include "glus_program_es.h"
#include "glus_program_es31.h"
#include "glus_programpipeline.h"
#include "glus_programpipeline_es31.h"
#include "glus_quaternion.h"
#include "glus_random.h"
#include "glus_raytrace.h"
#include "glus_screenshot.h"
#include "glus_shape.h"
#include "glus_shape_adjacency.h"
#include "glus_shape_texgen.h"
#include "glus_shape_wavefront.h"
#include "glus_sphere.h"
#include "glus_time.h"
#include "glus_typedef.h"
#include "glus_vector.h"
#include "glus_version.h"
#include "glus_wavefront.h"
#include "glus_window.h"
#include <string>

namespace lwjglx {
namespace opengl {


class Display {
public:
    static bool createWindow(const std::string& title, int width, int height, bool fullscreen = false);
    static void update(bool swap = true);
    static void destroy();
    static bool isCloseRequested();
    static void sync(int fps);
    static void setVSync(bool enabled);
    static SDL_Window* getWindow();
    static SDL_GLContext getContext();

    // SDL2/GLUS replacements or stubs for unsupported methods
    static void setIcon(void*) {} // Stub: No-op
    static void setTitle(const std::string& title) { if (window) SDL_SetWindowTitle(window, title.c_str()); }
    static void setResizable(bool resizable) { if (window) SDL_SetWindowResizable(window, resizable ? SDL_TRUE : SDL_FALSE); }
    static void setFullscreen(bool fullscreen) { if (window) SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0); }
    static int getWidth() { int w = 0, h = 0; if (window) SDL_GetWindowSize(window, &w, &h); return w; }
    static int getHeight() { int w = 0, h = 0; if (window) SDL_GetWindowSize(window, &w, &h); return h; }
    static bool isFullscreen() { return window && (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN); }
    static bool isCreated() { return window != nullptr; }
    static void processMessages() { update(false); }
    static void makeCurrent() { if (window && context) SDL_GL_MakeCurrent(window, context); }
    static void releaseContext() { if (window) SDL_GL_MakeCurrent(window, nullptr); }
    // The following are stubs or minimal implementations
    static void setDisplayMode(void*) {} // Stub
    static void setDisplayModeAndFullscreen(void*) {} // Stub
    static void setVSyncEnabled(bool enabled) { setVSync(enabled); }
    static void setBorderlessWindow(bool) {} // Stub
    static void create(void*) {} // Stub
    static void destroyContext() { destroy(); }
    static void* getDisplayMode() { return nullptr; } // Stub
    static void* getDesktopDisplayMode() { return nullptr; } // Stub
    static void* getAvailableDisplayModes() { return nullptr; } // Stub
    static void* getWindow() { return window; }

private:
    static SDL_Window* window;
    static SDL_GLContext context;
    static bool closeRequested;
};

} // namespace opengl
} // namespace lwjglx
