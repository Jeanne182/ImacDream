#version 300 es
precision mediump float;


in vec3 vPosition_vs;
in vec3 vNormal_vs;


out vec3 fFragTexture;


uniform Mat{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};


uniform float uShininess;
uniform vec3 uLightDir_vs; // travailler dans le view space; il faudra donc multiplier la direction de la lumière par la View Matrix avant de l'envoyer au shader. 
uniform vec3 uLightIntensity;

vec3 blinnPhong(){
  vec3 wi = normalize(uLightDir_vs);
  vec3 w0 = normalize(-vPosition_vs);
  return vec3(uLightIntensity*(Diffuse*dot(wi, vNormal_vs)+Specular*pow(dot((w0+wi)/2.,vNormal_vs),uShininess)));
}

void main() {
  fFragTexture = blinnPhong();
};
