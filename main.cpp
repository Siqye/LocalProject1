#if 1

#include "iostream"
#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/graphics/shaders.h"

#include "src/graphics/buffers/vertexbuffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/renderer2d.h"
#include "src/graphics/renderable2d.h"
#include "src/graphics/simplerenderer2d.h"

using namespace LocalProject1;
using namespace maths;
using namespace graphics;



int main(int argc, char* argv[]) {
    Window window(
        800,
        600,
        "Local Engine",
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    Renderable2D sprite(vec3(3.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f),&shader);

    shader.setUniform2f("light_pos", vec2(0.3f,0.1f));

    shader.setUniform4f("colour", vec4(0.4f, 0.0f, 0.0f, 0.0f));

    Simple2DRenderer renderer;

    shader.on();

    while (!window.closed()) {
        renderer.submit(&sprite);
        renderer.flush();
        
        window.update();
    }

    return 0;
}

#endif