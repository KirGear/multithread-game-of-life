#include "Renderer.h"
#include "fragmentShaderSource.h"
#include "vertexShaderSource.h"
#include <format>

Renderer::Renderer(GLFWwindow* window, GameOfLife* gameToRender):
	window(window),
	gameToRender(gameToRender)
{
	int resolution_width;
	glfwGetWindowSize(window, &resolution_width, NULL);
    reversedCellSize = (float)gameToRender->getWidth()/resolution_width;

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    glGenBuffers(1, &ssbo_front);
    glGenVertexArrays(1, &dummyVAO);

    
    grid_size_uniform = glGetUniformLocation(shaderProgram, "grid_size");
    reversed_cell_size_uniform = glGetUniformLocation(shaderProgram, "reversed_cell_size");
    view_shift_uniform = glGetUniformLocation(shaderProgram, "view_shift");
    glUseProgram(shaderProgram);
    glUniform2i(grid_size_uniform, gameToRender->getWidth(), gameToRender->getHeight());
    glUniform1f(reversed_cell_size_uniform, reversedCellSize);
    glUniform2f(view_shift_uniform, 0.0, 0.0);
    

    //view = RenderView(resolution_width, );
    std::cout << "renderer created" << std::endl;
}

Renderer::Renderer() :
	window(NULL),
	gameToRender(NULL),
    reversedCellSize(0)
{}

//Renderer::~Renderer()
//{
//    glBindVertexArray(0);
//    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
//    glDeleteProgram(shaderProgram);
//}

Renderer& Renderer::operator=(const Renderer& other)
{
	this->window = other.window;
	this->gameToRender = other.gameToRender;
	this->reversedCellSize = other.reversedCellSize;
    this->shaderProgram = other.shaderProgram;
    this->ssbo_front = other.ssbo_front;
    this->dummyVAO = other.dummyVAO;

    this->reversed_cell_size_uniform = other.reversed_cell_size_uniform;
    this->grid_size_uniform = other.grid_size_uniform;
    this->view_shift_uniform = other.view_shift_uniform;

    std::cout << "renderer copied" << std::endl;
    std::cout << other.grid_size_uniform <<" ; " << reversed_cell_size_uniform  << std::endl;
    return *this;
}

void Renderer::render()
{
    //std::cout << "rendering" << std::endl;
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    feelSSBO();
    glUseProgram(shaderProgram);
    glBindVertexArray(dummyVAO); 
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
}

void Renderer::feelSSBO()
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo_front);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 4*gameToRender->getHeight()*gameToRender->getWidth(), gameToRender->getCells(), GL_STATIC_READ); //TODO:  4*gameToRender->getHeight()*gameToRender->getWidth() can be optimized
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssbo_front);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind;
}



