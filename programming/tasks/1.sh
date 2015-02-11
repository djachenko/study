gcc $1.c -o $1.out -lm
echo "$1 running..."
./$1.out $2 $3 $4 $5 $6 $7 $8 $9
rm $1.out
