

varying vec3 N;
varying vec4 eyePosition;
varying vec2 texCoord;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;
uniform vec4 lightPosition;
uniform sampler2D tex;

void main() {
	vec3 lightColor = vec3(1.0, 1.0, 1.0);  // let la, ld, ls be white
	vec3 L = normalize(vec3(lightPosition - eyePosition));
	vec3 E = normalize(vec3(-eyePosition));
    vec3 R = normalize(-reflect(L, N));  

	vec3 ambient = lightColor * ambientColor;
	vec3 diffuse = lightColor * diffuseColor * max(dot(N, L), 0.0);
	vec3 specular = lightColor * specularColor * pow(max(dot(R, E), 0.0), shininess);

	vec4 texColor = texture(tex, texCoord);

	vec4 finalColor = vec4(ambient, 1.0) + vec4(diffuse, 1.0) * texColor + vec4(specular, 1.0) + 0.1 * texColor;

    gl_FragColor = finalColor;
 } 
