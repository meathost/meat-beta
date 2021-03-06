#include "intr.h"
#include "functions.h"
#include "mypasswd.h"

MYSQL *mysql_con()
{
    MYSQL *mysql;

	mysql = mysql_init(NULL);
	mysql_real_connect(mysql, MYHOST, MYUSER, MYPASS, MYDB, 0,NULL,0);
	mysql_set_character_set(mysql, "utf8");
    
    return mysql;
}

void echodata(char *data, FCGX_Stream *out)
{
	        FCGX_PutS("Content-type: text/html\r\n", out); 
	        FCGX_PutS("\r\n", out); 
    		FCGX_PutS(data,out);
}
void rawdata(char *data, FCGX_Stream *out)
{
    		FCGX_PutS(data,out);
}

int tpl(char *filename, FCGX_Stream *out) {
    FILE    *infile;
    char    *buffer;
    long    numbytes;
 
infile = fopen(filename, "r");
 
    if(infile == NULL)
	return 1;
 
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
 
    fseek(infile, 0L, SEEK_SET);	
 
    buffer = (char*)calloc(numbytes, sizeof(char));	
 
    if(buffer == NULL)
	return 1;
 
    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);

    rawdata(buffer,out);
 
    free(buffer);
}


void art(FCGX_Stream *out,MYSQL *mysql,char *id,FCGX_ParamArray envp)
{
    MYSQL_ROW row;	

	        FCGX_PutS("Content-type: text/html\r\n", out); 
	        FCGX_PutS("\r\n", out);
		tpl("tpl/header1.tpl",out); 
		tpl("tpl/menu.tpl",out);
                menu(mysql,out,envp);

		char query1[150] = "SELECT name, DATE_FORMAT(reg_date, '%H:%i:%s - %W %M %Y'), article FROM art WHERE id=";
		char *query2 = strcat(query1,id);
		mysql_real_query(mysql,query2,strlen(query2));
		MYSQL_RES *result = mysql_store_result(mysql);
		int totalrows = mysql_num_rows(result);
                if (totalrows == 1)
		{ 
		    row = mysql_fetch_row(result);
		    mysql_free_result(result);


		    tpl("tpl/header2.tpl",out);
	
		    rawdata(row[0],out);
		
		    tpl("tpl/header3.tpl",out);
		    rawdata(row[1],out);

		    tpl("tpl/header4.tpl",out);
		    rawdata(row[2],out);
		
		    tpl("tpl/footer.tpl",out);
		 } else 
		{
		    tpl("tpl/header2.tpl",out);
		    rawdata("Not found",out);
		}
    }

void doit() 
{ 
    FCGX_Stream *in, *out, *err;
    FCGX_ParamArray envp;
    MYSQL_ROW row;
    MYSQL *mysql = mysql_con();
    while (FCGX_Accept(&in, &out, &err, &envp) >= 0) 
    {
	getid(in,out,mysql,envp);
	
    }
    mysql_close(mysql);
} 

int main(void) 
{
    doit();    
    return 0; 
}
