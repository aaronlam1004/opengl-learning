# version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D fragTexture;

void main()
{
    FragColor = texture(fragTexture, texCoord) * vec4(vertexColor, 1.0);
}