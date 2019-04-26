#ifndef SHADER_HPP
#define SHADER_HPP

#include <vector>
#include <string>

#include <GL/glew.h>






using namespace std;

GLuint LoadShaders(vector<const char*> includes, const char * vertex_file_path,const char * fragment_file_path);

#endif
