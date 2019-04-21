#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 pos;

// Ouput data
out vec3 color;

uniform mat4x4 invVP;
uniform mat4x4 viewMat, projMat;
// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;


uniform vec3 camera, target;
float fov;

vec3 coord2ray() {
    float xx = UV.x;
    float yy = UV.y;

    vec4 screenPos = vec4(xx, -yy, 1.0, 1.0);
    vec4 worldPos = invVP *screenPos;
    return normalize(worldPos.xyz);
}


void main(){

        // Output color = color of the texture at the specified UV
        //color = texture( myTextureSampler, UV ).rgb;

        vec3 ray = coord2ray();
        color = vec3(ray.x, ray.y,ray.z);
}
