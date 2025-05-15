gcc -c myknot.c -o myknot.o -Wall
gcc -c figures.c -o figures.o -Wall
gcc -c tests.c -o tests.o -Wall
gcc tests.o figures.o myknot.o -o knot_exe
