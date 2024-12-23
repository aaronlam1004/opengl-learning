# version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D containerTexture;
uniform sampler2D faceTexture;

void main()
{
    FragColor = mix(texture(containerTexture, texCoord), texture(faceTexture, texCoord), 0.5);
}