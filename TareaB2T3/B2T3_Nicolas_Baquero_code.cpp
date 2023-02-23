#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Movimiento | Cubo 1
float movex = -0.5f;
float movey = -0.5f;
float movez = -0.5f;
float factorx = 0.025f;
float factory = 0.0125f;
float factorz = 0.015f;

// Cambio de escala | Cubo 2
float scale = 1.0f;
float scaleFactor = 0.0005f;

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// tiempo
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Nicolás Baquero, 1750147397", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    Shader ourShader("shaders/vshaderB2T3.vs", "shaders/fshaderB2T3.fs");

    float vertices[] = {
        // positions      // texture coords
    -0.5f, -0.5f, -0.5f,  0.936f, 0.3275f, //Cara posterior
     0.5f, -0.5f, -0.5f,  0.72325f, 0.3275f,
     0.5f,  0.5f, -0.5f,  0.72325f, 0.5811f,
     0.5f,  0.5f, -0.5f,  0.72325f, 0.5811f,
    -0.5f,  0.5f, -0.5f,  0.936f, 0.5811f,
    -0.5f, -0.5f, -0.5f,  0.936f, 0.3275f,

    -0.5f, -0.5f,  0.5f,  0.298f, 0.3275f, // Cara Frontal*
     0.5f, -0.5f,  0.5f,  0.50885f, 0.3275f,
     0.5f,  0.5f,  0.5f,  0.50885f, 0.5811f,
     0.5f,  0.5f,  0.5f,  0.50885f, 0.5811f,
    -0.5f,  0.5f,  0.5f,  0.298, 0.5811f,
    -0.5f, -0.5f,  0.5f,  0.298f, 0.3275f,

    -0.5f,  0.5f,  0.5f,  0.298f, 0.5811f, // Cara lateral izquierda*
    -0.5f,  0.5f, -0.5f,  0.085, 0.5811f,
    -0.5f, -0.5f, -0.5f,  0.085f, 0.3275f,
    -0.5f, -0.5f, -0.5f,  0.085f, 0.3275f,
    -0.5f, -0.5f,  0.5f,  0.298f, 0.3275f,
    -0.5f,  0.5f,  0.5f,  0.298f, 0.5811f,

     0.5f,  0.5f,  0.5f,  0.50885f, 0.5811f, // Cara lateral derecha*
     0.5f,  0.5f, -0.5f,  0.72325f, 0.5811f,
     0.5f, -0.5f, -0.5f,  0.72325f, 0.3275f,
     0.5f, -0.5f, -0.5f,  0.72325f, 0.3275f,
     0.5f, -0.5f,  0.5f,  0.50885f, 0.3275f,
     0.5f,  0.5f,  0.5f,  0.50885f, 0.5811f,

    -0.5f, -0.5f, -0.5f,  0.298f, 0.0715f, // Cara inferior*
     0.5f, -0.5f, -0.5f,  0.50885f, 0.0715f,
     0.5f, -0.5f,  0.5f,  0.50885f, 0.3275f,
     0.5f, -0.5f,  0.5f,  0.50885f, 0.3275f,
    -0.5f, -0.5f,  0.5f,  0.298f, 0.3275f,
    -0.5f, -0.5f, -0.5f,  0.298f, 0.0715f,

    -0.5f,  0.5f, -0.5f,  0.298f, 0.8367f, // Cara superior*
     0.5f,  0.5f, -0.5f,  0.50885f, 0.8367f,
     0.5f,  0.5f,  0.5f,  0.50885f, 0.5811f,
     0.5f,  0.5f,  0.5f,  0.50885f, 0.5811f,
    -0.5f,  0.5f,  0.5f,  0.298f, 0.5811f,
    -0.5f,  0.5f, -0.5f,  0.298f, 0.8367f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(3.0f,  6.0f, -10.0f),
        glm::vec3(-4.0f, 3.0f, -6.0f),
        glm::vec3(-4.0f, -2.0f, -5.0f),
        glm::vec3(3.0f, 0.0f, -6.0f),
        glm::vec3(-2.0f,  3.0f, -8.0f)
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture1, texture2;

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("textures/bowser.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("textures/texture2.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use(); 
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
       
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);
		
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        movex += factorx;
        movey += factory;
        movez += factorz;
        if (movex >= 5.0f || movex <= -5.0f) {
            factorx = -factorx;
        }
        if (movey >= 5.0f || movey <= -5.0f) {
            factory = -factory;
        }
        if (movez >= 5.0f || movez <= -5.0f) {
            factorz = -factorz;
        }

        scale += scaleFactor;
        if (scale > 1.5f || scale < 1.0f) {
            scaleFactor = -scaleFactor;
        }

        glBindVertexArray(VAO);
        ourShader.setFloat("textureFlag", 1.0f);
        for (unsigned int i = 0; i < 3; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 30.0f * i;
            if (i == 1) {
                model = glm::translate(model, glm::vec3(movex, movey, movez));
                angle = glfwGetTime() * 90.0f;
            }
            if (i == 2) {
                model = glm::scale(model, glm::vec3(scale, scale, scale));
                angle = glfwGetTime() * -120.0f;
            }
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.5f, 0.7f, 2.5f));
            ourShader.setMat4("model", model);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        ourShader.setFloat("textureFlag", 0.0f);
        for (unsigned int i = 3; i < 6; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 10.0f * i;
            if (i == 4)
                angle = glfwGetTime() * 80.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(2.0f, 4.0f, 0.8f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);    
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
