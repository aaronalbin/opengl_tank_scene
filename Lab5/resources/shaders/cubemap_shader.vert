
attribute vec4 vertexPosition;

varying vec3 texCoord;

uniform mat4 MVP; // modelview projection

void main() {
	texCoord = vertexPosition.xyz;
    gl_Position = MVP * vertexPosition;
}
