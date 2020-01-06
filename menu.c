#include "intr.h"
#include <assert.h>
#include "functions.h"


void menu(MYSQL *mysql,FCGX_Stream *out,FCGX_ParamArray envp)
{
    char *buf;
    char *method;
    MYSQL_ROW row;
    int i;
        
                char *query1 = "SELECT id,name from art";
                mysql_real_query(mysql,query1,strlen(query1));
                MYSQL_RES *result = mysql_store_result(mysql);
                unsigned int num_fields = mysql_num_fields(result);
                int totalrows = mysql_num_rows(result);
                int numfields = mysql_num_fields(result);
//              MYSQL_FIELD *field;

                while((row = mysql_fetch_row(result)))
                {
//              for(i = 0; i < numfields; i++)
                {
                        char li[128] = "<li><a href=\"http://meat-dev.org?show=";
                        strcat(li,row[0]);
			strcat(li,"\">");
			strcat(li,row[1]);
			strcat(li,"</a>");
                        rawdata(li,out);
                }
            }
//	    art(out,mysql,input,envp);
}
