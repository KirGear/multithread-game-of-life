#pragma once
const char* fragmentShaderSource = R"(
    #version 460 core
    layout(origin_upper_left) in vec4 gl_FragCoord;
    layout(std430, binding = 3) buffer layoutName
    {
        int data_SSBO[];
    };
    out vec4 FragColor;
    uniform ivec2 grid_size;
    uniform float reversed_cell_size;
    uniform float current_scale;
    
    uniform vec2 view_shift;
    
    void main()
    {
        int coord = int(mod((gl_FragCoord.x * current_scale + view_shift.x) * reversed_cell_size, grid_size.x)) + int(mod((gl_FragCoord.y * current_scale + view_shift.y) * reversed_cell_size, grid_size.y))*grid_size.x;
        
        FragColor = vec4(data_SSBO[coord/32], data_SSBO[coord/32], data_SSBO[coord/32], 1);
        //FragColor = vec4(gl_FragCoord.x/1200.0, 1,1,1);
    }
)";