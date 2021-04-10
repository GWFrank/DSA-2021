python p6-gen.py
gcc p6.c -o p6 -O2 -lm -static -std=c11 -pg
./p6 < p6-in > p6-out
# ./p6 < p6-in
diff p6-ans p6-out