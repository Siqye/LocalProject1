#include "constsprite.h"
namespace LocalProject1 {
	namespace graphics {
		ConstSprite::ConstSprite(float x, float y, float width, float height,maths::vec4 color,Shader& shader)
			: Renderable2D(maths::vec3(x,y,0),maths::vec2(width,height),color), m_Shader(&shader)
		{
			GLfloat verts[] = {
				0,0,0,
				0,height,0,
				width ,height,0,
				width,0,0,
			};


			GLfloat colors[] = {
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			GLushort idx[] = {
				0, 1, 2,
				2, 3, 0
			};
			
			m_VertexArray = new VertexArray();
			m_IndexBuffer = new IndexBuffer(idx,12);

			m_VertexArray->addBuffer(new Buffer(verts, 4 * 3, 3), 0);
			m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
		}
		ConstSprite::~ConstSprite() {
			delete m_VertexArray;
			delete m_IndexBuffer;
		}

	}
}