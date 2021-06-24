#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <commons/string.h>
#include <commons/collections/list.h>


typedef struct t_tripulante {
    uint32_t id_tripulante;
    char estadoTripulante;
}t_tripulante;



t_list *tripulantes_ready;
t_list *tripulantes_new;
t_list *tripulantes_totales;



int encontrar_index_en_lista(t_list *lista,uint32_t id_tripulante_buscado){
    int i = 0;
    int index;
    t_tripulante* unTripAux;
    unTripAux = malloc(sizeof(t_tripulante));
    while(lista != NULL){
       unTripAux = lista->head->data;
        if(unTripAux -> id_tripulante == id_tripulante_buscado){
         index = i;
         break;
        }
        lista ->head = lista->head->next;
        i++;
   }

    free(unTripAux);
    return index;
  }


t_tripulante *buscar_tripulante(uint32_t id_tripulante)
{

		t_tripulante *p = NULL;
		for (int i = 0; i < list_size(tripulantes_totales); i++)
		{
			p = list_get(tripulantes_totales, i);
			uint32_t id_tripulante_2 = p->id_tripulante;
			if (id_tripulante == id_tripulante_2)
				break;
			p = NULL;
		}
		return p;
}




t_list *la_lista_que_quiero(char estado){
    if(estado == 'n'){
        return tripulantes_new;
    }
    if(estado == 'r'){
        return tripulantes_ready;
    }

}


char *f_actualizar_estado_tripulante(uint32_t id_tripulante_buscado, char nuevo_estado){


    t_tripulante *tripulante_buscado; //=  malloc(sizeof(t_tripulante));
    tripulante_buscado = buscar_tripulante(id_tripulante_buscado);
    printf("%s","id del tripulante buscado -> ");
    printf("%d\n",tripulante_buscado->id_tripulante);
    if(tripulante_buscado != NULL){

        char estadoAnt = tripulante_buscado->estadoTripulante;
        //printf("%s\n","antes de asignar el nuevo estado");
        tripulante_buscado->estadoTripulante = nuevo_estado;
       // printf("%s\n","despues de asignar el nuevo estado");
        t_list* listaAnt = list_create();
        listaAnt = la_lista_que_quiero(estadoAnt);
        //printf("%s\n","consegui la lista que quiero");
        t_list* listaEnLaQueAgrego = list_create();
        listaEnLaQueAgrego = la_lista_que_quiero(nuevo_estado);
        //printf("%s\n","consegui la lista en la que agrego");
        list_add(listaEnLaQueAgrego,tripulante_buscado);
       // printf("%s\n","agregue en la lista");
        list_remove(listaAnt,encontrar_index_en_lista(listaAnt,id_tripulante_buscado));
        //printf("Se actualizo el estado del tripulante\n");
        return nuevo_estado;
    }
    else{
        printf("No existe el tripulante\n");
    }
}


int main()
{
    tripulantes_totales = list_create();
    tripulantes_new = list_create();
    tripulantes_ready = list_create();
    t_tripulante* tripAux;
    t_tripulante* tripAux3;
    tripAux = malloc(sizeof(t_tripulante));
    tripAux->id_tripulante = 1;
    tripAux->estadoTripulante = 'n';
    tripAux3 = malloc(sizeof(t_tripulante));
    tripAux3->id_tripulante = 12;
    tripAux3->estadoTripulante = 'n';
    t_tripulante* tripAux2 = malloc(sizeof(t_tripulante));
    list_add(tripulantes_totales,tripAux);
    list_add(tripulantes_totales,tripAux3);
    list_add(tripulantes_new,tripAux);
    list_add(tripulantes_new,tripAux3);
    tripAux2 = buscar_tripulante(12);
    printf("%s\n","despues de buscar tripulante");
    char a = tripAux->estadoTripulante;
    printf("%s","estado del trip antes de actualizar -> ");
    printf("%c\n", a);
    f_actualizar_estado_tripulante(1,'r'); // no actializa el estado
    char x = tripAux->estadoTripulante;
    printf("%s","estado del trip despues  de actualizar -> ");
    printf("%c\n", x);
    t_tripulante* tripAux21 = malloc(sizeof(t_tripulante));
    tripAux21 = list_get(tripulantes_new,0);
    printf("%s","deberia devolver el id 12 -> ");
    printf("%d", tripAux21 -> id_tripulante);


    return 0 ;
}
