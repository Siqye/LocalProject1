#pragma once
#include "renderable2d.h"
#include "../maths/maths.h"
namespace LocalProject1 {
	namespace graphics {
		class ConstSprite : public Renderable2D {
		protected:
			Shader* m_Shader;
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
		public:
			ConstSprite(float x, float y, float width, float height, maths::vec4 color, Shader& shader);
			~ConstSprite();

			inline const VertexArray* getVAO() const { return m_VertexArray; }
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
			inline Shader* getShader() const { return m_Shader; }
		};
	}
}