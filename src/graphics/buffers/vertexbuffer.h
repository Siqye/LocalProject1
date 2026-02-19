#pragma once
#include "glad/glad.h"
namespace LocalProject1 {
	namespace graphics {

		class Buffer {

		private:
			GLuint m_BufferID;
			GLuint m_ComponetnCount;
		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);

			void bind() const;
			void unbind() const;


			inline GLuint getComponentCount() const { return m_ComponetnCount; }

		};

	}
}