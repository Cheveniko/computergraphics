#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture2;
uniform float visible;

void main()
{
    FragColor = mix(texture(texture2, TexCoord), vec4(ourColor, 1.0), visible);
}