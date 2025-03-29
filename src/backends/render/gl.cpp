#include "../../core.hpp"
#include "../../debug.hpp"
#include "gl.hpp"

#ifdef BOSHIBACKEND_RND_GL

#ifdef BOSHIBACKEND_WND_SDL2
#include "../window/sdl2.hpp"
#endif

/*
 * Because boshi isn't necessarily trying to be groundbreaking,
 * I'm using OpenGL 2.0 here for compatibility. In most cases than not,
 * we're probably not gonna need newer versions. This choice is purely made
 * for porting purposes (like for example, should you want to port this to
 * the PlayStation Vita, you can just use vitaGl like it's nothing and have it
 * go like it's nothing.)
*/
namespace boshi::Backends::Render {
    void OpenGL::Initialize() {
        Debug::Log(0x00, "Using OpenGL as the render backend...");

        PrepareRenderTexture(GEI.gameSize.x, GEI.gameSize.y);
        isInitialized = 1;
    }

    uint8_t OpenGL::IsInitialized() {
        return isInitialized;
    }

    void OpenGL::Destroy() {
        if (glIsTexture(screenTexture))
            glDeleteTextures(1, &screenTexture);
        isInitialized = 0;
    }

    void OpenGL::PrepareRenderTexture(int w, int h) {
        if (glIsTexture(screenTexture))
            glDeleteTextures(1, &screenTexture);

        glGenTextures(1, &screenTexture);
            glBindTexture(GL_TEXTURE_2D, screenTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGL::ChangeViewport(int w, int h) {
        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
            glOrtho(0, w, h, 0, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void OpenGL::DrawRectangle(float x1, float y1, float x2, float y2, Color color) {
        glColor4f(color.r, color.g, color.b, color.a);
        glBegin(GL_QUADS);
            glVertex2f(x1, y1);
            glVertex2f(x1 + x2, y1);
            glVertex2f(x1 + x2, y1 + y2);
            glVertex2f(x1, y1 + y2);
        glEnd();
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    }

    void OpenGL::BeginFrame() {
        ChangeViewport(GEI.gameSize.x, GEI.gameSize.y);
        Clear(Color(100.0 / 255.0, 149.0 / 255.0, 237.0 / 255.0));
    }

    void OpenGL::Clear(Color color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGL::PresentFrame() {
        glBindTexture(GL_TEXTURE_2D, screenTexture);
            glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GEI.gameSize.x, GEI.gameSize.y, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        ChangeViewport(GEI.screenSize.x, GEI.screenSize.y);

        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
            Clear(Color(0.0, 0.0, 0.0, 1.0f));

        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, screenTexture);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(GEI.gameSize.x, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(GEI.gameSize.x, GEI.gameSize.y);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, GEI.gameSize.y);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);

        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);

        #ifdef BOSHIBACKEND_WND_SDL2
            auto* backend = dynamic_cast<Backends::Window::SDL2*>(GEI.windowBackend.get());
            if (backend != nullptr) {
                SDL_GL_SwapWindow(backend->GetWindow());
            }
        #endif
    }
}
#endif
