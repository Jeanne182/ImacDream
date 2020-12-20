#version 300 es
precision mediump float;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform Mat{
	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;
};

void main() {

    fFragColor = Diffuse;


};