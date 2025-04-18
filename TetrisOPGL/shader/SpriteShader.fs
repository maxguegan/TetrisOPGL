#version 330 core

in vec2 texCoords;

out vec4 fragColor;

uniform vec4 aColor;
uniform sampler2D tex;

void main(){
	vec4 color = texture(tex,texCoords);
	if(color.x >= 0.99 && color.y >= 0.99 && color.z >= 0.99 && color.w >= 0.99)
		discard;
	color = color * aColor;
	fragColor = color;
}