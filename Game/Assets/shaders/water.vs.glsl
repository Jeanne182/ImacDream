#version 300 es
precision mediump float;

// Attributs de sommet
layout(location = 0) in vec3 aVertexPosition; // Position du sommet
layout(location = 1) in vec3 aVertexNormal; // Normale du sommet
layout(location = 2) in vec2 aVertexTexCoords; // Coordonnées de texture du sommet

// Matrices de transformations reçues en uniform
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;
uniform float waveTime;

// Sorties du shader
out vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
out vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
out vec2 vTexCoords; // Coordonnées de texture du sommet

//Constantes
const float PI = 3.1415926535897932384626433832795;
const float waveLength = 10.0;
const float waveAmplitude = 1.0;

//Mouvements de l'eau
float generateOffset(float x, float z){
    float radiansX = (x / waveLength + waveTime) * 2.0 * PI;
    float radiansZ = (z / waveLength + waveTime) * 2.0 * PI;
    return waveAmplitude * 0.5 * (sin(radiansZ) + cos(radiansX));
}

vec3 applyDistortion(vec3 vertex){
    float xDistortion = generateOffset(vertex.x, vertex.z);
    float yDistortion = generateOffset(vertex.x, vertex.z);
    float zDistortion = generateOffset(vertex.x, vertex.z);
    return vertex + vec3(xDistortion, yDistortion, zDistortion);
}

void main() {
    // Passage en coordonnées homogènes
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    vec3 currentVertex = aVertexPosition;
    currentVertex = applyDistortion(currentVertex);
    // Calcul des valeurs de sortie
    vPosition_vs = vec3(uMVMatrix * vertexPosition);
    vNormal_vs = vec3(uNormalMatrix * vertexNormal);
    vTexCoords = aVertexTexCoords;

    // Calcul de la position projetée
    gl_Position = uMVPMatrix * vec4(currentVertex, 1.0);
}

//void main(){
//
//    vec3 currentVertex = aVertexPosition;
//    currentVertex = applyDistortion(currentVertex);
//
//    vNormal_vs = vec3(0.0, 1.0, 0.0);
//
//
//    gl_Position = uMVPMatrix * vec4(currentVertex, 1.0);
//
//    vPosition_vs = normalize(currentVertex);
//
//
//}

//void main() {
//    // Passage en coordonnées homogènes
//    vec4 vertexPosition = vec4(aVertexPosition, 1);
//    vec4 vertexNormal = vec4(aVertexNormal, 0);
//
//    // Calcul des valeurs de sortie
//    vPosition_vs = vec3(uMVMatrix * vertexPosition);
//    vNormal_vs = vec3(uNormalMatrix * vertexNormal);
//    vTexCoords = aVertexTexCoords;
//
//    // Calcul de la position projetée
//    gl_Position = uMVPMatrix * vertexPosition;
//}