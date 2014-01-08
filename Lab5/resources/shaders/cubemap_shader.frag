
varying vec3 texCoord;
uniform samplerCube cubemap;

void main() {
	gl_FragColor = textureCube(cubemap, normalize(texCoord));
 } 
