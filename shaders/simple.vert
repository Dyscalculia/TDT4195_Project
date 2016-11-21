#version 430 core

in vec3 position;
layout(location = 1) in vec4 vcolor;

out vec4 fragColor;

uniform layout(location = 2) mat4 matrix1;

void main()
{
	gl_Position =  matrix1 * vec4(position, 1.0f);

	fragColor = vcolor;
}
