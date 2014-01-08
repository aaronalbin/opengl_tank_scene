
varying vec3 eyePosition;
varying vec3 eyeN;
varying vec3 N;

uniform samplerCube cubemap;
uniform mat4 inverseViewMatrix;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;
uniform vec4 lightPosition;

void main() {
	vec3 incidentEye = normalize(eyePosition);
	vec3 eyeN1 = normalize(eyeN);

	vec3 reflected = reflect(incidentEye, eyeN1);
	reflected = vec3(inverseViewMatrix * vec4(reflected, 0.0));
	vec4 texColor = textureCube(cubemap, reflected);

	vec3 lightColor = vec3(1.0, 1.0, 1.0);  // let la, ld, ls be white
	vec3 L = normalize(vec3(lightPosition - eyePosition));
	vec3 E = normalize(vec3(-eyePosition));
    vec3 R = normalize(-reflect(L, N));  

	vec3 ambient = lightColor * ambientColor;
	vec3 diffuse = lightColor * diffuseColor * max(dot(N, L), 0.0);
	vec3 specular = lightColor * specularColor * pow(max(dot(R, E), 0.0), shininess);
	
	vec4 finalColor = vec4(ambient, 1.0) + vec4(diffuse, 1.0) * texColor + vec4(specular, 1.0) + 0.3 * texColor;

	gl_FragColor = finalColor;
 } 
