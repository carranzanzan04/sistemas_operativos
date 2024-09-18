#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

void showtree(){
   char cmd[20]={""};
   sprintf(cmd," pstree -cAlp %d",getpid());
   system(cmd);
}
int main(void){

    pid_t out; //variable para almacenar retorno del wait
    pid_t root = getpid(); // variable para almacenar el pid del proceso padre 

     for(int i=0;i<2;i++){
        
        if(!fork()){
         for(int t=0;t<3;t++){
            if(!fork()) 
               break;
          }
          printf("padre[%d] e hijo[%d] \n",getppid(),getpid());
          break;
        }
     }
     if(root==getpid()){
           sleep(1);
          showtree();
          for (int j = 0; j < 2; j++) {
             out=wait(NULL);
          }
          printf("p:%d-w:%d\n", getpid(), out); 
       }
       else{
          
          for(int k=0;k<3;k++)
              out=wait(NULL);
       if(out!=-1)
         printf("p:%d-w:%d\n", getpid(), out);
       sleep(2);
       }
        
     
    return EXIT_SUCCESS;
}