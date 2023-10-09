#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char* split_on_C(char *str, char *element){

    char string[strlen(str)];
    int len_input_str = strlen(str);
    //printf("%d", len_input_str);
    
    for (int i = 0; len_input_str > 0; i++)
    {
        string[i] = str[i];
        len_input_str--;
    }

    printf("%s", string);

    return string;
}


int main()
{
    char* str1 = "rwejflenrklwjerligjwrelmglwerkg;wekr'l;wker";

    char str[300];
    char *srt = split_on_C(str1 , "c");
    printf("%s", srt);
    

}
