#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>


#include <GL/glew.h>

#include "source/shader/shader.h"
namespace LShaders {
#include "resources/shaders/out/scenePlanet_frag.h"
#include "resources/shaders/out/scenePlanet_vert.h"
#include "resources/shaders/out/raymarcherinc_frag.h"
#include "resources/shaders/out/scene1_frag.h"
#include "resources/shaders/out/scene1_vert.h"
#include "resources/shaders/out/screen1_frag.h"
#include "resources/shaders/out/screen1_vert.h"
#include "resources/shaders/out/glyph_frag.h"
#include "resources/shaders/out/glyph_vert.h"
}

//GLuint LoadShaders(vector<string> includes, const char * vertex_file_path,const char * fragment_file_path){
    GLuint LoadShaders(vector<const char*> includes, const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
    std::string VertexShaderCode(vertex_file_path);
/*	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}else{
       printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
		return 0;
	}
*/
	// Read the Fragment Shader code from the file

    includes.push_back(fragment_file_path);

    std::stringstream sstr;
    std::string FragmentShaderCode;
    for (const char* s: includes) {
/*        std::ifstream FragmentShaderStream(s, std::ios::in);
        if(FragmentShaderStream.is_open()){
            sstr << FragmentShaderStream.rdbuf();
            FragmentShaderStream.close();
        }*/
        string f(s);
        sstr<<f;
    }
    GLint Result = GL_FALSE;
	int InfoLogLength;

    FragmentShaderCode = sstr.str();


	// Compile Vertex Shader
#ifdef IS_DEBUG
//    printf("Compiling shader : %s\n", vertex_file_path);
#endif
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

#ifdef IS_DEBUG
    // Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("Error compiling vertex shader : %s\n", vertex_file_path);

		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
#endif


	// Compile Fragment Shader
#ifdef IS_DEBUG
  //  printf("Compiling shader : %s\n", fragment_file_path);
#endif
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
#ifdef IS_DEBUG

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("Error compiling fragment shader : %s\n", fragment_file_path);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

#endif

	// Link the program
#ifdef IS_DEBUG
//    printf("Linking program\n");
#endif
    GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

#ifdef IS_DEBUG
    // Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

#endif
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
