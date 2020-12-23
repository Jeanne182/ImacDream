#version 300 es
precision mediump float;


in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform sampler2D texture_diffuse1;

void main() {
     fFragColor = texture(texture_diffuse1, vTexCoords);

};
