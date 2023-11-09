#include "util.h"
#include <stdio.h>

int main()
{ 
    // char sep = '_';
    // string_split("ghbdtn_sfsf_sfdfs", sep);
    int count;
    char **test = string_split("ghbdtn_sfsf_sfdfs", '_', &count);
    for (int i = 0; i < count; i++)
    {
        
        printf("%d = '%s'\n", i, test[i]);
        for (int k = 0; k < 10; k++)
        {
            printf("%d = '%d', ", k, test[i][k]);
        }
        
    }
    
    return 0;
}
