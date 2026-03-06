#include "mat4.h"
#include "math.h"
float toRadians(float degrees) {
	return degrees * (M_PI / 180.0f);
}

namespace LocalProject1 {
	namespace maths {

		mat4::mat4() {
			for (int i = 0; i < 16; i++)
				elements[i] = 0.0f;
		}
		
		mat4::mat4(float diagonal) {
			for (int i = 0; i < 16; i++)
				elements[i] = 0.0f;

			elements[0+0*4] = diagonal;
			elements[1+1*4] = diagonal;
			elements[2+2*4] = diagonal;
			elements[3+3*4] = diagonal;
			
		}

		mat4 mat4::identity() {
			return mat4(1.0f);
		}

		mat4& mat4::multiply(const mat4& other) {
			float sum;
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					sum = 0.0f;
					for (int e = 0; e < 4; e++) {
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					elements[x + y * 4] = sum;
				}
			}
			return *this;
		}

		mat4 operator*(mat4 right, const mat4& left) {
			return right.multiply(left);
		}
		mat4& mat4::operator*=(const mat4& other) {
			return multiply(other);
		}

		mat4 mat4::orthographic(float left, float right, float top, float bottom, float far, float near) {
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (far + near) / (far - near);

			return result;
		}
		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far) {
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 1.0f / (aspectRatio * tanf(toRadians(fov / 2.0f)));
			result.elements[1 + 1 * 4] = 1.0f / (tanf(toRadians(fov / 2.0f)));
			
			result.elements[2 + 2 * 4] = (far+near) / (far-near);
			result.elements[2 + 3 * 4] = (2.0f*far * near) / (far - near);

			result.elements[3 + 2 * 4] = -1.0f;

			return result;
		}

		mat4 mat4::translation(const vec3& trans) {
			mat4 result(1.0f);
			result.elements[0 + 3 * 4] = trans.x;
			result.elements[1 + 3 * 4] = trans.y;
			result.elements[2 + 3 * 4] = trans.z;

			return result;
		}

		mat4 mat4::rotation(float angle, const vec3& axis) {
			mat4 result(1.0f);
			
			float r = toRadians(angle);
			float s = sin(r);
			float c = cos(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;


			result.elements[1 + 0 * 4] = x * omc + c;
			result.elements[1 + 0 * 4] = y * x * omc + z * s;
			result.elements[2 + 0 * 4] = z * x * omc - y * s;

			result.elements[1 + 1 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * omc + c;
			result.elements[2 + 1 * 4] = z * z * omc - x * s;

			result.elements[1 + 2 * 4] = x * z * omc + y * s;
			result.elements[1 + 2 * 4] = y * x * omc - x * s;
			result.elements[2 + 2 * 4] = z * omc - c;


			return result;
		}

		mat4 mat4::scale(const vec3& scale) {
			mat4 result(1.0f);
			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;
			return result;
		}
	}
}