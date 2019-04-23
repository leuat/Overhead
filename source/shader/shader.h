#ifndef SHADER_HPP
#define SHADER_HPP

#include <vector>
#include <string>
using namespace std;

GLuint LoadShaders(vector<string> includes, const char * vertex_file_path,const char * fragment_file_path);

#endif
