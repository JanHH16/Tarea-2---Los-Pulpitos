#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "funciones.h"
#include "Map.h"

void agregarProducto (Map *mapaNombre){
  
  printf("Agregando producto...");
  productos * p = (productos*) malloc (sizeof(productos));
    //Asigando memoria a las variables *, ya que no funciona asignarlo en las estructuras 
      p->nombre = (char*) calloc (sizeof(char),50);
      p->marca = (char*) calloc (sizeof(char),30);
      p->tipo = (char*) calloc (sizeof(char),20);
    //////////////////////////////////////////////
  
  //Ingresaremos el nombre del producto, y si existe, se sumara al stock, saliendo de la funcion.
  printf("\nIngrese el nombre del Producto : "); scanf(" %[^\n]s",p->nombre);

  //Se busca con searchMap si existe, si no, sale
  productos *aux = searchMap(mapaNombre,p->nombre);
  if (aux != NULL){
    printf("Este producto ya existe, se agregara al stock ");
    aux->stock++; return;
  }
  //Si el producto no existe, se le agregara todo lo correspondiente para poder ser añadido al mapa
  printf("\nIngrese la marca del Producto : "); scanf(" %[^\n]s",p->marca);
  printf("\nIngrese el tipo de Producto : "); scanf(" %[^\n]s",p->tipo);
  printf("\nIngrese el stock total del Producto : "); scanf("%i",&p->stock);
  printf("\nIngrese el precio del Producto : "); scanf ("%i",&p->precio);
  //Añadimos al mapa
  insertMap(mapaNombre,p->nombre,p);
}

void buscar_producto_nombre(Map *mapaNombre){
  char nombreBuscado [30]; 
  printf ("Ingrese el Nombre del Producto a buscar : ");scanf (" %[^\n]s",nombreBuscado);
  //Buscar si existe con el searchMap
  productos * aux = searchMap(mapaNombre, nombreBuscado);
  //Si es NULL es porque no existe, y lo mostrara por pantalla
  if (aux == NULL){
    printf("producto buscado no existe"); 
    return;
  }
  //Si es !=NULL lo mostrara en pantalla
  printf("%s ,%s ,%s ,%i ,$%i", aux->nombre, aux->marca, aux->tipo, aux->stock, aux->precio);
}

//Hay que arreglarlo para usar listas y el mapa marca
void buscar_producto_marca(Map *mapaNombre){
  char nombreBuscado [30]; int cont=0;
  printf ("Ingrese la Marca del producto a buscar : ");scanf (" %[^\n]s",nombreBuscado);
  //Creamos el aux desde el inicio del mapa
  productos * aux = firstMap(mapaNombre);
  //Si es NULL es porque no existe, cuando sea NULL, saldra el while
  while (aux!=NULL){
    if(strcmp(aux->marca,nombreBuscado)==0){
      if (cont==0) printf("======== Mostrando los productos marca %s ========",nombreBuscado);
      printf("\n%s ,%s, ,%s ,%i ,$%i",aux->nombre,aux->marca,aux->tipo,aux->stock,aux->precio);
      cont++;
    }
    aux=nextMap(mapaNombre);
    }
  if (cont==0) printf("No existe esa marca\n");
}

//Hay que arreglarlo para usar listas y el mapa tipo
void buscar_producto_tipo(Map *mapaNombre){
  char nombreBuscado [30]; int cont=0;
  printf ("Ingrese el tipo de producto a buscar : "); scanf (" %[^\n]s",nombreBuscado);
  //Creamos el aux desde el inicio del mapa
  productos * aux = firstMap(mapaNombre);
  //Si es NULL es porque no existe, cuando sea NULL, saldra el while
  while (aux!=NULL){
    if(strcmp(aux->tipo,nombreBuscado)==0){
      if (cont==0) printf("======== Mostrando los productos de tipo %s ========",nombreBuscado);
      printf("\n%s ,%s, ,%s ,%i ,$%i",aux->nombre,aux->marca,aux->tipo,aux->stock,aux->precio);
      cont++;
    }
    aux=nextMap(mapaNombre);
  }
  if (cont==0) printf("No existe ese tipo\n");
}

void mostrarProductos(Map * mapaNombre){
  //Se crea un aux que recorra toda la funcion, muy similar a como lo hicimos
  //utilizando las listas enlazadas en la tarea 1 
    printf("============== MOSTRANDO TODOS LOS PRODUCTOS==============\n");
  productos * aux = firstMap(mapaNombre);
  while (aux != NULL){
    printf("%s, %s, %s, %i, $%i \n",aux->nombre,aux->marca,aux->tipo,aux->stock,aux->precio);
    aux = nextMap(mapaNombre);
  }
}

