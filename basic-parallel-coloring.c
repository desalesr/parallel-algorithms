#include <stdio.h>
#include <omp.h> /*Compilar con -fopenmp*/
#include <stdlib.h>
#include <time.h>
#include <math.h> /*Compilar con -lm*/



int IntToBin(int k);
void Shuffle(int array[], int length, int seed);
int NewColor(int color, int succ_color);

int main(int argc, char * argv[]) {
    
    int vertices_number; /*Cantidad de vértices*/
    int seed; /*Semilla del random*/
    
    if (argc != 3) { /*Checamos cantidad de argumentos*/
        printf("Número de argumentos inválidos");
        return 0;
    }
    /*Convertimos los argumentos a enteros*/
    vertices_number = atoi(argv[1]);
    seed = atoi(argv[2]);

    if(vertices_number <= 0 || seed <= 0) { /*Si hubo algún error en la conversión o son valores inválidos terminamos el programa */
        printf("Argumentos inválidos. Ambos deben ser dos números enteros positivos.");
        return 0;
    }
    int vertices_colors[vertices_number]; /*Arreglo de la cantidad de vértices del ciclo*/
    char * new_colors[vertices_number]; //Para la impresión de los resultados
    omp_set_num_threads(vertices_number); 
    #pragma omp parallel   /*Llenamos el arreglo en paralelo*/
    {/*Inicio sección paralela*/
        int i = omp_get_thread_num();
        vertices_colors[i] = i+1; /*Va de 1 a N*/
    }/*Final sección paralela*/
    printf("-------------------------------------\n");
    printf("|   v   |  rep. binaria  | k  |  c' |\n");
    printf("-------------------------------------\n");
    Shuffle(vertices_colors, vertices_number, seed);  /*Procedemos a revolverlo */
    #pragma omp parallel   /*Calculamos nuevos colores*/
    { /*Inicio sección paralela*/
        int i = omp_get_thread_num();
        int color = vertices_colors[i];
        int color_succ = vertices_colors[(i+1)%omp_get_num_threads()]; 
        #pragma omp barrier /*Sincronizamos los threads, esto para garantizar la consistencia
                             de las variables guardadas y la actualización sincronizada*/
        //new_vertices_colors[i] = NewColor(color, color_succ); /*Actualizamos el nuevo color en el arreglo de nuevos colores*/
        int new_color;
        int k = __builtin_ctz(color^color_succ);
        int ci_k =  (color >> k) & 1;
        int binary = 
        new_color = 2*k + ci_k;
        char buffer [128];
        sprintf(buffer, "|%-4d   | %14d | %d  | %-2d  |", vertices_colors[i],IntToBin(vertices_colors[i]), k, new_color);
        new_colors[i]= buffer;
    } /*Final sección paralela*/
    int i;
    for(i = 0; i < vertices_number; i++)
        printf("%s\n",new_colors[i]);
    printf("-------------------------------------\n");
}

/*Función para obtener la representación binaria de un número*/
int IntToBin(int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * IntToBin(k / 2)));
}
/*función que revuelve el arreglo pasado como parámetro*/
void Shuffle(int array[], int length, int seed) {
    srand(seed);
    int i;
    for (i = 0; i < length -1 ; i++) {
        size_t j = i + rand() / (RAND_MAX / (length - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}
/*Función que determina el nuevo color de la arista -YA NO UTILIZADA POR LA IMPRESIÓN EN FORMATO-*/
int NewColor(int color, int succ_color){
    int new_color;
    int k = __builtin_ctz(color^succ_color);
    int ci_k =  (color >> k) & 1;
    new_color = 2*k + ci_k;
    return new_color;
}
