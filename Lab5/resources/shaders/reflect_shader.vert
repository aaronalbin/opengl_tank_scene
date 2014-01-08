
attribute vec4 vertexPosition;
attribute vec3 vertexNormal;

varying vec3 eyePosition;
varying vec3 eyeN;
varying vec3 N;

uniform mat4 normalMatrix;
uniform mat4 MVP; // modelview projection
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;

void main() {

	eyePosition = vec3(modelViewMatrix * vertexPosition);
	eyeN = vec3(modelViewMatrix * vec4(vertexNormal, 0.0));
	N = normalize(vec3(normalMatrix * vec4(vertexNormal, 1.0)));

    gl_Position = MVP * vertexPosition;
}
