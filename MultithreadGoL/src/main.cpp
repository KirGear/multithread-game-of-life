#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>

#define NOMINMAX
#include <windows.h>
#include <GameOfLife.h>
#include "FullGame.h"

int main()
{

    FullGame myfullgame(80, 80, 800, 100);
    myfullgame.run();
    
    glfwTerminate();
    return 0;
}

