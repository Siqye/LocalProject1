#include "simplerenderer2d.h"
#include <iostream>
namespace LocalProject1 {
	namespace graphics {
		
		void Simple2DRenderer::submit(const Renderable2D* renderable) {
			m_RenderQueue.push_back((const ConstSprite*)renderable);
		}
		void Simple2DRenderer::flush() {
			while (!m_RenderQueue.empty()) {
				const ConstSprite* sprite = m_RenderQueue.front();

				sprite->getVAO()->bind();
				sprite->getIBO()->bind();
				
				sprite->getShader()->setUniformMat4f("ml_matrix", maths::mat4::translation(sprite->getPosition()));

				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);

				sprite->getIBO()->unbind();
				sprite->getVAO()->unbind();
				
				m_RenderQueue.pop_front();
			}

		}
	
	}
}