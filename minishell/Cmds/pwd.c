#include <unistd.h>  
//print working directory 
void ft_pwd()
{
    char CWD[100000];
   

    if(!getcwd(CWD, sizeof(CWD)))
    {
        printf("error:get cwd in pwd");//maybe dont need to do this??
        //or maybe write is better can write to stderror
        return;
    }

   else
   {
    printf("%s\n", CWD);
   }


}