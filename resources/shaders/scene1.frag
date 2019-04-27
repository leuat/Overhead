
vec2 map( in vec3 pos )
{
    vec2 res = vec2( 1e10, 0.0 );

//    if( pos.x>-10.5 && pos.x<10.5 )
    {
        int j=0;
        for (int i=0;i<1;i++) {
        // res = opU( res, vec2( sdSphere(    pos-vec3( spherePos[5*i+0],spherePos[5*i+1], spherePos[5*i+2]), spherePos[5*i+4] ), spherePos[5*i+3]*200.0 + time ) );
//         res = opU( res, vec2( sdSphere(    pos-vec3( spherePos[5*i+0],spherePos[5*i+1], spherePos[5*i+2]), 0.5),  spherePos[5*i+3]  ));
         vec3 p = pos-vec3(
                 spherePos[5*i+0]*0.01,
                 spherePos[5*i+1]*0.0+0.2,
                 spherePos[5*i+2])*0.01;
         float c= cos(time/25.0)+2;
//         c = 1.1;
         p = modfunc(p,vec3(c,4,c));
//         p = modfunc(p,vec3(2.5,5,2.5));


         if (j>=0)
            res = opU( res, vec2( sdBox(    p, 0.5*vec3(1,1,1)),spherePos[5*i+3]));
        else
             res = opU( res, vec2( sdTorus(    p, vec2(1,0.5)),spherePos[5*i+3]));

         j=j+5;
        }
   }

    return res;
}


void main(){
        float th = cos(time/100.0)*2+1;
        vec3 rd = fvcam(UV,th);

        vec3 ro = camera +rd;
        color = crc(rd, ro, 0,0,1,10,10,0.45);

}
