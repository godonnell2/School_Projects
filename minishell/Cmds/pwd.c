#include <unistd.h>  
//print working directory 
void ft_pwd()
{
    char PWD[100000];
   

    if(!getcwd(PWD, sizeof(PWD)))
    {
        perror("pwd:get cwd in pwd");
        return;
    }

   else
   {
    printf("%s\n", PWD);
   }


}