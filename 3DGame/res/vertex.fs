#version 400


in vec3 position;
layout (location=2) in vec2 textCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 outTexCoord;


void main(){
	gl_Position =projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.f);
	outTexCoord = textCoord;

}
