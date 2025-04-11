#version 330 core
layout (location = 0) in vec4 aVertex; // xy position , zw texCoords.

out vec2 texCoords;

uniform mat4 projection;
uniform mat4 model;

void main(){
	texCoords = aVertex.zw;
	gl_Position = projection * model * vec4(aVertex.xy,0.0f,1.0f);
}