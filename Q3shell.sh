nasm -f elf64 syscall.S -o syscall.o
g++ -c -std=c++17 -nostdlib -ffreestanding -fno-exceptions -fno-rtti basicIO.cpp -o basicIO.o
g++ -c -std=c++17 -nostdlib -ffreestanding -fno-exceptions -fno-rtti Q3.cpp -o Q3.o
g++ -nostdlib -static syscall.o basicIO.o Q3.o -o Q3
./Q3
