#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// out vec3 ourColor;
out vec4 position;

uniform float offset;

void main() {
   gl_Position = vec4(aPos.x + offset, aPos.yz, 1.0);
   position = vec4(aPos, 1.0);
}
