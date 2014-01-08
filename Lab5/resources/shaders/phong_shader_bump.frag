
varying vec2 texCoord;
varying vec3 lightVec;
varying vec3 halfVec;
varying vec3 eyeVec;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;
uniform vec4 lightPosition;

uniform sampler2D tex;
uniform sampler2D tex2;

void main() {
	vec3 lightColor = vec3(1.0, 1.0, 1.0);  // let la, ld, ls be white

	vec3 normal = 2.0 * texture2D(tex2, texCoord).rgb - 1.0;
	normal = normalize(normal);

	float lamberFactor = max(dot(lightVec, normal), 0.0);

	vec3 finalColor = vec3(0.0, 0.0, 0.0);
	vec3 ambient = lightColor * ambientColor;

	if (lamberFactor > 0.0) {
		vec4 diffuseMaterial = 0.8*texture2D(tex, texCoord);
		vec3 diffuse = lightColor * diffuseColor * diffuseMaterial.xyz * lamberFactor;

		vec3 specular = lightColor * specularColor * pow(max(dot(halfVec, normal), 0.0), shininess);

		finalColor += diffuse + specular;
	}

	finalColor += ambient;

	gl_FragColor = vec4(finalColor, 1.0);
 } 
