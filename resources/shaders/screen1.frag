#version 330 core

// Ouput data
out vec3 color;
in vec2 UV;
uniform sampler2D renderedTexture;


#pragma parameter CURVATURE_X "Screen curvature - horizontal" 0.10 0.0 1.0 0.01
#pragma parameter CURVATURE_Y "Screen curvature - vertical" 0.15 0.0 1.0 0.01
#pragma parameter MASK_BRIGHTNESS "Mask brightness" 0.70 0.0 1.0 0.01
#pragma parameter SCANLINE_WEIGHT "Scanline weight" 6.0 0.0 15.0 0.1
#pragma parameter SCANLINE_GAP_BRIGHTNESS "Scanline gap brightness" 0.12 0.0 1.0 0.01
#pragma parameter BLOOM_FACTOR "Bloom factor" 1.5 0.0 5.0 0.01
#pragma parameter INPUT_GAMMA "Input gamma" 2.4 0.0 5.0 0.01
#pragma parameter OUTPUT_GAMMA "Output gamma" 2.2 0.0 5.0 0.01

// Haven't put these as parameters as it would slow the code down.
#define SCANLINES
#define MULTISAMPLE
#define GAMMA
//#define FAKE_GAMMA
//#define CURVATURE
//#define SHARPER
// MASK_TYPE: 0 = none, 1 = green/magenta, 2 = trinitron(ish)
#define MASK_TYPE 1


#ifdef GL_ES
#define COMPAT_PRECISION mediump
precision mediump float;
#else
#define COMPAT_PRECISION
#endif

//#define CURVATURE_X 0.10
//#define CURVATURE_Y 0.25
#define CURVATURE_X 0.30
#define CURVATURE_Y 0.65
#define MASK_BRIGHTNESS 0.70
#define SCANLINE_WEIGHT 6.0
#define SCANLINE_GAP_BRIGHTNESS 0.12
#define BLOOM_FACTOR 1.5
#define INPUT_GAMMA 2.4
#define OUTPUT_GAMMA 2.2

/* COMPATIBILITY
   - GLSL compilers
*/

uniform vec2 TextureSize;
#if defined(CURVATURE)
varying vec2 screenScale;
#endif
varying vec2 TEX0;
float filterWidth = 0.5;

float CalcScanLineWeight(float dist)
{
        return max(1.0-dist*dist*SCANLINE_WEIGHT, SCANLINE_GAP_BRIGHTNESS);
}

float CalcScanLine(float dy)
{
        float scanLineWeight = CalcScanLineWeight(dy);
#if defined(MULTISAMPLE)
        scanLineWeight += CalcScanLineWeight(dy-filterWidth);
        scanLineWeight += CalcScanLineWeight(dy+filterWidth);
        scanLineWeight *= 0.3333333;
#endif
        return scanLineWeight;
}




vec2 CURVATURE_DISTORTION = vec2(CURVATURE_X, CURVATURE_Y);
// Barrel distortion shrinks the display area a bit, this will allow us to counteract that.
vec2 barrelScale = 1.0 - (0.23 * CURVATURE_DISTORTION);

vec2 Distort(vec2 coord)
{
        float rsq = coord.x * coord.x + coord.y * coord.y;
        coord += coord * (CURVATURE_DISTORTION * rsq);
        coord *= barrelScale;
        return coord;
}


void main()
{
    float N = 320;
    vec2 PUV = floor(UV*N)/N;

    vec2 pr = Distort(PUV)*0.88;
    vec2 pg = Distort(PUV)*0.85;
    vec2 pb = Distort(PUV)*0.82;

    color.x = texture( renderedTexture, pr*0.5 + vec2(0.5,0.5) ).x;
    color.y = texture( renderedTexture, pg*0.5 + vec2(0.5,0.5) ).y;
    color.z = texture( renderedTexture, pb*0.5 + vec2(0.5,0.5) ).z;

    float amp = 0.5;
    float s = 600;
    color.x *=(1 + amp*sin(pr.y*s));
    color.r *=(1 + amp*sin(pg.y*s));
    color.z *=(1 + amp*sin(pb.y*s));

    if (pr.x>1 || pr.x<-1 || pr.y>1 || pr.y<-1) { color.r = 0;}
    if (pg.x>1 || pg.x<-1 || pg.y>1 || pg.y<-1) { color.g = 0;}
    if (pb.x>1 || pb.x<-1 || pb.y>1 || pb.y<-1) { color.b = 0;}

//    color.b *= 0.2;
//    color.r *= 0.2;

//    color.r = 0;

}
