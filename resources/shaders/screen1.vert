
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

out vec3 vpos;


void main(){

    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;


    vpos = vertexPosition_modelspace;

    // UV of the vertex. No special space for this one.
    UV = vertexUV;

}
