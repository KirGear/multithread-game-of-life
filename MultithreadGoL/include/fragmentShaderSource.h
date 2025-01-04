#pragma once
const char* fragmentShaderSource = R"(
#version 460 core
layout(origin_upper_left) in vec4 gl_FragCoord;
layout(std430, binding = 3) buffer layoutName
{
    int data_SSBO[];
};
out vec4 FragColor;
uniform vec2 mouse;
void main()
{
    int coord = int(gl_FragCoord.x)/10 + (int(gl_FragCoord.y)/10)*80;
    //int mouse_coord = int(mouse.x)/10 + (int(mouse.y)/10)*80;

    //if (mouse_coord==coord){
    //    data_SSBO[coord] = 1 - data_SSBO[coord];
    //}

    FragColor =  vec4(data_SSBO[coord], data_SSBO[coord], data_SSBO[coord], 1);
}
)";