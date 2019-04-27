../remcomments.sh $1 > tmp
#remove empty lines and stuff
cat tmp | sed '/^$/d' > tmp2
cat tmp2 | sed -e 's/^[ \t]*//' > tmp3
rm tmp4
#cp tmp3 out/$2.stripped
python pystrip.py tmp3 tmp4
#tr -d '\n' < tmp3 > tmp4
mv tmp4 $2
