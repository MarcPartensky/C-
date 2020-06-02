#include "Shader.h"


Shader::Shader():
vertexID(0), fragmentID(0), programID(0), vertexSource(), fragmentSource()
{}

Shader::Shader(Shader const &shader) {
    vertexSource = shader.vertexSource;
    fragmentSource = shader.fragmentSource;
    load();
}

Shader::Shader(std::string vertexSource, std::string fragmentSource):
vertexID(0), fragmentID(0), programID(0),
vertexSource(vertexSource), fragmentSource(fragmentSource)
{}


Shader::~Shader() {
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
    glDeleteProgram(programID);
}


// MŽthodes

Shader& Shader::operator=(Shader const &shader) {
    vertexSource = shader.vertexSource;
    fragmentSource = shader.fragmentSource;
    load();
    return *this;
}

bool Shader::load()
{
    std::cout <<  "Destroying potential old shader." << std::endl;
    std::cout << vertexID << std::endl;
    
    if(glIsShader(vertexID) == GL_TRUE)
        glDeleteShader(vertexID);

    if(glIsShader(fragmentID) == GL_TRUE)
        glDeleteShader(fragmentID);

    if(glIsProgram(programID) == GL_TRUE)
        glDeleteProgram(programID);
    
    std::cout << "Compilation of shaders" << std::endl;
    if(!compilerShader(vertexID, GL_VERTEX_SHADER, vertexSource))
        return false;
    if(!compilerShader(fragmentID, GL_FRAGMENT_SHADER, fragmentSource))
        return false;
    
    std::cout << "Creation of the program" << std::endl;
    programID = glCreateProgram();
    // Association des shaders
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);

    // Verrouillage des entrŽes shader
    glBindAttribLocation(programID, 0, "in_Vertex");
    glBindAttribLocation(programID, 1, "in_Color");
    glBindAttribLocation(programID, 2, "in_TexCoord0");

    // Linkage du programme
    glLinkProgram(programID);

    // VŽrification du linkage
    GLint errorLink(0);
    glGetProgramiv(programID, GL_LINK_STATUS, &errorLink);

    if(errorLink != GL_TRUE) {
        GLint errorSize(0);
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &errorSize);
        char *error = new char[errorSize + 1];
        glGetShaderInfoLog(programID, errorSize, &errorSize, error);
        error[errorSize] = '\0';
        std::cout << error << std::endl;
        delete[] error;
        glDeleteProgram(programID);
        return false;
    }
    else
        std::cout << "Shader loaded successfully." << std::endl;
        return true;
}


bool Shader::compilerShader(GLuint &shader, GLenum type, std::string const &sourceFile)
{
    std::cout << "Creation of the shader" << std::endl;
    shader = glCreateShader(type);
    if(shader == 0) {
        std::cout << "Error the type (" << type << ") doesn't exist." << std::endl;
        return false;
    }
    std::ifstream file(sourceFile.c_str());
    if(!file) {
        std::cout << "Error the file (" << sourceFile << ") cannot be found." << std::endl;
        glDeleteShader(shader);
        return false;
    }
    std::string line;
    std::string sourceCode;
    while(getline(file, line))
        sourceCode += line + '\n';
    file.close();

    const GLchar* sourceCodeString = sourceCode.c_str();

    glShaderSource(shader, 1, &sourceCodeString, 0);
    glCompileShader(shader);

    GLint compilationError(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationError);

    if(compilationError != GL_TRUE)
    {
        GLint sizeError(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &sizeError);
        char *error = new char[sizeError + 1];
        glGetShaderInfoLog(shader, sizeError, &sizeError, error);
        error[sizeError] = '\0';
        std::cout << "Compilation error:" << error << std::endl;
        delete[] error;
        glDeleteShader(shader);
        return false;
    }
    else
        std::cout << "Shader compiled successfully." << std::endl;
        return true;
}


GLuint Shader::getProgramID() const
{
    return programID;
}
