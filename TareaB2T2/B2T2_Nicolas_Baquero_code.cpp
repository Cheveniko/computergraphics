#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <learnopengl/shader_s.h>
#include <learnopengl/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Configuración de la ventana
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float visibilityFactor = 0.5f;
float factor = 0.002f;

// Figura 1
float xMov = 0.0f;
float yMov = 0.0f;
float movFactor = 0.005f;
float scale = 1.0f;
float scaleFactor = 0.001f;
float grades = 0.0f;
float gradesXZ = 0.0f;
float rotationFactor = 0.5f;

// Figura 2
float scale2 = 0.5f;
float grades2 = 0.0f;
float movex2 = -0.5f;
float movey2 = -0.5f;
float factorx2 = 0.005f;
float factory2 = 0.0025f;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Nicolas Baquero, 1750147397", NULL, NULL);
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
    
    Shader ourShader1("shaders/vshaderB2T2.vs", "shaders/fshader1B2T2.fs");
    Shader ourShader2("shaders/vshaderB2T2.vs", "shaders/fshader2B2T2.fs");

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
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(2);
    
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //glBindVertexArray(0);
    
    unsigned int texture1, texture2;
    // Textura 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load("textures/texture1.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // Textura 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("textures/texture2.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader1.use();
    
    glUniform1i(glGetUniformLocation(ourShader1.ID, "texture1"), 0);
    
    ourShader2.use();
    ourShader2.setInt("texture2", 1);
    
    
    // Bucle de renderizado
    
    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        // Figura 1 (Control por teclado)
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(xMov, yMov, 0.0f));
        transform = glm::rotate(transform, glm::radians(grades), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::rotate(transform, glm::radians(gradesXZ), glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(scale, scale, scale));

        visibilityFactor = visibilityFactor + factor;
        if (visibilityFactor >= 1.0f) {
            visibilityFactor = 1.0f;
            factor = (-1.0f) * factor;
        }
        if (visibilityFactor <= 0.0f) {
            visibilityFactor = 0.0f;
            factor = (-1.0f) * factor;
        }

        ourShader1.setFloat("visible", visibilityFactor);
        ourShader1.use();
        unsigned int transformLoc1 = glGetUniformLocation(ourShader1.ID, "transform");
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);

        ourShader2.setFloat("visible", visibilityFactor);
        ourShader2.use();
        unsigned int transformLoc2 = glGetUniformLocation(ourShader2.ID, "transform");
        glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawElements(GL_TRIANGLES, 21, GL_UNSIGNED_INT, (GLvoid*)(6 * sizeof(GLfloat)));
        
        // Figura 2
        grades2 += 1.0f;
        movex2 += factorx2;
        movey2 += factory2;
        if (movex2 >= 1.0f || movex2 <= -1.0f) {
            factorx2 = -factorx2;
        }
        if (movey2 >= 1.0f || movey2 <= -1.0f) {
            factory2 = -factory2;
        }

        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(movex2, movey2, 0.0f));
        transform = glm::rotate(transform, glm::radians(grades2), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(scale2, scale2, scale2));

        ourShader1.use();
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
        ourShader2.use();
        glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawElements(GL_TRIANGLES, 21, GL_UNSIGNED_INT, (GLvoid*)(6 * sizeof(GLfloat)));
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);


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
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Movimiento en Y positivo
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        yMov += movFactor;
        if (yMov > 1.0f) {
            yMov = 1.0f;
        }
    }
    // Movimiento en Y negativo
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        yMov -= movFactor;
        if (yMov < -1.0f) {
            yMov = -1.0f;
        }
    }
    // Movimiento en X positivo
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        xMov += movFactor;
        if (xMov > 1.0f) {
            xMov = 1.0f;
        }
    }
    // Movimiento en X negativo
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        xMov -= movFactor;
        if (xMov < -1.0f) {
            xMov = -1.0f;
        }
    }
    // Aumento en la escala
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        scale += scaleFactor;
    }
    // Reduccion en la escala
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        scale -= scaleFactor;
    }
    // Rotacion en sentido antihorario
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        grades += rotationFactor;
    // Rotacion en sentido horario
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        grades -= rotationFactor;
    // Rotacion en eje XZ (Sentido Antihorario)
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        gradesXZ += rotationFactor;
    // Rotacion en eje XZ (Sentido Horario)
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        gradesXZ -= rotationFactor;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
