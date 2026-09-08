// Ashish kumar_MT26154
#include "basicIO.h"
void output(const char* NAME, int AGE){
    io.outputstring("Name: ");
    io.outputstring(NAME);
    io.outputstring("\n");
    io.outputstring("AGE: ");
    io.outputint(AGE);
    io.outputstring("\n");
}
int main(){
    char verify[2];
    char NAME[100];
    int AGE;
    io.outputstring("Enter your NAME: ");
    io.inputstring(NAME,100);
    io.outputstring("Enter your AGE: ");
    AGE = io.inputint();
    io.outputstring("\ncheck if they are correct:\n");
    output(NAME,AGE);
    io.outputstring("\n Y/N to save or clr ");
    io.inputstring(verify,3);
    if(verify[0]=='Y' || verify[0]=='y'){
        io.outputstring("saved\n");
    }
    else if(verify[0]=='N'||verify[0]=='n'){
        io.outputstring("clr");
        NAME[0]='\0';
        AGE=0;
    }
    else{
        io.outputstring("invalid option\n");
    }
    output(NAME,AGE);
    return 0;
}
