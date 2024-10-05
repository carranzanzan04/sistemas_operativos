#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
FILE * flujo;
int ndatos,ndatos1[2],ndatos2[2];
long int * array = NULL ;
int **vec=NULL;
/*esta funcion recibe como parametro un  char **
 (en este caso el argv o vector de argumentos matriz de punteros a matrizces 
 de objetos de caracteres) donde recibiremos un archivo con los datos en un
 formato de terminado y  listos para prcesar*/
void cargar_datos( char* v[], int a){ 
  flujo=fopen(v[a],"r");
  if(flujo==NULL){
     perror("el archivo no existe");
  }
  fscanf(flujo,"%d*",&ndatos);
  array=(long int*)malloc(ndatos*sizeof(long int));
  for (int i = 0; i < ndatos; i++){
    fscanf(flujo,"%ld*",&array[i]);
  }
}
void cargar_datos_out( char* v[], int a){ 
  flujo=fopen(v[a],"r");
  if(flujo==NULL){
     perror("el archivo no existe");
  }
  array=(long int*)malloc(2*sizeof(long int));
  for (int s = 0; s < 2; s++){
    fscanf(flujo,"%ld*",&array[s]);
  }
}
void cargar_ndatos1(int n){
 if(n%2==0){
    ndatos1[0]=0;
    ndatos1[1]=n/2;
    ndatos2[0]=(n/2)+1;
    ndatos2[1]=n;
 }
    

}
void showtree(){
   char cmd[20]={""};
   sprintf(cmd," pstree -cAlp %d",getpid());
   system(cmd);
   fclose(flujo);
}
int archivo_vacio(char *v){
  FILE * f;
  f=fopen(v,"r");
  fseek(f,0,SEEK_END);
  if (ftell(f)==0){
    return 0;
  }else
    return 1;
} 

int main(int argc,char* argv[]){
pid_t root = getpid(),out; //se crea una variable root donde se captura el pid del proceso padre y otra para obtener la salida
pid_t h1,h2;// variavles para manejar los dos procesos hijos
FILE* fileout ; //flujo para editar el archivo de salida
long int acomulador1=0,acomulador2=0,acout=0;//variables para la suma de cada proceso y el resultado final  
cargar_datos(argv,1);// leemos el archivo donde estan los datos y lo cargamos en memoria
cargar_ndatos1(ndatos);//definimos los limites de la suma de los hijos
//creando los jerarquia
for(int i=0;i<2;i++){
    if(fork()==0){//si es hijo
      if(i==0){ // si es el primer hijo 
        for(int j=ndatos1[0];j<=ndatos1[1];j++){//recorremos la mitad del vector 
            acomulador1+=array[j];//sumamos cada dato  
            h1=getpid();//capturamos el identificador de procesos del primer hijo  
        } 
      }else if (i==1){// si no si es el segundo hijo
        for(int j=ndatos2[0];j<=ndatos2[1];j++){//recorremos de la mitad +1 hasta el final del vector
            acomulador2+=array[j];//sumamos cada dato
            h2=getpid();//capturamos el identificador de proceso del segundo hijo
        } 
      }
      break;  //contola la jerarqia 1 padre 2 hijos
    }
}
if(root==getpid()){ //aqui va lo que solo debe hacer el padre
           sleep(1);//esperar 1 segundo 
          showtree();//mostrar el arbol de procesos
          for (int j = 0; j < 2; j++) {//esperar que sus dos hijos terminen
             out=wait(NULL);
          }
          free(array);//liberamos memoria una vez que los datos fueron sumados
          array=(long int*)malloc(2*sizeof(long int));//trcrtvamos memoria para leer los datos del archivo out
            cargar_datos_out(argv,2);//cargamos los resultados (de la suma de datos hechas por los hijos) en memoria 
            for(int r=0;r<2;r++){//recorremos el vector con lon nuevos datos
                acout+=array[r];// sumamos cada resultado 
                printf("array[%d] : %ld \n",r,array[r]);// constatamos motrando cada resultado por pantalla
            }
          fileout=fopen(argv[2],"a+t");//abrimos el archivo out en formato de escrituta al final 
          fprintf(fileout,"%ld\n",acout);//agregamos el resultado 
          fclose(fileout);//cerramos el archivo 
          printf("acout: %ld\n",acout);// mostramos el resultado por pantalla
       }else if(h1==getpid()){//aqui va lo que debe hacer el hijo1
          fileout=fopen(argv[2],"a+t");// lo primero es abrir el archivo out para poner su resultado 
           if(fileout==NULL){
               perror("archivo no existe");
           }
          fprintf(fileout,"%ld\n",acomulador1);//poniendo el resultado de la suma en el archivo
          fclose(fileout);//cerrando el flujo de out
          printf("proceso(%d) = suma1{ total :%ld ps ini: %d ps fin:%d }  \n",getpid(),acomulador1,ndatos1[0],ndatos1[1]);
        }else if(h2==getpid()){//aqui va lo que debe hacer el hijo2
        fileout=fopen(argv[2],"a+t");//abrimos al archivo de forma escritura al final
             if(fileout==NULL){
                 perror("archivo no existe");
             }
        fprintf(fileout,"%ld\n",acomulador2);//poniendo el resultado de la suma del hijo en el archivo
        fclose(fileout);// cerrar el flujo 
        printf("proceso(%d) = suma2{total:%ld  ps ini: %d ps fin:%d}\n",getpid(),acomulador2,ndatos2[0],ndatos2[1]);
      }
return 0;
}
