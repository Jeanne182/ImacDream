#version 300 es

precision highp float;


in vec2 vVertexCoord;
out vec4 color;
uniform sampler2D uText;
uniform vec3 uTextColor;


void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uText, vVertexCoord).r);
    color = vec4(uTextColor, 1.0) * sampled;
}