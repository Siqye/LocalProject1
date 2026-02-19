#pragma once
#include "glad/glad.h"


namespace LocalProject1 {
	namespace graphics {

		class IndexBuffer {

		private:
			GLuint m_BufferID;
			GLuint m_Count;
		public:
			IndexBuffer(GLuint* data, GLsizei count);

			void bind() const;
			void unbind() const;
			
			inline GLuint getCount() const { return m_Count; }

		};

	}
}