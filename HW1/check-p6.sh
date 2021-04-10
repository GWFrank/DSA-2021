echo 'Generating...'
python p6-gen.py
echo 'Compiling...'
gcc p6.c -o p6 -O2 -lm -static -std=c11 -pg 2> /dev/null
echo 'Executing...'
./p6 < p6-in > p6-out
# ./p6 < p6-in
echo 'Done'
diff p6-ans p6-out