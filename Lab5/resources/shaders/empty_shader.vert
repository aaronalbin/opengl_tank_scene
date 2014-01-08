
attribute vec4 vertexPosition;
attribute vec3 vertexNormal;

varying vec3 N;
varying vec4 eyePosition;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;
uniform vec4 lightPosition;

uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
uniform mat4 MVP; // modelview projection

void main() {
	eyePosition = modelViewMatrix * vertexPosition;
    N = normalize(vec3(normalMatrix * vec4(vertexNormal, 1.0)));

    gl_Position = MVP * vertexPosition;
}
