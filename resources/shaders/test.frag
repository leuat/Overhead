#version 330 core

// Ouput data
out vec3 color;
in vec2 UV;

uniform sampler2D renderedTexture;
uniform sampler2D frontTexture;

uniform vec3 textColor;
uniform vec3 screenColor;
uniform float chromatic;



#define CURVATURE_X 0.30
#define CURVATURE_Y 0.65
#define MASK_BRIGHTNESS 0.70
#define SCANLINE_WEIGHT 6.0
#define SCANLINE_GAP_BRIGHTNESS 0.12



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


vec3 getTexture(in vec2 pr, in vec2 pg, in vec2 pb) {
    vec3 color;
    color.x = texture( renderedTexture, pr*0.5 + vec2(0.5,0.5) ).x*screenColor.x;
    color.y = texture( renderedTexture, pg*0.5 + vec2(0.5,0.5) ).y*screenColor.y;
    color.z = texture( renderedTexture, pb*0.5 + vec2(0.5,0.5) ).z*screenColor.z;

    color.x += texture( frontTexture, pr*0.5 + vec2(0.5,0.5) ).x*textColor.x;
    color.y += texture( frontTexture, pg*0.5 + vec2(0.5,0.5) ).y*textColor.y;
    color.z += texture( frontTexture, pb*0.5 + vec2(0.5,0.5) ).z*textColor.z;

    return color;
}

void main()
{
    float N = 320;


    vec2 PUV = floor(UV*N)/N;

    PUV = Distort(PUV);

    vec2 pr = PUV*(0.85+chromatic);
    vec2 pg = PUV*(0.85);
    vec2 pb = PUV*(0.85-chromatic);

    color = getTexture(pr,pg,pb);
/*    color.x = texture( renderedTexture, pr*0.5 + vec2(0.5,0.5) ).x;
    color.y = texture( renderedTexture, pg*0.5 + vec2(0.5,0.5) ).y;
    color.z = texture( renderedTexture, pb*0.5 + vec2(0.5,0.5) ).z;
*/


    float amp = 1;
    float s = 600;
    color.r *=1*(1 + amp*sin(pr.y*s));
    color.g *=1*(1 + amp*sin(pg.y*s));
    color.b *=1*(1 + amp*sin(pb.y*s));

    if (pr.x>1 || pr.x<-1 || pr.y>1 || pr.y<-1) { color.r = 0;}
    if (pg.x>1 || pg.x<-1 || pg.y>1 || pg.y<-1) { color.g = 0;}
    if (pb.x>1 || pb.x<-1 || pb.y>1 || pb.y<-1) { color.b = 0;}

//
//    color = color + texture( frontTexture, UV*0.5 + vec2(0.5,0.5) ).xyz *textColor;
//    color.w = 1;

//    color  = pow(color,8);

//    color.b *= 0.2;
//    color.r *= 0.2;

//    color.r = 0;


//    color = texture( renderedTexture, p*0.5 + vec2(0.5,0.5) ).xyz;
}
