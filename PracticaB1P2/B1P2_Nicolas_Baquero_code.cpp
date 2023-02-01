#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Configuración de la ventana
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Definición de la fuente del vertex shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Definición de las fuentes de los fragment shaders
//Creamos cuantos fragment shaders sean necesarios para realizar nuestra figura, en este caso, cada fragment shader propporcionará un color diferente
const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.423f, 0.713f, 0.329f, 1.0f);\n"
"}\n\0";
const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.76f, 0.2f, 1.0f);\n"
"}\n\0";
const char* fragmentShader3Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.321f, 0.109f, 0.69f, 1.0f);\n"
"}\n\0";
const char* fragmentShader4Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.505f, 0.2f, 1.0f);\n"
"}\n\0";
const char* fragmentShader5Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.882f, 0.415f, 0.4f, 1.0f);\n"
"}\n\0";
const char* fragmentShader6Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.227f, 0.525f, 1.0f, 1.0f);\n"
"}\n\0";
const char* fragmentShader7Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.447f, 0.611f, 0.266f, 1.0f);\n"
"}\n\0";

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
    
    //Generación de un shader object de tipo VERTEX, se guarda su ID en la variable vertexShader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Se especifica el código fuente del shader object.
    glCompileShader(vertexShader); //Se compila el código fuente del vertexShader
    
    //Se verifica si la compilación fue correcta o no.
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER); //Declaramos el primer shader object de tipo FRAGMENT y guardamos su ID en la variable fragmentShader
    glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShader1); //Se compila el código fuente del fragment shader
    
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShader2);
    
    unsigned int fragmentShader3 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader3, 1, &fragmentShader3Source, NULL);
    glCompileShader(fragmentShader3);
    
    unsigned int fragmentShader4 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader4, 1, &fragmentShader4Source, NULL);
    glCompileShader(fragmentShader4);
    
    unsigned int fragmentShader5 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader5, 1, &fragmentShader5Source, NULL);
    glCompileShader(fragmentShader5);
    
    unsigned int fragmentShader6 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader6, 1, &fragmentShader6Source, NULL);
    glCompileShader(fragmentShader6);
    
    unsigned int fragmentShader7 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader7, 1, &fragmentShader7Source, NULL);
    glCompileShader(fragmentShader7);
    
    //Se define el shader program que nos servirá para unir el vertex shader y el fragment shader
    unsigned int shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader); //Enlazamos el shader program con el vertex shader
    glAttachShader(shaderProgram1, fragmentShader1); //Enlazamos el shader program con el fragment shader
    glLinkProgram(shaderProgram1); //Enlaza el vertex y fragment shader (Linking)
    
    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    
    unsigned int shaderProgram3 = glCreateProgram();
    glAttachShader(shaderProgram3, vertexShader);
    glAttachShader(shaderProgram3, fragmentShader3);
    glLinkProgram(shaderProgram3);
    
    unsigned int shaderProgram4 = glCreateProgram();
    glAttachShader(shaderProgram4, vertexShader);
    glAttachShader(shaderProgram4, fragmentShader4);
    glLinkProgram(shaderProgram4);
    
    unsigned int shaderProgram5 = glCreateProgram();
    glAttachShader(shaderProgram5, vertexShader);
    glAttachShader(shaderProgram5, fragmentShader5);
    glLinkProgram(shaderProgram5);
    
    unsigned int shaderProgram6 = glCreateProgram();
    glAttachShader(shaderProgram6, vertexShader);
    glAttachShader(shaderProgram6, fragmentShader6);
    glLinkProgram(shaderProgram6);
    
    unsigned int shaderProgram7 = glCreateProgram();
    glAttachShader(shaderProgram7, vertexShader);
    glAttachShader(shaderProgram7, fragmentShader7);
    glLinkProgram(shaderProgram7);
    
    glDeleteShader(vertexShader); // Una vez generados los shader programs el vertex shader ya no es necesario asi que se puede eliminar para liberar recursos.
    glDeleteShader(fragmentShader1); //  Una vez generados los shader programs los fragment shaders ya no son necesarios asi que se pueden eliminar para liberar recursos.
    glDeleteShader(fragmentShader2);
    glDeleteShader(fragmentShader3);
    glDeleteShader(fragmentShader4);
    glDeleteShader(fragmentShader5);
    glDeleteShader(fragmentShader6);
    glDeleteShader(fragmentShader7);
    
    // Se define el arreglo de vértices a utilizar
    float vertices[] = {
        1.0f, 0.0f, 0.0f, // A
        0.5f, 0.8f, 0.0f, // B
        0.5f, 0.0f, 0.0f, // C
        0.0f, 0.0f, 0.0f, // D
        0.1f, 0.2f, 0.0f, // E
        0.3f, 0.5f, 0.0f, // F
        0.0f, 0.8f, 0.0f, // G
        -0.2f, 0.5f, 0.0f, // H
        -0.4f, 0.2f, 0.0f, // I
        -0.7f, 0.2f, 0.0f, // J
        -0.4f, 0.7f, 0.0f, // K
        -0.2f, 1.0f, 0.0f // L
    };
    // Se definen los índices a utilizar
    unsigned int indices[]{
        0, 1, 2, // 1
        1, 2, 3, // 2
        4, 5, 7, // 3
        4, 7, 8, // 4
        5, 6, 7, // 5
        6, 7, 11, // 6
        7, 10, 11, //7
        7, 8, 10, //8
        8, 9, 10 //9
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
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    
    // Bucle de renderizado

    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1); //Ejecutamos el shader program
        glBindVertexArray(VAO); //Enlazamos el vertex Array con la información de los vértices en el VAO
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); //Se empieza a dibujar las primitivas mediante indices
        
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*) (3*sizeof(float)));
        
        glUseProgram(shaderProgram3);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) (6*sizeof(float)));
        
        glUseProgram(shaderProgram4);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*) (12*sizeof(float)));
        
        glUseProgram(shaderProgram5);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) (15*sizeof(float)));
        
        glUseProgram(shaderProgram6);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*) (21*sizeof(float)));
        
        glUseProgram(shaderProgram7);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*) (24*sizeof(float)));
        
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
