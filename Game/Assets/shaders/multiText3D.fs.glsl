#version 300 es
precision mediump float;


in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fFragTexture;

uniform sampler2D uTexture;
uniform sampler2D uTexture2;

void main() {
  //vec3 texture = texture(uTexture, vTexCoords).rgb;
  //vec3 texture2 = texture(uTexture2, vTexCoords).rgb;
  fFragTexture = vec3(texture(uTexture, vTexCoords).rgb + texture(uTexture2, vTexCoords).rgb);
}