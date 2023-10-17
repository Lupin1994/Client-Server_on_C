#include "util.h"
#include <stdio.h>

int main()
{ 
    char sep = ' ';
    string_split("ghbdtn sfsf sfdfs \0", sep);
    //char **test = string_split("ghbdtn sfsf sfdfs", ' ');
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("%s",test[i]);

    //     for (int j = 0; j < 10; j++)
    //     {
    //         printf("%s",test[j]);
    //     }
    // }
    
    return 0;
}
