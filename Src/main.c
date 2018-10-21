#include <stdio.h>
#include <stdlib.h>
#include "../Include/rules.h"
#include "../Include/prototypes.h"


//entrer dans le mode d'un flag ?
int getFlag(char *line)
{

}



int main(int ac, char **av)
{
    FILE *fd;
    char *buff;
    size_t size;


    size = 256;

    if ((buff = malloc(sizeof(char) * 256)) == NULL)
        return (-1);

    if ((fd = fopen(av[1], "r")) == NULL)
        return (-1);
    
    while (getline(&buff, &size, fd) != -1)
    {
        getFlag(buff);
    }
}