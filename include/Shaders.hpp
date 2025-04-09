#pragma once

#include <Shader.hpp>

Shader HELLO_TRIANGLE_SHADER;
Shader RED_TRIANGLE_SHADER;
Shader UNIFORM_SHADER;
Shader INTERPOLATION_SHADER;
Shader TEXTURE_SHADER;
Shader COLOR_MASK_TEXTURE_SHADER;
Shader TEXTURES_COMBINED_SHADER;
Shader TRANSFORMATIONS_SHADER;
Shader COORDINATE_SYSTEM_SHADER;

void loadShaders_Scene0(void)
{
    HELLO_TRIANGLE_SHADER.load("shaders/hello_triangle/shader.vert", "shaders/hello_triangle/shader.frag");
    RED_TRIANGLE_SHADER.load("shaders/red_triangle/shader.vert", "shaders/red_triangle/shader.frag");
    UNIFORM_SHADER.load("shaders/shaders_uniform/shader.vert", "shaders/shaders_uniform/shader.frag");
    INTERPOLATION_SHADER.load("shaders/shaders_interpolation/shader.vert", "shaders/shaders_interpolation/shader.frag");
    TEXTURE_SHADER.load("shaders/textures/shader.vert", "shaders/textures/shader.frag");
    COLOR_MASK_TEXTURE_SHADER.load("shaders/color_mask_textures/shader.vert", "shaders/color_mask_textures/shader.frag");
    TEXTURES_COMBINED_SHADER.load("shaders/textures_combined/shader.vert", "shaders/textures_combined/shader.frag");
    TRANSFORMATIONS_SHADER.load("shaders/transformations/shader.vert", "shaders/transformations/shader.frag");
    COORDINATE_SYSTEM_SHADER.load("shaders/coordinate_systems/shader.vert", "shaders/coordinate_systems/shader.frag");
}

Shader LIGHT_SHADER;
Shader LIGHTED_CUBE_SHADER;
Shader COLORED_LIGHT_SHADER;
Shader MATERIAL_CUBE_SHADER;

void loadShaders_Scene1(void)
{
    LIGHT_SHADER.load("shaders/basic_lighting/lightShader.vert", "shaders/basic_lighting/lightShader.frag");
    LIGHTED_CUBE_SHADER.load("shaders/basic_lighting/shader.vert", "shaders/basic_lighting/shader.frag");
    COLORED_LIGHT_SHADER.load("shaders/material/lightShader.vert", "shaders/material/lightShader.frag");
    MATERIAL_CUBE_SHADER.load("shaders/material/shader.vert", "shaders/material/shader.frag");
}
