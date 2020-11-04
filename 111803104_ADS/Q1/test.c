#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dictionary.c"


const char* getcolumn(char* line, int num){
    const char* token;
    for (token = strtok(line, ":"); token && *token; token = strtok(NULL, ";\n")){
        if (!--num)
            return token;
    }
    return NULL;
}

int main(){
    Dict d;

    d = create();
   
    FILE* stream = fopen("input.txt", "r");
    char line[1024];
    while (fgets(line, 1024, stream)){
        char* tmp = strdup(line);
        insert(d, getcolumn(tmp,1), getcolumn(tmp,2));
        free(tmp);
    }
    fclose(stream);
    printf("The meaning of the word dictionary is : ");
    puts(search(d, "dictionary"));
    printf("\nThe dictionary sorted in ascending order is - \n\n");
    sortasc(d);
    update(d, "dictionary", "new meaning");
    printf("\nThe updated meaning of dictionary is : ");
    puts(search(d, "dictionary"));
    Delete(d, "dictionary");
    printf("\nDeleted word 'dictionary' along with its meaning\n\n");
    printf("The dictionary sorted in descending order is - \n\n");
    sortdesc(d);   
    destroy(d);

    return 0;
}

    
