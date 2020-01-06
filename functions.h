void art(FCGX_Stream *out,MYSQL *mysql,char *id,FCGX_ParamArray envp);
void menu(MYSQL *mysql,FCGX_Stream *out,FCGX_ParamArray envp);
void rawdata(char *data, FCGX_Stream *out);
char *getid(FCGX_Stream *in,FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp);
void echodata(char *data, FCGX_Stream *out);
