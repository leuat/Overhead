cd /home/leuat/code/Overhead/resources
cd fonts

../compilesingle.sh allerta allerta_small.ttf allerta.h
cd ..
cd shaders
../compilesingleshader.sh glyph_vert glyph.vert glyph_vert.h
../compilesingleshader.sh glyph_frag glyph.frag glyph_frag.h
../compilesingleshader.sh raymarcherinc raymarcherinc.frag raymarcherinc_frag.h


../compilesingleshader.sh scene1_vert scene1.vert scene1_vert.h
../compilesingleshader.sh scene1_frag scene1.frag scene1_frag.h

../compilesingleshader.sh scenePlanet_vert sceneplanet.vert scenePlanet_vert.h
../compilesingleshader.sh scenePlanet_frag sceneplanet.frag scenePlanet_frag.h

../compilesingleshader.sh screen1_vert screen1.vert screen1_vert.h
../compilesingleshader.sh screen1_frag screen1.frag screen1_frag.h
echo "Files converted!"
