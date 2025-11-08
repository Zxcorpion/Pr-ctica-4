#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include "MediExpress.h"
#include "PaMedicamento.h"
#include "Laboratorio.h"
#include "Farmacia.h"
#include "Stock.h"

/**
 * @brief La funcion muestra por pantalla una farmacia con sus respectivos datos
 * @param farma Farmacia que vamos a mostrar
 * @post Se muestran por pantalla todos los datos relacionados con una farmacia
 */
void mostrarFarmacia(Farmacia &farma) {
    std::cout<<"CIF = " << farma.get_cif()
    << ", Provincia = " << farma.get_provincia()
    << ", Localidad = " << farma.get_localidad()
    << ", Nombre = " << farma.get_nombre()
    << ", Direccion = " << farma.get_direccion()
    << ", CodPostal = " << farma.get_cod_postal()
    << std::endl;
}

/**
 * @author Pablo Rodriguez Gniadek prg00054@red.ujaen.es
 * @author Marco Diaz Vera mdv00011@red.ujaen.es
 */
int main() {
    //Prueba 1
    MediExpress medBatman("../pa_medicamentos.csv","../lab2.csv","../farmacias.csv");
    std::vector<Farmacia*> farmas_Sevilla = medBatman.buscar_Farmacia_Provincia("SEVILLA");
    std::cout<<"Farmacias encontradas: "<< farmas_Sevilla.size()<<std::endl;// esto lo tengo como comprobacion de cuantas de sevilla hay
    int id_Magnes = 3640, id_Carbonato = 3632, id_Cloruro = 3633;
    PaMedicamento *oxido = 0, *carbonato = 0,*cloruro = 0;

    //Aqui empezamos a buscar los medicamentos
    //cambiar pq busca ahora es private
    for (int i = 0;i < farmas_Sevilla.size(); i++) {
        int stock_Magnesio = farmas_Sevilla[i]->buscaMedicamID(id_Magnes);
        int stock_Carbonat = farmas_Sevilla[i]->buscaMedicamID(id_Carbonato);
        int stock_Clorur = farmas_Sevilla[i]->buscaMedicamID(id_Cloruro);

        std::cout<<"==============================="<<std::endl;
        std::cout<<"Stock de cada medicamento de la Farmacia "<<i+1<< ": "<<farmas_Sevilla[i]->get_nombre()<<std::endl;
        std::cout<<"Oxido: "<<stock_Magnesio<<", Carbonato: "<<stock_Carbonat<<", Cloruro: "<<stock_Clorur<<std::endl;
        std::cout<<"==============================="<<std::endl;

        for (int j = 0; j < 12; j++) {
            //Hacemos las 12 compras
            if (farmas_Sevilla[i]->comprarMedicam(id_Magnes,1,oxido) > 0) {
                //hemos comprado sin problemas
            }else if (farmas_Sevilla[i]->comprarMedicam(id_Carbonato,1,carbonato) > 0) {
                std::cout<<"no hay oxido"<<std::endl;
                //compramos sin problemas
            }else if (farmas_Sevilla[i]->comprarMedicam(id_Cloruro,1,cloruro) > 0) {
                std::cout<<"no hay carbonato"<<std::endl;
                //compramos con exito
            }else{
                std::cout<<"La farmacia "<<farmas_Sevilla[i]->get_nombre()<<" no posee ninguno de los PaMeds que necesita, lo sentimos ^_^'"<<std::endl;
                //Con esto ya afirmo que no tengo que hacer las compras(posible cambio porque no se que quiere alvaro)
            }
        }
    }

    //Prueba2

    return 0;
}