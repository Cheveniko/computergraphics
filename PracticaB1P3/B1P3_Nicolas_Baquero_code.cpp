#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>
#include <cmath>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Configuración de la ventana
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // Inicialización de glfw y configuración inicial
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CG Exercise C", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    Shader ourShader("shaders/vshaderB1P3.vs", "shaders/fshaderB1P3.fs");
    
    // Se define el arreglo de vértices y colores a utilizar
    float vertices[] = {
        //posición       //color
        1.0f, 0.0f, 0.0f, 0.556f, 1.0f, 0.0f, // A
        0.5f, 0.8f, 0.0f, 0.658f, 1.0f, 0.0f, // B
        0.5f, 0.0f, 0.0f, 0.760f, 1.0f, 0.0f, // C

        0.5f, 0.8f, 0.0f, 0.988f, 1.0f, 0.513f, // B
        0.5f, 0.0f, 0.0f, 0.992f, 0.949f, 0.364f, // C
        0.0f, 0.0f, 0.0f, 0.976, 0.913f, 0.035f, // D

        0.1f, 0.2f, 0.0f, 0.792f, 0.411f, 0.890f, // E
        0.3f, 0.5f, 0.0f, 0.662f, 0.325f, 0.866f, // F
        -0.2f, 0.5f, 0.0f, 0.611f, 0.058f, 0.749f,  // H
        -0.4f, 0.2f, 0.0f, 0.552f, 0.039f, 0.615f, // I
        
        0.3f, 0.5f, 0.0f, 0.941f, 0.407f, 0.219f, // F
        -0.2f, 0.5f, 0.0f, 0.941f, 0.596f, 0.188f,  // H
        0.0f, 0.8f, 0.0f, 0.847f, 0.282f, 0.345f, // G
        
        -0.2f, 0.5f, 0.0f, 1.0, 0.6f, 0.8f,  // H
        0.0f, 0.8f, 0.0f, 1.0, 0.337f, 0.533f, // G
        -0.2f, 1.0f, 0.0f, 1.0, 0.2f, 0.466f,  // L
        -0.4f, 0.7f, 0.0f, 1.0f, 0.733f, 0.933f, // K
        
        -0.2f, 0.5f, 0.0f, 0.282f, 0.827f, 1.0f,  // H
        -0.4f, 0.7f, 0.0f, 0.219f, 0.764f, 1.0f, // K
        -0.4f, 0.2f, 0.0f, 0.031f, 0.576f, 0.811f, // I
        
        -0.4f, 0.2f, 0.0f, 0.603f, 0.996f, 0.180f, // I
        -0.7f, 0.2f, 0.0f, 0.301f, 0.498f, 0.09f, // J
        -0.4f, 0.7f, 0.0f, 0.419f, 0.694f, 0.125f, // K
        
    };
    // Se definen los índices a utilizar
    unsigned int indices[]{
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        6, 8, 9,
        10, 11, 12,
        13, 14, 15,
        13, 15, 16,
        17, 18, 19,
        20, 21, 22
    };
    
    unsigned int VBO, VAO, EBO; //Asignación de un espacio de memoria para VBO, VAO y EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    
    // Bucle de renderizado
    
    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);
        
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Utilizamos nuestro shader program
        ourShader.use();
        
        float timeValue = glfwGetTime();
        float timeColor = (sin(timeValue)/2 - 0.25);
        int vertexColorLocation = glGetUniformLocation(ourShader.ID, "timeColor");
        glUniform4f(vertexColorLocation, timeColor * 0.1f, timeColor * 0.3f, timeColor * 0.2f, 1.0f);
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, (GLvoid*)0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
//   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
