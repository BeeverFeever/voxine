#version 460 core
out vec4 FragColor;
// in position vec3 ourColor;
in vec4 position;

void main() {
   // FragColor = vec4(position, 1.0);
   FragColor = position;
}
