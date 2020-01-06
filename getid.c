#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intr.h"
#include "functions.h"

char *getid(FCGX_Stream *in,FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp)
{       
    char* id = 0;
    char *input = FCGX_GetParam("QUERY_STRING", envp);
    char *show = "show";
    char *log = "login";
        char *query = strdup(input); 
        char *tokens = query;
        char *p = query;

    while ((p = strsep (&tokens, "&\n"))) {
        char *var = strtok (p, "="),
             *val = NULL;
         if (var && (val = strtok (NULL, "="))){
	    if(strcmp(var,show) == 0) art(out,mysql,val,envp);
	} 
        else
            art(out,mysql,"2",envp);
    }
    free (query);
    return id;
}