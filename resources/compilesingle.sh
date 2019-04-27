filetoh $1 $2 $3
sed 's/static//g' $3 > tmp
mv tmp $3
