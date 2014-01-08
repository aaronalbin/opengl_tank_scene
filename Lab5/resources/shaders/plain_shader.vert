
attribute vec4 vertexPosition;
uniform vec3 vertexColor;
uniform mat4 MVP; // modelview projection

void main() {
    gl_Position = MVP * vertexPosition;
}
