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


float sdSphere( in vec3 p, in float s )
{
//    p.x = p.x;
  //  p.z = p.z+cos(time/10);
    return length(p)-s;
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


vec2 map( in vec3 pos )
{
    vec2 res = vec2( 1e10, 0.0 );

//    if( pos.x>-10.5 && pos.x<10.5 )
    {
        int j=0;
        for (int i=0;i<28;i++) {
        // res = opU( res, vec2( sdSphere(    pos-vec3( spherePos[5*i+0],spherePos[5*i+1], spherePos[5*i+2]), spherePos[5*i+4] ), spherePos[5*i+3]*200.0 + time ) );
         res = opU( res, vec2( sdSphere(    pos-vec3( spherePos[5*i+0],spherePos[5*i+1], spherePos[5*i+2]), 0.5),  spherePos[5*i+3]  ));
         j=j+5;
        }
   }


        //res = min( res, sdBox(pos-vec3(0.5,0.4,-0.5), vec3(2.0,0.41,2.0) ) );
    return res;
}

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
       float tp1 = (0.0-ro.y)/rd.y;
       if( tp1>0.0 )
       {
           tmax = min( tmax, tp1 );
           res = vec2( tp1, 1.0 );
       }

      ///else return res;

       // raymarch primitives
//       vec2 tb = iBox( ro-vec3(0.5,0.4,-0.5), rd, vec3(2.0,0.41,2.0) );
//       vec2 tb = iBox( ro-0*vec3(0.5,0.4,-0.5), rd, 8*vec3(2.0,0.41,2.0) );
  //     if( tb.x<tb.y && tb.y>0.0 && tb.x<tmax)
       {
    //       tmin = max(tb.x,tmin);
      //     tmax = min(tb.y,tmax);
            tmin = 0.005;
            tmax = 30;
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



void main(){
        // Output color = color of the texture at the specified UV
        //color = texture( myTextureSampler, UV ).rgb;




        vec3 rd;// = coord2ray();
        vec3 ro = camera;
        float s= 3.14/2;
        float s2 = s*2;

        //ro = vec3(sin(UV.x*s2)*cos(UV.y*s),sin(UV.x*s2)*sin(UV.y*s), cos(UV.y*s*s2));
        mat3 ca = setCamera( ro, target, 0 );

//        vec2 o = vec2(float(m),float(n)) / float(AA) - 0.5;
//        vec2 p = (-iResolution.xy + 2.0*(fragCoord+o))/iResolution.y;
//#else
 //       vec2 p = iResolution2.0*(UV)*1;
        vec2 p = 2*UV;
//        p.x = cos(UV.x*2)*2;
  //      p.y = sin(UV.y*2)*2;

//#endif

        // ray direction
        float amp = 0.2*sin(time*0.05)*0;
        rd = (ca * normalize( vec3(p.xy,2.0) ) + amp*cos(p.x+time*0.1)*vec3(0,1,0));;
//        rd = (ca * normalize( vec3(p.xy,2.0) ));




        vec3 col = vec3(0,0,0);//(vec3(0.9, 0.9, 1.0) +rd.y*0.8);

        vec2 res = RayMarch(rd, ro);

//        vec2 res = castRay(ro,rd);
        float t = res.x;
        float m = res.y;

        if( m>-0.5 )
        {
            vec3 pos = ro + t*rd;
            vec3 nor = (m<1.5) ? vec3(0.0,1.0,0.0) : calcNormal( pos );
            vec3 ref = reflect( rd, nor );
            // material
            col = 0.45 + 0.35*sin( vec3(0.05,0.08,0.10)*(m-1.0) );

            if( m<1.5 )
            {
                float f = checkersGradBox( 2.0*pos.xz );
                col = 0.3 + f*vec3(0.1);
            }

            // lighting
            float occ = calcAO( pos, nor );
            vec3  lig = normalize( vec3(-0.4, 0.7, -0.6) );
            vec3  hal = normalize( lig-rd );
            float amb = clamp( 0.5+0.5*nor.y, 0.0, 1.0 );
            float dif = clamp( dot( nor, lig ), 0.0, 1.0 );
            float bac = clamp( dot( nor, normalize(vec3(-lig.x,0.0,-lig.z))), 0.0, 1.0 )*clamp( 1.0-pos.y,0.0,1.0);
            float dom = smoothstep( -0.2, 0.2, ref.y );
            float fre = pow( clamp(1.0+dot(nor,rd),0.0,1.0), 2.0 );

    //        dif *= calcSoftshadow( pos, lig, 0.02, 2.5 );
      //      dom *= calcSoftshadow( pos, ref, 0.02, 2.5 );

                    float spe = pow( clamp( dot( nor, hal ), 0.0, 1.0 ),60.0)*
                        dif *
                        (0.04 + 0.96*pow( clamp(1.0+dot(hal,rd),0.0,1.0), 5.0 ));

                    vec3 lin = vec3(0.0);
            lin += 1.40*dif*vec3(1.00,0.80,0.55)*0;
            lin += 0.20*amb*vec3(0.40,0.60,1.00)*occ;
            lin += 0.40*dom*vec3(0.40,0.60,1.00)*occ*1;
            lin += 0.50*bac*vec3(0.25,0.25,0.25)*occ*10;
            lin += 0.25*fre*vec3(1.00,1.00,1.00)*occ*10;

                    col = col*lin;
                    col += 9.00*spe*vec3(1.00,0.90,0.70);



//            col = mix( col, vec3(0.8,0.9,1.0), 1.0-exp( -0.0002*t*t*t ) );
        }

//        color = pow( clamp(col,0.0,1.0),vec3(0.45));
        color = clamp(col,0.0,1.0);

}
