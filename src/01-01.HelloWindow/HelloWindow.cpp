#include <glad/glad.h>
#include <SDL2/SDL.h>

#include <iostream>

static void sdl_die(const char *message);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static SDL_Window *window = NULL;
static SDL_GLContext glContext;

int main(int argc, char * argv[])
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        sdl_die("Couldn't initialize SDL");
    atexit (SDL_Quit);

    //Context Setup
    SDL_GL_LoadLibrary(nullptr); // Default OpenGL is fine.

    // Request an OpenGL 3.3 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //Create Window
    window = SDL_CreateWindow(
        "LearnOpenGL_SDL",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL
    );
    if (window == nullptr) sdl_die("Couldn't set video mode");

    // Create Context
    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) sdl_die("Failed to create OpenGL Context");

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    // Use v-sync
    SDL_GL_SetSwapInterval(1);

    // Done Initializing context

    SDL_Event event;
    bool quit = false;
    // render loop
    // -----------
    while (!quit)
    {
        SDL_GL_SwapWindow(window);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    return 0;
}

void sdl_die(const char *message)
{
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    exit(2);
}
