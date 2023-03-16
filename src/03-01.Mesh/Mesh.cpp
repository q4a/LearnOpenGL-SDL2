#include <glad/glad.h>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

#include "shader.h"
#include "camera.h"
#include "mesh.h"
#include "model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void keyboard_handling();
void mouse_handling(SDL_MouseMotionEvent &event);
void scroll_handling(SDL_MouseWheelEvent &event);

int contextCreate();
void sdl_die(const char *message);

// screen
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static SDL_Window *window = NULL;
static SDL_GLContext glContext;

// camera
Camera camera(glm::vec3(0.0f, 0.0f,  3.0f));

//framerate
Uint64 NOW = SDL_GetPerformanceCounter();
Uint64 LAST = 0;
double deltaTime = 0;

//keyboard
const Uint8 * keystate;

int main(int argc, char * argv[])
{
    if (contextCreate() == -1)
    {
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    unsigned int VAO, VBO;

    Shader ourShader("shader/shader.vs", "shader/shader.fs");
    Model ourModel("Assets/Model/nanosuit.obj");

    SDL_Event event;
    bool quit = false;
    // render loop
    // -----------
    while (!quit)
    {
        keystate = SDL_GetKeyboardState(nullptr);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                mouse_handling(event.motion);
            }
            if (event.type == SDL_MOUSEWHEEL)
            {
                scroll_handling(event.wheel);
            }
        }
        keyboard_handling();
        // framerate sample
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST)/ (double)SDL_GetPerformanceFrequency() );

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        SDL_GL_SwapWindow(window);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}

int contextCreate()
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
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

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
    std::cout<<"Vendor:    "<<glGetString(GL_VENDOR)<<std::endl;
    std::cout<<"Renderer:  "<<glGetString(GL_RENDERER)<<std::endl;
    std::cout<<"Version:   "<<glGetString(GL_VERSION)<<std::endl;

    // Use v-sync
    SDL_GL_SetSwapInterval(-1);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // Disable depth test and face culling.
    glDisable(GL_CULL_FACE);

    int w,h;
    SDL_GetWindowSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(0.4f, 0.7f, 1.0f, 0.0f);
    return 0;
}

void sdl_die(const char *message)
{
    std::cerr<<message<<": "<<SDL_GetError()<<std::endl;
    exit(2);
}

void keyboard_handling()
{
    if (keystate[SDL_SCANCODE_ESCAPE])
    {
        SDL_Event quit;
        quit.type = SDL_QUIT;
        SDL_PushEvent(&quit);
        return;
    }

    if (keystate[SDL_SCANCODE_W])
    {
        camera.ProcessKeyboard(FORWARD, (float)deltaTime);
    }
    if (keystate[SDL_SCANCODE_S])
    {
        camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
    }
    if (keystate[SDL_SCANCODE_A])
    {
        camera.ProcessKeyboard(LEFT, (float)deltaTime);
    }
    if (keystate[SDL_SCANCODE_D])
    {
        camera.ProcessKeyboard(RIGHT, (float)deltaTime);
    }
}

void mouse_handling(SDL_MouseMotionEvent &event)
{
    camera.ProcessMouseMovement((float)event.xrel, (float)-event.yrel);
}

void scroll_handling(SDL_MouseWheelEvent &event)
{
    camera.ProcessMouseScroll((float)event.y);
}
