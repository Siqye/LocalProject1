#pragma once
#include "buffers/vertexbuffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "shaders.h"
#include "../maths/maths.h"


namespace LocalProject1 {
	namespace graphics {
		class Renderable2D {
		protected:
			maths::vec3 m_Position;
			maths::vec2 m_Size;
			maths::vec4 m_Color;

			Shader* m_Shader;
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;

		public:
			Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader* shader)
				: m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
			{

				GLfloat verts[] = {
					0,0,0,
					0,size.y,0,
					size.x ,size.y,0,
					size.x,0,0,

				};

				GLfloat colors[] = {
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w
				};

				GLuint idx[] = {
					0, 1, 2,
					2, 3, 0
				};
				m_VertexArray = new VertexArray();
				m_IndexBuffer = new IndexBuffer(idx, 12);

				m_VertexArray->addBuffer(new Buffer(verts, 4 * 3, 3), 0);
				m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

			}
			virtual ~Renderable2D() {
				delete m_VertexArray;
				delete m_IndexBuffer;
			}

			inline const VertexArray* getVAO() const { return m_VertexArray; }
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }

			inline Shader* getShader() const { return m_Shader; }
			inline const maths::vec3 getPosition() const { return m_Position; }
			inline const maths::vec2 getSize() const { return m_Size; }
			inline const maths::vec4 getColor() const { return m_Color; }
		};
	}
}