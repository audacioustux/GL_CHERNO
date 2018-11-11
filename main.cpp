#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int logLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
        // char* strLog = new char[logLength + 1];
        char* strLog = (char*)alloca(logLength * sizeof(char));
        glGetShaderInfoLog(id, logLength, NULL, strLog);

        std::cout << "faild to Compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << strLog << std::endl;

        // delete[] strLog;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(int argc, char const *argv[])
{
    GLFWwindow* window;
    if(!glfwInit())
        return -1;
    
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if(!window){
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // make context
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress); // Load glad (to work with gl functions)

    std::cout << glGetString(GL_VERSION) << std::endl;

    // GL Code Here
    float position[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };
    unsigned int buffer; 
    glGenBuffers(1, &buffer); // Create VertexBuffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // Bind Buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW); // Store data to VertexBuffer
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    
    std::string vertexShader = "#version 330 core\n"
    "layout(location = 0) in vec4 position;\n"
    "void main(){\n"
    "gl_Position = position;\n"
    "}\n";

    std::string fragmentShader = "#version 330 core\n"
    "layout(location = 0) out vec4 color;\n"
    "void main(){\n"
    "color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);
    
    while(!glfwWindowShouldClose(window)){
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Legacy OpenGL
        // glBegin(GL_TRIANGLES);
        // glVertex2f(-0.5f, -0.5f);
        // glVertex2f( 0.0f, 0.5f);
        // glVertex2f( 0.5f, -0.5f);
        // glEnd();
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
