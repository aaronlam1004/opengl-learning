# version 330 core
out vec4 FragColor;

// in vec4 vertexColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
// uniform vec4 ourColor; // Set in OpenGL

void main()
{
    // FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    // FragColor = vertexColor;
    // FragColor = ourColor;
    FragColor = texture(ourTexture, TexCoord);
}