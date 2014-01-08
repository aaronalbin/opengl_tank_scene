

varying vec3 N;
varying vec4 eyePosition;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;
uniform vec4 lightPosition;

void main() {
	vec3 lightColor = vec3(1.0, 1.0, 1.0);  // let la, ld, ls be white
	vec3 L = normalize(vec3(lightPosition - eyePosition));
	vec3 E = normalize(vec3(-eyePosition));
    vec3 R = normalize(-reflect(L, N));  

	vec3 ambient = lightColor * ambientColor;
	vec3 diffuse = lightColor * diffuseColor * max(dot(N, L), 0.0);
	vec3 specular = lightColor * specularColor * pow(max(dot(R, E), 0.0), shininess);
	vec3 finalColor = ambient + diffuse + specular;

	//gl_FragColor = vec4(finalColor, 1.0);
 } 