void agregar_al_carrito(List * carrito, Map * mapaNombre){
  char nombreBuscado[50]; int seguirComprando = 0; int cont = 0; int exit=0;
  productos *auxCarrito=firstList(carrito); int stock = 0; int auxStock = 0;

  //Ver si existe el producto, searchMap
  while(seguirComprando == 0){
    printf("¿Que producto desea agregar al carrito ? : "); scanf(" %[^\n]s",nombreBuscado);
    productos *auxProducto = searchMap(mapaNombre,nombreBuscado);
    //Si el producto no existe, se solicitara que ingrese uno valido
    if(auxProducto==NULL){
      while (exit==0){
        printf("\nIngrese un producto que exista : ");
        scanf(" %[^\n]s",nombreBuscado);
        auxProducto=searchMap(mapaNombre,nombreBuscado);
        if (auxProducto!=NULL) 
          exit=1;
      }
      exit=0;
    }

    //Cuantos productos quiere 
    printf("Cuantos quiere añadir ? Hay %i en stock : ",auxProducto->stock);
    scanf("%i",&stock);
    if((auxProducto->stock) < stock){
      while(exit==0){
      printf("\nStock no valido, ingrese a lo mas %i : ",auxProducto->stock);
      scanf("%d",&stock);
        if ((auxProducto->stock) >= stock) exit=1;
      }
      exit=0;
    }

    //Para reservar valores y cuidarlos
    auxProducto->stock=stock;
    pushBack(carrito,auxProducto);
    
    //Cont solo para iniciarla y despues para continuar en la lista
    if (cont == 0 ){
      auxCarrito=firstList(carrito);
      cont++;
    } else auxCarrito=nextList(carrito);
    
    //Mostrar el producto añadido
    printf("%s, %s, %s, %i, $ %i \n",auxCarrito->nombre,auxCarrito->marca,auxCarrito->tipo,auxCarrito->stock,(auxCarrito->precio)*(auxCarrito->stock));
 

    //Saber si quiere seguir comprando
    printf("¿Desea seguir comprando? (SI = 0, NO = 1) : ");  
    while(exit==0){
      scanf("%d", &seguirComprando);
      if(seguirComprando != 1 && seguirComprando != 0){
        printf("Ingrese un numero valido (SI = 0, NO = 1) : ");
      }else (exit=1);   
    }
    exit=0;
  }
}

void eliminar_del_carrito(List * carrito){
  productos * auxCarrito=firstList(carrito);
   while (auxCarrito != NULL){
    printf("%s, %s, %s, %i, %i \n",auxCarrito->nombre,auxCarrito->marca,auxCarrito->tipo,auxCarrito->stock,auxCarrito->precio);
    auxCarrito = nextList(carrito);
  }
  auxCarrito=popBack(carrito);
}

 void concretar_compra(List * carrito){
   productos *auxCarrito = firstList(carrito); int total_a_pagar=0;             
printf("========Total productos del carrito========\n");
while (auxCarrito != NULL){
printf("%s, %s, %s, %i, $%i \n",auxCarrito->nombre,auxCarrito->marca,auxCarrito->tipo,auxCarrito->stock,(auxCarrito->precio)*(auxCarrito->stock));
  //Se multiplica por el stock, asi nos da el precio total
  total_a_pagar = total_a_pagar + auxCarrito->precio*auxCarrito->stock;
 auxCarrito = nextList(carrito);
  }
   printf("\nTotal a pagar es = $%i \n",total_a_pagar);
 cleanList(carrito);
 free(carrito);
}

void mostrar_carrito(List * carrito){
  productos *auxCarrito = firstList(carrito);
  printf("========Total productos del carrito========\n");
  while (auxCarrito != NULL){
     //Se multiplica por el stock, asi nos da el precio total
    printf("%s, %s, %s, %i, $%i \n",auxCarrito->nombre,auxCarrito->marca,auxCarrito->tipo,auxCarrito->stock,auxCarrito->precio*auxCarrito->stock);
    auxCarrito = nextList(carrito);
  }
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

/*
  funcion para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

/*
  funcion para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

/*
  funcion para comparar claves de tipo int
  retorna 1 si son iguales
*/
int is_equal_int(void * key1, void * key2) {
    if(*(int*)key1 == *(int*)key2) return 1;
    return 0;
}

/*
  funcion para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}

// Funcion para leer el k-esimo elemento de un string (separado por comas)
const char *get_csv_field (char * tmp, int k) {
  int open_mark = 0;
  char* ret=(char*) malloc (100*sizeof(char));
  int ini_i=0, i=0;
  int j=0;
  while(tmp[i+1]!='\0'){
      if(tmp[i]== '\"'){
        open_mark = 1-open_mark;
        if(open_mark) ini_i = i+1;
        i++;
        continue;
      }
      if(open_mark || tmp[i]!= ','){
        if(k==j) ret[i-ini_i] = tmp[i];
        i++;
        continue;
      }
      if(tmp[i]== ','){
          if(k==j) {
          ret[i-ini_i] = 0;
          return ret;
        }
          j++; ini_i = i+1;
      }
      i++;
  }
  if(k==j) {
    ret[i-ini_i] = 0;
    return ret;
  }
  return NULL;
}    
