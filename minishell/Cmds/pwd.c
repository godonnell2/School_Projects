#include <unistd.h>  
//print working directory 
void ft_pwd()
{
    char PWD[100000];
   

    if(!getcwd(PWD, sizeof(PWD)))
    {
        printf("error:get cwd in pwd");//maybe dont need to do this??
        //or maybe write is better can write to stderror
        return;
    }

   else
   {
    printf("%s\n", PWD);
   }


}