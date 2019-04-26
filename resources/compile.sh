cd /home/leuat/code/Overhead/resources
cd fonts

filetoh allerta allerta_small.ttf allerta.h
cd ..
cd shaders
filetoh glyph_vert glyph.vert glyph_vert.h
filetoh glyph_frag glyph.frag glyph_frag.h
filetoh raymarcherinc raymarcherinc.frag raymarcherinc_frag.h


filetoh scene1_vert scene1.vert scene1_vert.h
filetoh scene1_frag scene1.frag scene1_frag.h

filetoh screen1_vert screen1.vert screen1_vert.h
filetoh screen1_frag screen1.frag screen1_frag.h
echo "Files converted!"
