#version 300 es
precision mediump float;

in vec2 vTexCoords;

out vec4 fFragColor;

uniform sampler2D texture_diffuse1;

void main() {
std::cout<<"shader"<<std::endl;
  fFragColor = vec4(0,1,0,1);
};
