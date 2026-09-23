#include <stdio.h>
#include <stdlib.h>
/*
int analex()

{

int etat=0;
while(1)

{switch (etat)
{
case 0: c = fgetc(fp);
if ((c==' ')||(c=='.')||(c=='\n'))
{
etat = 0;
break;
}

else if (isalpha(c))
{etat = 1;
break;
}

else if (c==";")

{
etat = 3;
break;
}

else if (isdigit(c))
{
etat = 4;
break;
}

else if (c==":")
{
etat = 6;
break;
}

else if (c=="<")
{
etat = 9;
break;
}

else if (c==">")
{
etat = 13;
break;
}

else if (c=="=")
{
etat = 16;
break;
}

else if (c=="|")
{
etat = 16;
break;
}

else if (c=="|")
{
etat = 17;
break;
}

else if (c=="(")
{
etat = 20;
break;
}

else if (c==")")
{
etat = ;
break;
}

case 1: c = fgetc(fp);

if (isdigit(c) || isalpha(c))
{ etat = 1;

break; }

else

{ etat = 2;

break; }


case 2: fseek(fp, -1,SEEK_CUR);

return (id);

case 3: return(pv);

case 4: c = fgetc(fp);

if (isdigit(c))

{ etat = 4; break;}
else

{ etat = 4; break; }

case 4: fseek(fp, -1,
SEEK_CUR);return (nb);

*/

#define TABLE_LEN 39
char *table[TABLE_LEN] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "program",
    "var", "begin", "end", "integer", "char", "if", "then", "else", "while", "do", "readln", "read", "writeln", "write"
};

int main()
{   printf("%s \n",table[24]);
    printf("%d \n",strcmp(table[24],"do"));
    printf("Hello world!\n");
    return 0;
}

