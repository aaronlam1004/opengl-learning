float TRIANGLE_VERTICES[] = {
    // aPos(xyz)
    -0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
};

float COLORED_TRIANGLE_VERTICES[] = {
    // aPos (xyz)       // aColor (RGB)
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f
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

float TEXTURED_CONTAINER_VERTICES[] = {
     // aPos (xyz)      //aTexCoord (xy)
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
};

unsigned int SQUARE_INDICES[] = {
    0, 1, 3, // 1st triangle
    1, 2, 3  // 2nd triangle
};

const char* SHADER_FILES[][2] = {
    { "shaders/hello_triangle/shader.vert", "shaders/hello_triangle/shader.frag" },
    { "shaders/red_triangle/shader.vert", "shaders/red_triangle/shader.frag" },
    { "shaders/shaders_uniform/shader.vert", "shaders/shaders_uniform/shader.frag" },
    { "shaders/shaders_interpolation/shader.vert", "shaders/shaders_interpolation/shader.frag" },
    { "shaders/textures/shader.vert", "shaders/textures/shader.frag" },
    { "shaders/color_mask_textures/shader.vert", "shaders/color_mask_textures/shader.frag" },
    { "shaders/textures_combined/shader.vert", "shaders/textures_combined/shader.frag" },
    { "shaders/transformations/shader.vert", "shaders/transformations/shader.frag" },
    { "shaders/coordinate_systems/shader.vert", "shaders/coordinate_systems/shader.frag" },
};

const char* TEXTURE_FILES[] = {
    "resources/textures/container.jpg",
    "resources/textures/awesomeface.png",
};
