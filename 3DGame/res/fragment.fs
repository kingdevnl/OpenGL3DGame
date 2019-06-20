#version 400

out vec4 fragColor;

in vec2 outTexCoord;

uniform sampler2D texture_sampler;

uniform bool hasTexture;

void main(){
if(hasTexture) {
	fragColor = texture(texture_sampler, outTexCoord);
} else {
	fragColor = vec4(0.0, 0.5, 0.5, 1.0);

}

}