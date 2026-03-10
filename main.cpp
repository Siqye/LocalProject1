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

#include "time.h"
#include "src/utils/timer.h"

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

    Timer timer;

    Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    shader.on();

    shader.setUniformMat4f("pr_matrix", mat4::orthographic(0.0f, 4.0f, 3.0f, 0.0, 1.0f, -1.0f));
    shader.setUniform4f("colour", vec4(0.0f, 0.0f, 0.4f, 1.0f));

    std::vector<Renderable2D*> sprites;
    srand(time(NULL));
    for (float j = 0.0f; j < 4.0f; j+=0.04f) {
        for (float k = 0.0f; k < 3.0f; k += 0.03f) {
            sprites.push_back(new 
#if PACKED_RENDERER
                Sprite
#else
                ConstSprite
#endif
            (j, k, 0.4f, 0.3f, maths::vec4(
                0,
                rand() % 1000 / 1000.0f,
                0,
                1)
#if !PACKED_RENDERER
                ,shader
#endif
            ));
        }
    }
#if PACKED_RENDERER
    Sprite sprite(0, 0, 1.0f, 1.0f, maths::vec4(0.0f, 0.5f, 0.0f, 0.0f));
    Packed2DRenderer renderer;

#else
    ConstSprite sprite(0, 0, 1.0f, 1.0f, maths::vec4(0.0f, 0.5f, 0.0f, 0.0f), shader);
    Simple2DRenderer renderer;
#endif

    

    shader.setUniform2f("light_pos", vec2(0,0));
    float x, y;

    float t = 0;
    long frames = 0;
    while (!window.closed()) {
        //timer.reset();
        //mat4 mat = mat4::translation(vec3(1, 1, 1));
        //mat *= mat4::translation(vec3(-3, -2, -1));
        mat4 mat = mat4::rotation(timer.elapsed() * 100.0f, vec3(0, 0, 1));
        shader.setUniformMat4f("ml_matrix",mat);
        window.getMousePosition(x, y);

        shader.setUniform2f("light_pos", vec2(
            -x * 4.0f / 800.0f, 
            -3.0f + y * 3.0f / 600.0f
        ));
#if PACKED_RENDERER
        renderer.begin();
#endif
        for (int i = 0; i < sprites.size();i++) {
            renderer.submit(sprites[i]);
        }
#if PACKED_RENDERER
        renderer.end();
#endif
        renderer.flush();
        frames++;
        if (timer.elapsed() - t > 1) {
            t+=1.0f;
            printf("%d fps\n", frames);
            frames = 0;
        }

        /*printf("%f ms\r\n", timer.elapsed() * 1000);*/
        window.update();
    }
    return 0;
}