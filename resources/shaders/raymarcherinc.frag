#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 vpos;

// Ouput data
out vec3 color;

uniform float time;
uniform mat4x4 invVP;
uniform mat4x4 viewMat, projMat;
// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;


uniform vec3 camera, target;
float fov;

uniform float spherePos[32*10];

vec3 coord2ray() {
    float xx = UV.x/(2*0.5);
    float yy = UV.y/(2*0.5);
//    double xx = x / (width  * 0.5) - 1.0;
  //  double yy = y / (height * 0.5) - 1.0;

    vec4 screenPos = vec4(xx, -yy, 1,1);
    vec4 worldPos = invVP *screenPos;
    return normalize(worldPos.xyz);
}


float sdPlane( vec3 p )
{
  return p.y;
}

float sdBox( vec3 p, vec3 b )
{
    vec3 d = abs(p) - b;
    return min(max(d.x,max(d.y,d.z)),0.0) + length(max(d,0.0));
}

/*float opRep( in vec3 p, in vec3 c, in sdf3d primitive )
{
    vec3 q = mod(p,c)-0.5*c;
    return primitve( q );
}
*/
float sdSphere( in vec3 p, in float s )
{
    return length(p)-s;
}

vec3 modfunc(in vec3 p, in vec3 c) {
    return mod(p,c)-0.5*c;
}

float sdTorus( vec3 p, vec2 t )
{
//    p.x = p.x + cos(time/100)+p.y;
    return length( vec2(length(p.xz)-t.x,p.y) )-t.y;
}

vec2 iBox( in vec3 ro, in vec3 rd, in vec3 rad )
{
    vec3 m = 1.0/rd;
    vec3 n = m*ro;
    vec3 k = abs(m)*rad;
    vec3 t1 = -n - k;
    vec3 t2 = -n + k;
        return vec2( max( max( t1.x, t1.y ), t1.z ),
                     min( min( t2.x, t2.y ), t2.z ) );
}
vec2 opU( vec2 d1, vec2 d2 )
{
        return (d1.x<d2.x) ? d1 : d2;
}

vec2 map( in vec3 pos );


vec3 calcNormal( in vec3 pos )
{
    vec2 e = vec2(1.0,-1.0)*0.5773*0.0005;
    return normalize( e.xyy*map( pos + e.xyy ).x +
                                          e.yyx*map( pos + e.yyx ).x +
                                          e.yxy*map( pos + e.yxy ).x +
                                          e.xxx*map( pos + e.xxx ).x );
}


float calcAO( in vec3 pos, in vec3 nor )
{
        float occ = 0.0;
    float sca = 1.0;
    for( int i=0; i<5; i++ )
    {
        float hr = 0.01 + 0.12*float(i)/4.0;
        vec3 aopos =  nor * hr + pos;
        float dd = map( aopos ).x;
        occ += -(dd-hr)*sca;
        sca *= 0.95;
    }
    return clamp( 1.0 - 3.0*occ, 0.0, 1.0 ) * (0.5+0.5*nor.y);
}

vec2 RayMarch(vec3 rd, in vec3 ro) {

    float tmin = 1.0;
       float tmax = 20.0;

       vec2 res = vec2(-1.0,-1.0);

       // raytrace floor plane
 /*      float tp1 = (0.0-ro.y)/rd.y;
       if( tp1>0.0 )
       {
           tmax = min( tmax, tp1 );
           res = vec2( tp1, 1.0 );
       }
*/
      ///else return res;

       // raymarch primitives
//       vec2 tb = iBox( ro-vec3(0.5,0.4,-0.5), rd, vec3(2.0,0.41,2.0) );
//       vec2 tb = iBox( ro-0*vec3(0.5,0.4,-0.5), rd, 8*vec3(2.0,0.41,2.0) );
  //     if( tb.x<tb.y && tb.y>0.0 && tb.x<tmax)
       {
    //       tmin = max(tb.x,tmin);
      //     tmax = min(tb.y,tmax);
            tmin = 0.005;
            tmax = 300;
           float t = tmin;
           for( int i=0; i<70 && t<tmax; i++ )
           {
               vec2 h = map( ro+rd*t );
               if( abs(h.x)<(0.0001*t) )
               {
                   res = vec2(t,h.y);
                    break;
               }
               t += h.x;
           }
       }

       return res;

}

mat3 setCamera( in vec3 ro, in vec3 ta, float cr )
{
        vec3 cw = normalize(ta-ro);
        vec3 cp = vec3(sin(cr), cos(cr),0.0);
        vec3 cu = normalize( cross(cw,cp) );
        vec3 cv =          ( cross(cu,cw) );
    return mat3( cu, cv, cw );
}

float checkersGradBox( in vec2 p )
{
    // filter kernel
    vec2 w = fwidth(p) + 0.001;
    // analytical integral (box filter)
    vec2 i = 2.0*(abs(fract((p-0.5*w)*0.5)-0.5)-abs(fract((p+0.5*w)*0.5)-0.5))/w;
    // xor pattern
    return 0.5 - 0.5*i.x*i.y;
}



