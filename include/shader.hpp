#include <glad/glad.h>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
class Shader {
public:
    Shader(std::string path, GLenum shader_type);
    void CreateShader();
    void CompileShader();
    void DeleteShader();
    GLuint getId() const;
private:
    GLenum m_type;
    GLuint m_id;
    std::string m_path;
    std::string m_source;
};