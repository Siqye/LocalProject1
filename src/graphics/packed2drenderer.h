#include "glad/glad.h"
#include "renderer2d.h"
#include "buffers/vertexarray.h"
#include "buffers/indexbuffer.h"
#include "constsprite.h"

#define MAX_SPRITES		10000
#define VERTEX_SIZE		sizeof(VertexData)
#define SPRITE_SIZE		VERTEX_SIZE * 4
#define BUFFER_SIZE		MAX_SPRITES * SPRITE_SIZE
#define INDICIES_SIZE	MAX_SPRITES * 6

#define VERTEX_INDEX	0
#define COLOR_INDEX		1

namespace LocalProject1 {
	namespace graphics {
		class Packed2DRenderer : public Renderer2D {
		private:
			GLuint m_VAO;
			IndexBuffer* m_IBO; 
			VertexData* m_Buffer;
			GLsizei m_IndexCount;
			GLuint m_VBO;
		public:
			Packed2DRenderer();
			~Packed2DRenderer();
			void init();
			void begin();
			void submit(const Renderable2D* renderable) override;
			void end();
			void flush() override;
		};
	}
}