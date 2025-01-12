# version 330 core
out vec4 FragColor;

in vec3 VertexColor;
in vec2 TexCoord;

uniform sampler2D fragTexture;

void main()
{
    FragColor = texture(fragTexture, TexCoord) * vec4(VertexColor, 1.0);
}
