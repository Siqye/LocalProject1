#include "iostream"
#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/graphics/shaders.h"

#include "src/graphics/buffers/vertexbuffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/renderer2d.h"
#include "src/graphics/renderable2d.h"
#include "src/graphics/packed2drenderer.h"
#include "src/graphics/simplerenderer2d.h"
//#include "src/graphics/packed2drenderer.h"
#include "src/graphics/constsprite.h"
#include "src/graphics/sprite.h"

#define PACKED_RENDERER 1

using namespace LocalProject1;
using namespace maths;
using namespace graphics;


int main(int argc, char* argv[]) {
    Window window(
        800,
        600,
        "Local Engine",
        SDL_WINDOW_OPENGL
    );

    Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    shader.on();

    shader.setUniformMat4f("pr_matrix", mat4::orthographic(0.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f));
    shader.setUniform4f("colour", vec4(0.0f, 0.0f, 0.4f, 1.0f));
#if PACKED_RENDERER
    Sprite sprite(0, 0, 1.0f, 1.0f, maths::vec4(0.0f, 0.5f, 0.0f, 0.0f));
    Sprite sprite2(0, 0, 1.0f, 1.0f, maths::vec4(0.0f, 0.5f, 0.0f, 0.0f));
    Packed2DRenderer renderer;
#else
    ConstSprite sprite(0, 0, 1.0f, 1.0f, maths::vec4(0.0f, 0.5f, 0.0f, 0.0f), shader);
    Simple2DRenderer renderer;
#endif

    

    shader.setUniform2f("light_pos", vec2(0,0));
    float x, y;

    while (!window.closed()) {
        window.getMousePosition(x, y);

        shader.setUniform2f("light_pos", vec2(
            -x * 1.0f / 800.0f, 
            -1.0f + y * 1.0f / 600.0f
        ));
#if PACKED_RENDERER
        renderer.begin();
#endif
        renderer.submit(&sprite);
        renderer.submit(&sprite2);
#if PACKED_RENDERER
        renderer.end();
#endif
        renderer.flush();

        window.update();
    }

    return 0;
}