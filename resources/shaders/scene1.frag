




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
        vec2 p = UV*vec2(0.5,1);
        vec2 p2 = (p)-vec2(0.5,1);
        vec2 thetaphi = ((p2) - vec2(1.0)) * vec2(3.1415926535897932384626433832795, 1.5707963267948966192313216916398);
        thetaphi.y = -thetaphi.y;
          rd = vec3(cos(thetaphi.y) * cos(thetaphi.x), sin(thetaphi.y), cos(thetaphi.y) * sin(thetaphi.x));

//        p.x = cos(UV.x*2)*2;
  //      p.y = sin(UV.y*2)*2;

//#endif

        // ray direction
        float amp = 0.2*sin(time*0.05)*0;
//        rd = (ca * normalize( vec3(p.xy,2.0) ) + amp*cos(p.x+time*0.1)*vec3(0,1,0));;
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
