#include "baicIO.h"
class Name_ASH
{
    private:
    char **names;
    int count;
    static const int MAX_NAME_LENGTH=128;
    static const int MAX_NAMES=1000;
    public:
    Name_ASH()
    {
        names=0;
        count=0;
    }
    bool allocate(int number)
    {
        if(number <=0 || number > MAX_NAMES)
        return false;
    names=new char*[number];
    for (int i=0; i < number; i++)
    {
        names[i]=new char[MAX_NAME_LENGTH];
        names[i][0] = '\0';
    }
    count=number;
    return true;
    }
    char* operator[] (int index)
    {
        if(index < 0 || index >=count)
        return 0;
    return names[index];
    }
    int size()
    {
        return count;
    }
    ~Name_ASH ()
    {
        for (int i = 0; i < count; i++)
        delete[] names[i];
    delete[] names;
    }
};
int main ()
{
    io.activateInput ();
    io.outputstring("QUESTION 4\n");
    io.outputstring("enter number of names: ");
    char numberBuffer[32];
    io.inputstring(numberBuffer, 32);
    int number=0;
    int i=0;
    if(numberBuffer[0] == '\0')
    {
        io.outputstring("Invalid number.\n");
        return 0;
    }
    while (numberBuffer[i] != '\0')
    {
        if(numberBuffer[i] < '0' || numberBuffer[i] > '9')
        {
            io.outputstring("invalid number.\n");
            return 0;
        }
        number=number * 10 + (numberBuffer[i] - '0');
        i++;
    }
    if (number <=0 || number > 1000)
    {
        io.outputstring("number of names must be between 1 and 1000.\n");
        return 0;
    }
    Name_ASH list;
    if (!list.allocate(number))
    {
        io.outputstring("could not allocate names.\n");
        return 0;
    }
    for (i=0; i < list.size() ; i++)
    {
        io.outputstring("enter name");
        io.outputint(i + 1);
        io.outputstring(": ");
        io.inputstring(list[i], 128);
    }
    for (i=0; i < list.size(); i++)
    {
        io.outputint(i + 1);
        io.outputstring(". ");
        io.outputstring(list[i]);
        io.terminate();
    }
    return 0;
}