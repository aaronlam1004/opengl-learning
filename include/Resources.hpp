float TRIANGLE_VERTICES[] = {
    // aPos(xyz)
    -0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
};

float SQUARE_VERTICES[] = {
     // aPos(xyz)
     0.5f,  0.5f, 0.0f, // top right
     0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,	// top left
};

float CONTAINER_VERTICES[] = {
     // aPos (xyz)      // aColor (RGB)   //aTexCoord (xy)
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left 
};

unsigned int SQUARE_INDICES[] = {
    0, 1, 3, // 1st triangle
    1, 2, 3  // 2nd triangle
};

const char* SHADER_FILES[][2] = {
    { "shaders/hello_triangle/shader.vert", "shaders/hello_triangle/shader.frag" }
};

const char* TEXTURE_FILES[] = {
    "resources/textures/container.jpg"
};
