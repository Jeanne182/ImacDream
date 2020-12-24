#version 300 es
precision mediump float;


in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fFragTexture;

uniform sampler2D uEarthTexture;
uniform sampler2D uCloudTexture;

void main() {
  fFragTexture = vec3(texture(uEarthTexture, vTexCoords).rgb + texture(uCloudTexture, vTexCoords).rgb);
};
