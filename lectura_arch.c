#include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
 #include <sys/time.h>
 #include<math.h>
 struct timespec start, end,toc,tic;
 double Elapsed,Elapsed1, Elapsed2;

 void ordenamiento_qs(int *arreglo,int inicio,int fin){
   int izq,der,pivote,aux;
   izq=inicio;
   der=fin;
   pivote= arreglo[((izq+der)/2)];
   do
   {
      while (arreglo[izq]<pivote && izq<fin) {
         izq++;
      }
      while (arreglo[der]>pivote && der>inicio) {
         der--;
      }
      
      if (izq<=der){
         aux=arreglo[izq];
         arreglo[izq]=arreglo[der];
         arreglo[der]=aux;
         izq++;
         der--;
      }
   } while (izq<=der);
   if (inicio<=der){
      ordenamiento_qs(arreglo,inicio,der);
   }
   if (fin>izq){
     ordenamiento_qs(arreglo,izq,fin);
   }
          

 }

 float calculo_media(long int suma,int n){  // funcion de la media
    return suma/n;
 }
 void ordenar_datos(int n,int *vector){ // ordenamiento de los datos    
    int aux;
    for(int i=0;i<n;i++){
        for(int x=i+1;x<n;x++){
        if(vector[i]>vector[x]){
            aux=vector[i];
            vector[i]=vector[x];
            vector[x]=aux;
        }
    }
  }
  for(int j=0;j<n;j++){
    printf("dato n (%d): %d \n",j,vector[j]);
  }
 }
 double varianza(float media,int n,int *vector1 ){
    double s=0 ; double r=0;
    for(int i=0;i<n;i++){

       r+=pow((vector1[i]-media),2);
     /*  if(i==2)
         printf("erre :%.8lf vector :%d media : %f ",r,vector1[i],media);
   */ }
    //s=(r)/n;
    r/=n;
    return r;
 }
 float desviacion_estandar(float s){
    return sqrt(s);
 }
 float mediana(int *array,int n){
    if(n%2 ==0)
      return(float)(array[(n/2)]+array[(n/2)+1])/2;
    else
      return array[(int)ceil(n/2)];
 }
 /*int dato_repetido(int *arreglo,int n){
   int aux ,d,c i=0 int v[n];
   aux=arreglo[i];
     while(i<n && i<=n-1){
        if(aux==vector[i+1]){
             d=aux;

             c=c+1;
        }
     }
 }*/


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
    printf("NUMERO DE DATOS : %d \n",nelementos);
    if (array!=NULL){
        for (int i = 0; i < nelementos; i++){
        fscanf(flujo,"%d*",&array[i]);
        }
    }
    /*fin del codigo a leer */
    clock_gettime(CLOCK_REALTIME, &end);
    Elapsed = (end.tv_sec - start.tv_sec)+((end.tv_nsec - start.tv_nsec)/1e9);
    printf("TIEMPO DE LECTURA : %.8lf\n",Elapsed);
   /*midiendo el tiempo de suma */
    clock_gettime(CLOCK_REALTIME,&start);
    long int suma;
    for(int j=0; j< nelementos; j++){
            suma+=array[j];
    }
    clock_gettime(CLOCK_REALTIME, &end);//fin del tiempo de suma
    Elapsed1= (end.tv_sec - start.tv_sec)+((end.tv_nsec - start.tv_nsec)/1e9);
    printf("TIEMPO DE SUMA : %.8lf\n",Elapsed1);
    printf(" SUMA : %ld \n",suma);
    printf("MEDIA : %f \n",calculo_media(suma,nelementos));
     /*midiendo el tiempo de ordenamiento*/
    clock_gettime(CLOCK_REALTIME,&start);
    //ordenar_datos(nelementos,array);
    ordenamiento_qs(array,0,nelementos-1);
     /*fin del codigo a leer */
    clock_gettime(CLOCK_REALTIME, &end);
    Elapsed2 = (end.tv_sec - start.tv_sec)+((end.tv_nsec - start.tv_nsec)/1e9);
    printf("TIEMPO DE ORDENAMIENTO CON BURBUJA : %.8lf\n",Elapsed2);
    float m=calculo_media(suma,nelementos);
    printf("VARIANZA : %.8lf \n",varianza(m,nelementos,array));
    printf("DESVIACION ESTANDAR :  %f \n",desviacion_estandar(varianza(m,nelementos,array)));
    printf("MEDIANA : %f \n",mediana(array,nelementos));
    fclose(flujo);
    free(array);
    
   return 0;    
 }

