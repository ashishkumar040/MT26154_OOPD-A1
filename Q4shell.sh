nasm -f elf64 syscall.S -o syscall.o
g++ -c -std=c++17 -nostdlib -ffreestanding -fno-exceptions -fno-rtti basicIO.cpp -o basicIO.o
g++ -c -std=c++17 -nostdlib -ffreestanding -fno-exceptions -fno-rtti Q4.cpp -o Q4.o
g++ -nostdlib -static syscall.o basicIO.o Q4.o -o Q4
./Q4
