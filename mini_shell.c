#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>
#include <sys/wait.h>
char** do_arr(char* str);
int main()
{
    char** argv;
    int c = 0;
    int res;
    char hostname[128];
    char * login;
    char str[510]; // Input array.
    pid_t d;
    strcpy(str ," ");//inilazation the string
    if(gethostname(hostname, sizeof hostname)==-1)//to use gethostname function
        strcpy(hostname ,"host");
    login = getlogin();
    if(login == NULL)
        login = "user";

    while(1)//the loop to the mini shell
    {

        printf("%s@%s$ ",login,hostname);
        if(gets(str)==NULL)//enter the task to do
            exit(1);
        if(strcmp(str,"done")==0)//if he want to done
            exit(0);

        argv=do_arr(str);//sent to the function that do the array
        d=fork();
        if(d<0) {//if he can`t open
            printf("error\n");
            exit(1);
        }
        if(d==0){//the son
            res=execvp(argv[0],argv);
            if(res==-1) {//if the enter is not exist
                printf("%s:command not found\n", argv[0]);
                exit(1);
            }

        }
        if(d>0) {//the father
            wait(NULL);
        }


    }
    //free the mallocs
    while (argv[c] != NULL)
    {
        free(argv[c]);
        c++;

    }
    free (argv);
    return 0;
}
char** do_arr(char* str)//function that do the array
{
    int j = 0;
    int len = strlen(str);
    int i = 0, cnt = 0;
    const char s[2] = " ";
    char *token;
    while (i<len) {//loop that pass on the string and count the words
        if (str[i]!=' ')
            cnt++;
        while (str[i] != ' '&&i<len)
            i++;
        while (str[i] == ' '&&i<len)
            i++;
    }

    char** array = (char**)malloc((cnt + 1) * sizeof(char*));//do matrix
    if (array == NULL) {
        printf("error");
        return NULL ;
    }
    token = strtok(str, s);
    //enter the words to the array
    while (token != NULL) {
        int len = strlen(token);
        array[j] = (char*)malloc((len+1) * sizeof(char));
        strcpy(array[j], token);
        j++;
        token = strtok(NULL, s);


    }
    //put null in the last local
    array[j] = NULL;

    return array;

}