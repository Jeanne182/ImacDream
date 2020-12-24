#version 300 es
precision mediump float;


in vec3 vPosition_vs;
in vec3 vNormal_vs;


out vec3 fFragTexture;

uniform vec3 uKd;
uniform vec3 uKs; 
uniform float uShininess;
uniform vec3 uLightPos_vs; // travailler dans le view space; il faudra donc multiplier la direction de la lumière par la View Matrix avant de l'envoyer au shader. 
uniform vec3 uLightIntensity;

vec3 blinnPhong(){
  vec3 wi = normalize(uLightPos_vs - vPosition_vs);
  vec3 w0 = normalize(-vPosition_vs);
  float d = distance(vPosition_vs, uLightPos_vs);
  vec3 Li = uLightIntensity / (d * d);
  return vec3(Li*(uKd*dot(wi, vNormal_vs)+uKs*pow(dotProduct((w0+wi)/2.,vNormal_vs),uShininess)));
}

void main() {
  fFragTexture = blinnPhong();
};
