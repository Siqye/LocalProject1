#pragma once
#include <iostream>
#include "maths.h"
#define _USE_MATH_DEFINES
namespace LocalProject1 {
	namespace maths {
		struct mat4 {

			union
			{
				float elements[16];
				vec4 columns[4];
			};

			mat4();
			mat4(float diagonal);
			friend mat4 operator*(mat4 right, const mat4& left);
			mat4& operator*=(const mat4& other);

			static mat4 identity();

			mat4& multiply(const mat4& other);

			static mat4 orthographic(float left,float right, float top, float bottom, float far, float near);
			static mat4 perspective(float fov,float aspectRatio,float near,float far);

			static mat4 translation(const vec3& trans);
			static mat4 rotation(float angle,const vec3& axis);
			static mat4 scale(const vec3& scale);

		};

	}
}