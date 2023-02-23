#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float textureFlag;

void main()
{
	if(textureFlag==1.0f){
		FragColor = texture(texture1, TexCoord);
	}
	else{
		FragColor = texture(texture2, TexCoord);
	}	
}