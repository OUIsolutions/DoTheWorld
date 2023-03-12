
gcc -c -o doTheWorldShared.o -fPIC code/doTheWorldSeparated.c

gcc -shared -o libdoTheWorldShared.so doTheWorldShared.o
rm doTheWorldShared.o