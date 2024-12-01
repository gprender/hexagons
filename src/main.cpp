/**
 * @author Graeme Prendergast 
 */

#include "config.h"


std::string get_shader_log(uint32_t shader)
{
    int log_length = -1;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length < 1)
    {
        return "Failed to get shader log";
    }

    auto log_buffer = new char[log_length];
    glGetShaderInfoLog(shader, log_length, NULL, log_buffer);

    std::string log_string(log_buffer);
    delete[] log_buffer;

    return log_string;
}


bool check_shader_status_successful(uint32_t shaderModule, uint32_t status_type)
{
    int success = 0;
    glGetShaderiv(shaderModule, status_type, &success);

    if (!success)
    {
        std::cout << "Shader status error: " << get_shader_log(shaderModule) << std::endl;
        return false;
    }

    return true;
}


uint32_t make_shader_module(std::string const& filepath, uint32_t module_type)
{
    std::ifstream file;
    std::stringstream buffer;
    std::string line;

    file.open(filepath);
    while (std::getline(file, line))
    {
        buffer << line << std::endl;
    }

    std::string shaderSource = buffer.str();
    const char* shaderSourceCstr = shaderSource.c_str();
    
    uint32_t shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSourceCstr, NULL);
    glCompileShader(shaderModule);

    return check_shader_status_successful(shaderModule, GL_COMPILE_STATUS);
}

uint32_t make_shader(std::string const& vertex_filepath, std::string const& fragment_filepath)
{
    std::vector<uint32_t> modules;
    modules.push_back(make_shader_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_shader_module(fragment_filepath, GL_FRAGMENT_SHADER));

    uint32_t shader = glCreateProgram();
    for (auto const module : modules)
    {
        glAttachShader(shader, module);
    }
    glLinkProgram(shader);
    check_shader_status_successful(shader, GL_LINK_STATUS);

    for (auto const module : modules)
    {
        glDeleteShader(module);
    }

    return shader;
}


int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW failed to start!\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "hello window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);

    // would be best to objectify this, then glDeleteProgram in its destructor
    uint32_t shader_id = make_shader("src/shaders/vertex.txt", "src/shaders/fragment.txt");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_id);
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader_id);
    glfwTerminate();
    return 0;
}

