rm $3
./LStrip.sh $2 stripped
#mono shader_minifier.exe --preserve-externals --format "none" $2 -o tmp4
cp stripped out/$3.stripped
filetoh $1 stripped $3
sed 's/static//g' $3 > tmp
mv tmp out/$3
