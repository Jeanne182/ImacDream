#version 300 es
precision mediump float;


in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec4 fFragColor;

uniform vec3 uAmbiant;
uniform vec3 uDiffuse;
uniform vec3 uSpecular;
uniform float uShininess;
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;
uniform vec3 viewPos;

vec3 blinnPhong(){

       // ambient
       vec3 ambiant = uAmbiant * uDiffuse;

       // diffuse
       vec3 lightDir = normalize(uLightPos_vs - vPosition_vs);
       vec3 normal = normalize(vNormal_vs);
       float diff = max(dot(lightDir, normal), 0.0);
       vec3 diffuse = diff * uDiffuse;

       // specular
       vec3 viewDir = normalize(viewPos - vPosition_vs);
       vec3 reflectDir = reflect(-lightDir, normal);

       float d = distance(vPosition_vs, uLightPos_vs);
       vec3 attenuation = clamp( uLightIntensity / d, 0.0, 1.0);
       float spec = 0.;

       vec3 halfwayDir = normalize(lightDir + viewDir);
       spec = pow(max(dot(normal, halfwayDir), 0.0),uShininess);

       vec3 specular = uSpecular * spec;

       return vec3(ambiant + diffuse + specular) * attenuation;


}

//void main() {
//       fFragColor = blinnPhong();
//}

void main() {

       vec4 texColor;
       texColor.rgb = blinnPhong();
       texColor.a = 0.3;
       fFragColor = texColor;
//       fFragColor = blinnPhong();
}
