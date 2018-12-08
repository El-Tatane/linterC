 #include <stdlib.h>
 #include <string.h>
 #include "prototypes.h"

char  *getLastPart(char *str, char c)
{
    char *ret;
    int i;
    int n;

    n = 0;
    if ((strchr(str, c)) == NULL)
        return (NULL);
    i = strlen(str);
    while (str[i] != c)
        i--;
    if ((ret = malloc(sizeof(char) * (strlen(str)))) == NULL)
        return (NULL);
    
    while (str[i] != '\0')
    {
        ret[n] = str[i];
        n++;
        i++;
    }
    ret[n] = '\0';
    return (ret);
}

char  *getFirstPart(char *str, char c, int *nbWord)
{
    char *ret;
    int i = 0;
    
    while (str[i] != c)
    {
        if (i == 0 && isFunctionChar(str[i]) == 1)
            (*nbWord)++;
        else if (isFunctionChar(str[i]) == 1 && (str[i - 1] == ' ' || str[i - 1] == '\t'))  
            (*nbWord)++;
        i++;
    }
    if ((ret = malloc(sizeof(char) * i + 1)) == NULL)
        return (NULL);
    strncpy(ret, str, i);
    ret[i] = '\0';
    return (ret);
}

char *removeSpaces(char *part)
{
    int i = 0;
    int n = 0;
    char *ret;

    
    if ((ret = malloc(sizeof(char) * strlen(part))) == NULL)
        return (NULL);
    while (part[i] != '\0')
    {   
        if (part[i] != ' ' && part[i] != '\t')
            ret[n++] = part[i];
        i++;
    }

    ret[n] = '\0';
    return (ret);
}

int isFunctionChar(char c)
{  
    if (c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_')
    {
        return (1);
    }
    return (0);
}

int containsType(char *line)
{
    char types[][10] = {
        "int",
        "char",
        "double",
        "float",
        "short",
        "long",
        "bool",
        "void",
        "unsigned",
        "struct",
    };

    for (int i = 0; i < 10; i++)
    {
        if ((strstr(line, types[i])) != NULL)
            return (1);
    }
    return (0);
}

char  *getLastWord(char *str, int pos) // recupère dernier mot à partir de pos (dernier caractere)
{
    int tmp;
    char *ret;
    int i = 0;

    tmp = pos;
    while (tmp > 0)
    {
        if (str[tmp] == ' ' || str[tmp] == '\t')
            break;
        tmp--;
    }
    if ((ret = malloc(sizeof(char) * (pos - tmp) + 1)) == NULL)
        return (NULL);

    tmp++;
    while (tmp < pos)
    {

        ret[i] = str[tmp];
        i++;
        tmp++;
    }
    ret[i] = '\0';
   return (ret);
}