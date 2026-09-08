 
# Ashish kumar_MT26154
nasm -f elf64 syscall.S -o syscall.o
g++ -c -std=c++17 -nostdlib -ffreestanding -fno-exceptions -fno-rtti basicIO.cpp -o basicIO.o
g++ -c -std=c++17 -nostdlib -ffreestanding -fno-exceptions -fno-rtti MT26154_Q4_Q5.cpp -o MT26154_Q4_Q5.o
g++ -nostdlib -static syscall.o basicIO.o MT26154_Q4_Q5.o -o MT26154_Q4_Q5
./MT26154_Q4_Q5