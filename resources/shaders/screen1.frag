#version 330 core

// Ouput data
out vec3 col;
in vec2 UV;

uniform sampler2D renderedTexture;
uniform sampler2D frontTexture;

uniform vec3 textColor;
uniform vec3 screenColor;
uniform float chromatic;

uniform float lamp;
uniform float lsca;



/*#define CURVATURE_X 0.30
#define CURVATURE_Y 0.65
#define MASK_BRIGHTNESS 0.70
*/





vec2 CD = vec2(0.3, 0.6);
// Barrel distortion shrinks the display area a bit, this will allow us to counteract that.
vec2 barrelScale = 1.0 - (0.23 * CD);
// Curvature distortion

vec2 Dd(vec2 coord)
{
        float rsq = coord.x * coord.x + coord.y * coord.y;
        coord += coord * (CD * rsq);
        coord *= barrelScale;
        return coord;
}


vec3 gt(in vec2 pr, in vec2 pg, in vec2 pb) {
    vec3 c;
    c.x = texture( renderedTexture, pr*0.5 + vec2(0.5,0.5) ).x*screenColor.x;
    c.y = texture( renderedTexture, pg*0.5 + vec2(0.5,0.5) ).y*screenColor.y;
    c.z = texture( renderedTexture, pb*0.5 + vec2(0.5,0.5) ).z*screenColor.z;

    c.x += texture( frontTexture, pr*0.5 + vec2(0.5,0.5) ).x*textColor.x;
    c.y += texture( frontTexture, pg*0.5 + vec2(0.5,0.5) ).y*textColor.y;
    c.z += texture( frontTexture, pb*0.5 + vec2(0.5,0.5) ).z*textColor.z;

    return c;
}

void main()
{
    float N = 320;


    vec2 PUV = floor(UV*N)/N;

    PUV = Dd(PUV);

    vec2 pr = PUV*(0.85+chromatic);
    vec2 pg = PUV*(0.85);
    vec2 pb = PUV*(0.85-chromatic);

    col = gt(pr,pg,pb);
/*    color.x = texture( renderedTexture, pr*0.5 + vec2(0.5,0.5) ).x;
    color.y = texture( renderedTexture, pg*0.5 + vec2(0.5,0.5) ).y;
    color.z = texture( renderedTexture, pb*0.5 + vec2(0.5,0.5) ).z;
*/


    col.r *=1*(1 + lamp*sin(pr.y*lsca));
    col.g *=1*(1 + lamp*sin(pg.y*lsca));
    col.b *=1*(1 + lamp*sin(pb.y*lsca));

    if (pr.x>1 || pr.x<-1 || pr.y>1 || pr.y<-1) { col.r = 0;}
    if (pg.x>1 || pg.x<-1 || pg.y>1 || pg.y<-1) { col.g = 0;}
    if (pb.x>1 || pb.x<-1 || pb.y>1 || pb.y<-1) { col.b = 0;}

//
//    color = color + texture( frontTexture, UV*0.5 + vec2(0.5,0.5) ).xyz *textColor;
//    color.w = 1;

//    color  = pow(color,8);

//    color.b *= 0.2;
//    color.r *= 0.2;

//    color.r = 0;


//    color = texture( renderedTexture, p*0.5 + vec2(0.5,0.5) ).xyz;
}
