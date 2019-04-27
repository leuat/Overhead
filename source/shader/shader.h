#ifndef SHADER_HPP
#define SHADER_HPP

#include <vector>
#include <string>

#include <GL/glew.h>


namespace LShaders
{
    extern char scenePlanet_frag[];
    extern char scenePlanet_vert[];
    extern char scene1_vert[];
    extern char scene1_frag[];
    extern char screen1_vert[];
    extern char screen1_frag[];
    extern char glyph_vert[];
    extern char glyph_frag[];

    extern char raymarcherinc[];

};


using namespace std;

GLuint LoadShaders(vector<const char*> includes, const char * vertex_file_path,const char * fragment_file_path);

#endif
