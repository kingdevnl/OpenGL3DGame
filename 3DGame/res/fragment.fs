#version 400

out vec4 fragColor;

in vec2 outTexCoord;

uniform sampler2D texture_sampler;

void main(){
    fragColor = vec4(0.0, 0.5, 0.5, 1.0);
	fragColor = texture(texture_sampler, outTexCoord);
}