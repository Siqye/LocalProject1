#pragma once

#include "../utils/file_utils.h"
#include "GLAD/glad.h"
#include "../maths/maths.h"
#include "iostream"
#include "vector"

 namespace LocalProject1 {
	namespace graphics {
		class Shader {
		private:
			GLuint m_Shader;
			const char *m_VertexPathShader, *m_FragmentPathShader;

		public:
			Shader(const char* vertexPath, const char* fragmentPath);
			~Shader();
			void on() const;
			void off() const;


			void setUniform1i(const GLchar* name, int value);
			void setUniform1f(const GLchar* name, float value);

			void setUniform2f(const GLchar* name, const maths::vec2& vector);
			void setUniform3f(const GLchar* name, const maths::vec3& vector);
			void setUniform4f(const GLchar* name, const maths::vec4& vector);
			void setUniformMat4f(const GLchar* name, const maths::mat4& matrix);

		private:
			GLuint compileShader(GLenum type, const char* src);
			GLuint getUniformLocation(const GLchar* name);
			GLuint load();
		};
	}
 }