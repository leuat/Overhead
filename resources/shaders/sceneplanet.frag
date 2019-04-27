uniform float aamp1;

float sumNoise1(in vec3 p) {
    float l = 0;
    float s = 1;
    for (int i=0;i<7;i++) {
        l = l + noise(p*s)/s;
        s*=2;
    }
    return l;
}


float sdPlanet( in vec3 p, in float s )
{
    float l = length(p)*(1+sumNoise1(p)*aamp1);

    return l-s;
}


vec2 map( in vec3 pos )
{
    vec2 res = vec2( 1e10, 0.0 );

         vec3 pp = pos-vec3(0.1,0,0);
//         float c= cos(time/25.0)+2;

             res = opU( res, vec2( sdPlanet(    pp, 6),(1.1+sin(time/74.5))*64f));

    return res;
}



void main(){
        mat3 ca = setCamera( camera, target, 0 );
        vec3 rd = ca * normalize( vec3(UV*vec2(2,1),2.0));

        color=crc(rd,camera,1,1,1, 0, 1, 0.8);

}
