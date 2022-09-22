 #include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
 #include <sys/time.h>
 struct timespec start, end,toc,tic;
 double Elapsed;

 int main (int argc, char * argv[]){
    /*midiendo el tiempo de lectura*/
    clock_gettime(CLOCK_REALTIME,&start);
    FILE * flujo=fopen(argv[1],"r");
    if (flujo==NULL){
        perror("el archivo no existe ");
    }
    int nelementos;
    fscanf(flujo,"%d",&nelementos);
    int * array =NULL;
    array=(int*)malloc(nelementos*sizeof(int));
    printf("%d \n",nelementos);
    if (array!=NULL){
        for (int i = 0; i < nelementos; i++){
        fscanf(flujo,"%d*",&array[i]);
        }
    }
    /*fin del codigo a leer */
    clock_gettime(CLOCK_REALTIME,&end);
    Elapsed = (double)(toc.tv_sec-tic.tv_sec)+((toc.tv_nsec-tic.tv_nsec)/(double)1E9);
    printf("TIEMPO DE LECTURA :\n");
    printf("%.8lf\n",Elapsed);

    long int suma;
    for(int j=0; j< nelementos; j++){
            suma+=array[j];
    }
    printf("%ld",suma);
    
    
    fclose(flujo);
    free(array);
    
    
 }