#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>

#define NOMINMAX
#include <windows.h>
#include <GameOfLife.h>
#include "FullGame.h"

int main()
{

    FullGame myfullgame(100, 100, 800, 100);
    myfullgame.run(3);
    
    glfwTerminate();
    return 0;
}

