// Ashish kumar_MT26154
#include "basicIO.h"
class Name_ASH
{
    private:
    int count;
    static const int MAX_NAME_LENGTH=128;
    static const int MAX_NAMES=1000;
    char names[MAX_NAMES][MAX_NAME_LENGTH];
    public:
    Name_ASH()
    {
        
        count=0;
    }
    bool allocate(int number)
    {
        if(number <=0 || number > MAX_NAMES)
        return false;
    count = number;
    for (int i=0; i < count; i++)
    {
        
        names[i][0] = '\0';
    }
    
    return true;
    }
    void addName(int index)
    {
        io.outputstring("enter name");
        io.outputint(index+1);
        io.outputstring(": ");
        io.inputstring(names[index], MAX_NAME_LENGTH);
    }
    void print(int index) const
    {
        io.outputint(index+1);
        io.outputstring(". ");
        io.outputstring(names[index]);
        io.terminate();

        
    }
    void printAll() const
    {
        for (int i=0; i < count; i++)
        print(i);
    }
    char* operator[] (int index)
    {
        if (index < 0 || index >= count)
        return 0;
    return names[index];
    }
    int size() const { return count; }
    Name_ASH& operator+ (int extra)
    {
        if (extra <=0)
        return *this;
    int newCount=count+extra;
    if (newCount > MAX_NAMES)
    {
        io.outputstring("cannot add that many - would exceed maximum capicity of");
        io.outputint(MAX_NAMES);
        io.outputstring(". adding as many as possible instead.\n");
        newCount=MAX_NAMES;
    }
    for (int i=count; i<newCount; i++)
    {
        names[i][0]='\0';
        addName(i);
    }
    count=newCount;
    return *this;
    }
    Name_ASH& operator-(int reduceBy)
    {
        if (reduceBy <=0)
        return *this;
    count -= reduceBy;
    if (count < 0)
    count=0;
    return *this;
    }
};

bool readNumber(const char* prompt, int&outNumber, int minVal, int maxVal)
{
    io.outputstring(prompt);
    char buffer[32];
    io.inputstring(buffer,32);
    if (buffer[0] == '\0')
    {
        io.outputstring("invalid number.\n");
        return  false;
    }
    int number=0;
    int i=0;
    while (buffer[i] != '\0')
    {
        if (buffer[i] < '0' || buffer[i] > '9')
        {
            io.outputstring("invalid number.\n");
            return false;
        }
        number=number*10+(buffer[i] - '0');
        i++;
    }
    if (number < minVal || number > maxVal)
    {
        io.outputstring(" number out of allowed range.\n");
        return false;
    }
    outNumber=number;
    return true;
}

int main (){
    io.activateInput ();
    io.outputstring("QUESTION 5\n");
    int number=0;
    if(!readNumber("enter number of names:" , number,1,1000))
    return 0;
Name_ASH list;
if (!list.allocate(number))
{
    io.outputstring("could not allocate names.\n");
    return 0;
}
for (int i=0; i< list.size(); i++)
list.addName(i);
io.outputstring("\nyou enterd the following names:\n");
list.printAll();
io.outputstring("\n do you want to change the number of names? (y/n): ");
    char changeBuffer[8];
    io.inputstring(changeBuffer, 8);
    if (changeBuffer[0] == 'y' || changeBuffer[0] =='Y')
    {
        io.outputstring("do you want to (a)dd or (r)emove names? ");
        char actionBuffer[8];
        io.inputstring(actionBuffer, 8);
        if (actionBuffer[0] == 'a' || actionBuffer[0] == 'A')
        {
            int extra = 0;
            if(readNumber("how many names to add? ", extra,1,1000))
            list + extra;
        }
        else if (actionBuffer[0] == 'r' || actionBuffer[0] == 'R')
        {
            int reduceBy = 0;
            if (readNumber("how many names to remove? ", reduceBy,1,1000))
            list - reduceBy;
        }
        else
        {
            io.outputstring("invalis choice, no changes made.\n");
        }
        io.outputstring("\nupdated list of names:\n");
        list.printAll();

        
    }
    io.outputstring("\nIs this correct? (y/n): ");
    char confirmBuffer[8];
    io.inputstring(confirmBuffer,8);
    char response = confirmBuffer[0];
    if (response == 'y' || response == 'Y')
    io.outputstring("details confirmed.\n");
else if (response == 'n' || response == 'N')
io.outputstring("details not confirmed.\n");
else
io.outputstring("invalid response.details not confirmed.\n");
return 0;
}