#include "shaders.h"

namespace LocalProject1 {
	namespace graphics {
		Shader::Shader(const char* vertexPath, const char* fragmentPath) 
			: m_VertexPathShader(vertexPath), m_FragmentPathShader(fragmentPath)
		{
			m_Shader = load();
			glUseProgram(m_Shader);
		}

		Shader::~Shader() {
			glDeleteProgram(m_Shader);
		}

		GLuint Shader::compileShader(GLenum type, const char* src) {
			std::string srcStr = read_file(src);

			const char* Src = srcStr.c_str();

			GLuint s = glCreateShader(type);
			glShaderSource(s, 1, &Src, nullptr);
			glCompileShader(s);
			GLint ok; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
			if (!ok) {
				GLint len; glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
				std::string log(len, '\0'); glGetShaderInfoLog(s, len, nullptr, &log[0]);
				std::cerr << "Shader compile error: " << log << std::endl;
			}
			return s;
		}

		GLuint Shader::load() {

			GLuint vs = compileShader(GL_VERTEX_SHADER, m_VertexPathShader);
			GLuint fs = compileShader(GL_FRAGMENT_SHADER, m_FragmentPathShader);

			GLuint p = glCreateProgram();
			GLint ok;
			glAttachShader(p, vs); glAttachShader(p, fs);
			glLinkProgram(p);glGetProgramiv(p, GL_LINK_STATUS, &ok);
			if (!ok) {
				GLint len; glGetProgramiv(p, GL_INFO_LOG_LENGTH, &len);
				std::string log(len, '\0'); glGetProgramInfoLog(p, len, nullptr, &log[0]);
				std::cerr << "Program link error: " << log << std::endl;
			}
			glDeleteShader(vs); glDeleteShader(fs);
			return p;
		}

		void Shader::on() const {
			glUseProgram(m_Shader);
		}

		void Shader::off() const {
			glUseProgram(0);
		}

		GLuint Shader::getUniformLocation(const GLchar* name) {
			return glGetUniformLocation(m_Shader, name);
		}

		void Shader::setUniform1i(const char* name, int value) {
			glUniform1i(getUniformLocation(name), value);
		}
		void Shader::setUniform1f(const char* name, float value) {
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform2f(const char* name, const maths::vec2& vector) {
			glUniform2f(getUniformLocation(name), vector.x,vector.y);
		}
		void Shader::setUniform3f(const char* name, const maths::vec3& vector) {
			glUniform3f(getUniformLocation(name), vector.x,vector.y,vector.z);
		}
		void Shader::setUniform4f(const char* name, const maths::vec4& vector) {
			glUniform4f(getUniformLocation(name), vector.x,vector.y,vector.z,vector.w);
		}
        void Shader::setUniformMat4f(const char* name, const maths::mat4& matrix) {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
        }

	}
}