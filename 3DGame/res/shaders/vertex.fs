#version 400


in vec3 position;
layout (location=2) in vec2 textCoord;
layout (location=3) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;

out vec2 outTexCoord;
out vec3 surfaceNormal;
out vec3 toLightVector;


void main(){
	vec4 worldPos = modelMatrix * vec4(position, 1.f);
	gl_Position =projectionMatrix * viewMatrix * worldPos;
	outTexCoord = textCoord;
	surfaceNormal = (modelMatrix * vec4(normal, 1.0)).xyz;

	toLightVector = lightPosition - worldPos.xyz;


}
