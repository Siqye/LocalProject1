#pragma once
#include "vector"

#include "glad/glad.h"

#include "vertexbuffer.h"

namespace LocalProject1 {
	namespace graphics {

		class VertexArray {
		private:
			GLuint m_ArrayID;
			std::vector<Buffer*> m_Buffers;

		public:
			VertexArray();
			~VertexArray();

			void addBuffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;

		};

	}
}