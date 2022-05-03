#ifndef funciones.h
#define funciones.h

typedef struct List List;
typedef struct Map Map;

typedef struct {
  char *nombre;
  char *marca;
  char *tipo;
  int stock;
  int precio;
}productos;

void mostrarProductos (Map * mapaNombre);

void agregarProducto (Map *mapaNombre);

void buscar_producto_nombre(Map *mapaNombre);

void buscar_producto_marca(Map *mapaNombre);

void buscar_producto_tipo(Map *mapaNombre);

void agregar_al_carrito(List * carrito,  Map * mapaNombre);

void eliminar_del_carrito(List * carrito);

void concretar_compra(List * carrito);

void mostrar_carrito(List * carrito);

const char *get_csv_field (char * tmp, int k);

int is_equal_string(void * key1, void * key2);

int lower_than_string(void * key1, void * key2);

int is_equal_int(void * key1, void * key2);

int lower_than_int(void * key1, void * key2);


#endif 
