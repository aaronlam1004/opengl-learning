# version 330 core
out vec4 FragColor;

in vec4 vertexColor;
uniform vec4 ourColor; // Set in OpenGL

void main()
{
    // FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    // FragColor = vertexColor;
    FragColor = ourColor;
}