#include "packed2drenderer.h"

namespace LocalProject1 {
	namespace graphics {

		Packed2DRenderer::Packed2DRenderer() {
			init();
		}
		Packed2DRenderer::~Packed2DRenderer() {
			
		}
		void Packed2DRenderer::init() {
			/*соблюдайте порядок пожалуйста*/
			glGenBuffers(1, &m_VBO);
			glGenVertexArrays(1, &m_VAO);
			/*иначе ваш анал треснет >:(*/
			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER,m_VBO);

			glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(VERTEX_INDEX,3,GL_FLOAT,GL_FALSE,VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::vertex));
			glVertexAttribPointer(COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE, (const GLvoid*)offsetof(VertexData,VertexData::color));
			glEnableVertexAttribArray(VERTEX_INDEX);
			glEnableVertexAttribArray(COLOR_INDEX);

			GLushort indecies[INDICIES_SIZE];
			int o = 0; /*o = offset*/
			/*
			0,	1,	2
			2,	3,	0			
			o+0,o+1,o+2
			o+2,o+3,o+0
			*/
			for (int i = 0; i < INDICIES_SIZE; i+=6) { /*i = index*/
				indecies[i]/*!*/= o + 0;
				indecies[i+1]	= o + 1;
				indecies[i+2]	= o + 2;

				indecies[i+3]	= o + 2;
				indecies[i+4]	= o + 3;
				indecies[i+5]	= o + 0;
				o += 4;
			}

			m_IBO = new IndexBuffer(indecies,INDICIES_SIZE);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		void Packed2DRenderer::submit(const Renderable2D* renderable) {

			maths::vec3 pos = renderable->getPosition();
			maths::vec2 size = renderable->getSize();
			maths::vec4 col = renderable->getColor();

			int r = col.x * 255;
			int g = col.y * 255;
			int b = col.z * 255;
			int a = col.w * 255;

			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			m_Buffer->vertex = pos;
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = maths::vec3(pos.x,pos.y+size.y,pos.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = maths::vec3(pos.x+size.x, pos.y + size.y, pos.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = maths::vec3(pos.x + size.x, pos.y, pos.z);
			m_Buffer->color = c;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void Packed2DRenderer::begin() {
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}
		void Packed2DRenderer::end() {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void Packed2DRenderer::flush() {
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(m_VAO);
			m_IBO->bind();
			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, 0);
			m_IBO->unbind();
			glBindVertexArray(0);

			m_IndexCount = 0;
		}
	}
}