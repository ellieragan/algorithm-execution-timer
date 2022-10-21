#shell file to get execution times for multiple algorithms
#ellie boyd
#10-3-21

#compile run.c
make run

#loop through all folders in jhu_apl
for dir in */; do
  
  echo $dir
  ./run $dir 25
  done

gcc -g elliptic.c -o elliptic -lcrypto
echo elliptic/
./elliptic
