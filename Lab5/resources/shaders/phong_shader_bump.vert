
attribute vec4 vertexPosition;
attribute vec3 vertexNormal;
attribute vec2 vertexTexture;
attribute vec3 vertexTangent;

varying vec2 texCoord;
varying vec3 lightVec;
varying vec3 halfVec;
varying vec3 eyeVec;

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shininess;
uniform vec4 lightPosition;

uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
uniform mat4 MVP; // modelview projection
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	vec3 pos = vec3(modelViewMatrix * vertexPosition);

    vec3 N = normalize(vec3(normalMatrix * vec4(vertexNormal, 1.0)));
	vec3 T = normalize(vec3(normalMatrix * vec4(vertexTangent, 1.0)));
	vec3 B = normalize(cross(N, T));

	vec3 lightDir = normalize(lightPosition.xyz - vertexPosition.xyz);

	vec3 v;
	v.x = dot (lightDir, T);
	v.y = dot (lightDir, B);
	v.z = dot (lightDir, N);
	lightVec = normalize(v);
	
	v.x = dot (vertexPosition.xyz, T);
	v.y = dot (vertexPosition.xyz, B);
	v.z = dot (vertexPosition.xyz, N);
	eyeVec = normalize(v);
	
	//vertexPosition = normalize(vertexPosition);

	// No need to divide by two, the result is normalized anyway.
	// vec3 halfVector = normalize((vertexPosition + lightDir) / 2.0); 
	vec3 halfVector = normalize(vertexPosition.xyz + lightDir);
	v.x = dot (halfVector, T);
	v.y = dot (halfVector, B);
	v.z = dot (halfVector, N);

	// No need to normalize, t,b,n and halfVector are normal vectors.
	//normalize (v);
	halfVec = v; 

	texCoord = vertexTexture;
    gl_Position = MVP * vertexPosition;
}
