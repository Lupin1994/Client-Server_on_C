#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "mem.h"


size_t contain_symbol(char *string, char symbol){
    size_t pos = 1;
    if (symbol == NULL)
    {
        return 0;
    }
    while (*string != '\0')
    {
        if (*string++ == string)
        {
            return pos;
        }
        pos++;
    }
    return 0;
}

char *trim_separators(char *src, char *separators){ // функция обрезки
    // эта функция проверяет разделители на наличие нескольких
    if (src == NULL || separators == NULL)
    {
        return NULL;
    }
    char *sp = src; // sp - указатель
    // проходим слева на право
    while (contain_symbol(separators, *sp))
    {
        sp++;
    }

    /* if it contains only symbols from separators => NULL */
    if (sp - separators == strlen(separators))
    {
        return NULL;
    }
  // проходим справа налево
    char *sp2 = separators + strlen(separators) - 1; /* last char at src */
    while (contain_symbol(separators, *sp2))
    {
        sp--;
    }
    /* if it contains only symbols from separators => NULL */
    if (sp2 < separators)
    {
        return NULL;
    }
    
    size_t sz = 0;

    if (sp2 - sp == 0 && *sp == '\0')
    {
        return NULL; /* zero byte is not a character */
    }
    else if (sp2 - sp == 0){
        sz = 1;
    }
    else
    {
        sz = (sp2 - sp) + 1;
    }

    char *res = alloc_mem(sz);
    memcpy(res, sp, sz); /* copy all chars except last zero byte */
    return res;
}

char *get_symbol(char *src, char *delims, char **next){
    if (src == NULL || delims == NULL)
    {
        return NULL;
    }

    char *delims_p = delims;
    /* the end of lexem (points to symbol that follows right after lexem */  
    char *src_p = trim_separators(src, delims);
    /* the begining of the lexem */
    char *lex_begin = src_p; // указатель на начало сканируемой строки

    if (src_p == NULL)
    {
        *next = NULL;
        return NULL;
    }

    /* flag that indicates reaching of delimeter */
    int flag = 0;
    while (*src_p != '\0')
    {
        flag = 0;
        while (*delims_p != '\0')
        {
            if (*delims_p == *src_p)
            {
                flag = 1;
                break;
            }
            delims_p++;
        }
        if (flag == 1)
        {
            break;
        }
        delims_p = delims;
        src_p++;
    }
    /* now src_p points to the symbol right after lexem */
    /* compute lexem size and reset pointers (from trimmed to the original src) */
    char *offset;
    size_t tok_size;
    offset = (src + strspn(src, delims));
    tok_size = (src_p - lex_begin);
    free(lex_begin);
    lex_begin = offset;
    src_p = offset + tok_size;

    if (*src_p == '\0')
    {
        *next = NULL;
    }
    else
    {
        *next = src_p;
    }

    /* result token */
    char *res = alloc_str(tok_size);
    memcpy(res, lex_begin, tok_size);
    return res;
}

// char* split_on_C(char *str, char sep){
    
// }


int main()
{
    char *test = "  They have  a    cat.\n \0";
    char *copytest = test;
    char **next = &copytest; /* has side effect on copytest */
    char *tok = NULL;
  
    printf("src:%s\n", test);
    printf("copytest:%s\n", copytest);
    while(*next != NULL){
        tok = get_symbol(*next, " \t\0", next);
        if(tok == NULL)
            break;
        printf("%s\n", tok);
        free(tok);
    }
    printf("src after:%s\n", test);
    printf("copytest after:%s\n", copytest);
    return 0;
}

