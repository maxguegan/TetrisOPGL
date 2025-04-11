#version 330 core

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D tex;
uniform vec3 aColor;
void main(){
	vec4 color = vec4(1.0f,1.0f,1.0f,texture(tex,texCoords).r);
	fragColor = color * vec4(aColor,1.0f);
}