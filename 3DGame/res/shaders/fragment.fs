#version 400

out vec4 fragColor;

in vec2 outTexCoord;
in vec3 surfaceNormal;
in vec3 toLightVector;


uniform sampler2D texture_sampler;
uniform vec3 lightColour;

uniform bool hasTexture;

void main(){
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(lightColour);
	float nDot1 = dot(unitNormal, unitLightVector);
	float brightness = max(nDot1, 0.0);

	vec3 diffuse = brightness * lightColour;
	if(!hasTexture) {
		fragColor = vec4(diffuse, 1.0) * vec4(0.0, 0.5, 0.5, 1.0);
	} else {
		fragColor = vec4(diffuse, 1.0) * texture(texture_sampler, outTexCoord);
	}




}