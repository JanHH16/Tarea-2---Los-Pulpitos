#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "list.h"
#include "funciones.h"

//VAMO CHILEEEEEEEE

int main(){
  //Creamos el mapa
  Map * mapaNombre = createMap(is_equal_string);
  List * carrito =createList();
  
  char archivo[100];
  printf("Que archivo desea abrir ?\n");
  scanf("%s", archivo);
  
  //Abrimos el archivo
  //FILE *fp = fopen ("Archivo_100productos.csv","r");
  strcat(archivo,".csv");
  FILE *fp = fopen(archivo,"r");
  char datos[2000];
  
  //Llegar hasta 100, ya que son 100 productos.
  int cantidadProductos = 0;
  
  //Leemos el archivo csv y lo ingresamos a los mapas y listas 
  while(fgets(datos,2000,fp)!=NULL){
    productos *product = (productos *) malloc(sizeof(productos));
      product->nombre = get_csv_field(datos,0);
      product->marca = get_csv_field(datos,1);
      product->tipo = get_csv_field(datos,2);
      product->stock = atoi(get_csv_field(datos,3));
      product->precio = atoi(get_csv_field(datos,4));
  
    insertMap(mapaNombre,product->nombre,product);
    cantidadProductos++;
    if (cantidadProductos==100) break;
  }
  
  printf("INTRODUZCA UNA OPCION DEL MENU\n");
  printf("---------------------------------------\n");
  printf("OPCION 1 : IMPORTAR ARCHIVO DE PRODUCTOS (no funcional) \n");
  printf("OPCION 2 : EXPORTAR ARCHIVO DE PRODUCTOS (no funcional) \n");
  printf("OPCION 3 : AGREGAR PRODUCTO\n");
  printf("OPCION 4 : BUSCAR PRODUCTO POR TIPO\n");
  printf("OPCION 5 : BUSCAR PRODUCTO POR MARCA\n");
  printf("OPCION 6 : BUSCAR PRODUCTO POR NOMBRE\n");
  printf("OPCION 7 : MOSTRAR TODOS LOS PRODUCTOS\n");
  printf("OPCION 8 : AGREGAR PRODUCTO AL CARRITO\n");
  printf("OPCION 9 : ELIMINAR PRODUCTO\n");
  printf("OPCION 10: CONCRETAR LA COMPRA\n");
  printf("OPCION 11: MOSTRAR CARRITO DE COMPRA\n");
  printf("OPCION 0 : EXIT\n");

  while (1){
    int opcion;
    scanf("%d",&opcion);
    switch(opcion) {
      case 0:
        printf("=========Programa Cerrado=========");
        return 0;
      
      case 1: puts("IMPORTAR ARCHIVO DE PRODUCTOS... \n");
        break;
      
      case 2: puts("EXPORTAR ARCHIVO DE PRODUCTOS... \n");
        break;
      
      case 3: puts("AGREGAR PRODUCTO... \n");
        agregarProducto(mapaNombre);
        break;
      
      case 4: printf("BUSCAR PRODUCTO POR TIPO... \n");
        buscar_producto_tipo(mapaNombre);
        break;
      
      case 5: printf("BUSCAR PRODUCTO POR MARCA... \n");
        buscar_producto_marca(mapaNombre); 
        break;
      
      case 6: printf("BUSCAR PRODUCTO POR NOMBRE... \n");
        buscar_producto_nombre(mapaNombre);
        break;
      
      case 7: printf("MOSTRAR TODOS LOS PRODUCTOS... \n");
        mostrarProductos(mapaNombre);
        break;
      
      case 8: printf("AGREGAR PRODUCTO AL CARRITO... \n");
        agregar_al_carrito(carrito,mapaNombre);
        break;
      
      case 9: printf("ELIMINAR PRODUCTO... \n");
        eliminar_del_carrito(carrito);
        break;
      
      case 10: puts("CONCRETAR LA COMPRA... \n");
        concretar_compra(carrito);
        return 0;

      case 11: puts("MOSTRAR CARRITO DE COMPRA... \n");
        mostrar_carrito(carrito);
        break;
      
      default: puts(""); 
    }
  printf("\n===================================================================\n");
  printf("INGRESE OTRA OPCION : ");
  }
}
