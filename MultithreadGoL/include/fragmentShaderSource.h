#pragma once
const char* fragmentShaderSource = R"(
    #version 460 core
    layout(origin_upper_left) in vec4 gl_FragCoord;
    layout(std430, binding = 3) buffer layoutName
    {
        int data_SSBO[];
    };
    out vec4 FragColor;
    uniform int grid_width;
    uniform float reversed_cell_size;
    
    void main()
    {
        int coord = int(gl_FragCoord.x * reversed_cell_size) + int(gl_FragCoord.y * reversed_cell_size)*grid_width;
        
        FragColor = vec4(data_SSBO[coord], data_SSBO[coord], data_SSBO[coord], 1);
    }
)";