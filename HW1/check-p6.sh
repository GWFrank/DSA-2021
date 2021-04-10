python p6-gen.py
gcc p6.c -o p6 -O2 -lm -Wall -static -std=c11
./p6 < p6-in > p6-out
diff p6-ans p6-out