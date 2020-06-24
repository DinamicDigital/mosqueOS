make clean
rm ./src/startup.o
nasm -felf64 ./src/startup.asm -o ./src/startup.o
make
make run