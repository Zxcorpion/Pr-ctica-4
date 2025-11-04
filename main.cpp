#include <iostream>
#include <sstream>
#include <fstream>
#include "MediExpress.h"
#include "PaMedicamento.h"
#include "Laboratorio.h"
#include <vector>
#include "AVL.h"
#include "Farmacia.h"

/**
 * @brief Funcion que sirve para leer datos de un fichero e introducirlos en un arbol AVL
 * @param fichero Fichero del que se quiere leer los datos
 * @return Arbol AVL con los datos del fichero
 * @post Un arbol AVL es creado con todos los datos de un fichero
 */
AVL<Farmacia> leeFicheroArbol(const std::string &fichero) {
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string cif_ = "";
    std::string provincia_= "";
    std::string localidad_= "";
    std::string nombre_= "";
    std::string direccion_= "";
    std::string codPostal_= "";

    AVL<Farmacia> arbolFarmacia;

    is.open(fichero); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, cif_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia_,';');
                getline(columnas, localidad_,';');
                getline(columnas, nombre_,';');
                getline(columnas, direccion_,';');
                getline(columnas, codPostal_,';');

                fila="";
                columnas.clear();

                Farmacia farmacia_(cif_,provincia_,localidad_,nombre_, direccion_, codPostal_);
                try {
                    arbolFarmacia.insertar(farmacia_);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }


                std::cout << ++contador
                          << " Farmacia: ( CIF = " << cif_
                          << " Provincia = " << provincia_ << " Localidad = " << localidad_
                          << " Nombre = " << nombre_ << " Direccion = " << direccion_ << " CodPostal = " << codPostal_
                          << ")" << std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    return arbolFarmacia;
}

/**
 * @brief Funcion que sirve para leer datos de un fichero e introducirlos en un vector dinamico
 * @param fichero Fichero del que se quiere leer los datos
 * @return Vector dinamico con los datos del fichero
 * @post Un vector dinamico es creado con todos los datos de un fichero
 */
std::vector<Farmacia> leeFicheroVector(const std::string &fichero) {
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string cif_ = "";
    std::string provincia_="";
    std::string localidad_="";
    std::string nombre_="";
    std::string direccion_="";
    std::string codPostal_="";

    std::vector<Farmacia> vectorFarmacia;

    is.open(fichero); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, cif_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia_,';');
                getline(columnas, localidad_,';');
                getline(columnas, nombre_,';');
                getline(columnas, direccion_,';');
                getline(columnas, codPostal_,';');


                Farmacia farmacia_(cif_,provincia_,localidad_,nombre_, direccion_, codPostal_);
                try {
                    vectorFarmacia.push_back(farmacia_);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.clear();

                std::cout << ++contador
                          << " Farmacia: ( CIF = " << cif_
                          << " Provincia = " << provincia_ << " Localidad = " << localidad_
                          << " Nombre = " << nombre_ << " Direccion = " << direccion_ << " CodPostal = " << codPostal_
                          << ")" << std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    return vectorFarmacia;
}

/**
 * @brief Funcion para calcular el tiempo de busqueda en un arbol usando la recursividad
 * @param vectorFarmacias  objeto VDinamico<Farmacia> pasado por referencia
 * @param arbol objeto de AVL<Farmacia> pasado por referencia
 * @param cifs string vector pasado por referencia
 * @param tiempo tiempo pasado por referencia para guardar el tiempo de busqueda
 */
void calcularbusqueda(std::vector<Farmacia> &vectorFarmacias,AVL<Farmacia> &arbol,std::string cifs[],float &tiempo) {
    clock_t t_ini = clock();
    for(int i=0;i<500;i++) {
        if(arbol.buscaRec(vectorFarmacias[i])->get_cif() != cifs[i]) {
            std::cout<<"No se encontro"<<std::endl;
        }
    }
    std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    tiempo=((clock() - t_ini) / (float) CLOCKS_PER_SEC);
}
/**
 * @brief Funcion para calcular el tiempo de busqueda en un arbol usando la busqueda iterativa
 * @param vectorFarmacias  objeto VDinamico<Farmacia> pasado por referencia
 * @param cifs string vector pasado por referencia
 * @param tiempo tiempo pasado por referencia para guardar el tiempo de busqueda
 */
void busquedasegundotipo(std::vector<Farmacia> &vectorFarmacias,std::string cifs[],float &tiempo) {
    clock_t t_ini = clock();
    for(int i=0;i<500;i++) {
        if(vectorFarmacias[i].get_cif()!=cifs[i]) {
            std::cout<<"No se encontro"<<std::endl;
        }
    }
    std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    tiempo=((clock() - t_ini) / (float) CLOCKS_PER_SEC);
}

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
    std::cout<<"Insercion de las farmacias en un arbol"<<std::endl;
    AVL<Farmacia> arbol1 = leeFicheroArbol("../farmacias.csv");
    std::cout<<"\n";
    std::cout<<"Insercion de las farmacias en un vector dinamico"<<std::endl;
    std::vector<Farmacia> vector1 = leeFicheroVector("../farmacias.csv");
    std::cout<<"\n";

    std::cout<<"Muestra por pantalla de las primeras 500 farmacias"<<std::endl;
    std::string vectorCIFS[500];
    for (int i=0; i<500; i++) {
        vectorCIFS[i] = vector1[i].get_cif();
    }

    std::cout<<"\n";
    std::cout<<"Conteo del tiempo sobre el arbol y sobre el vector"<<std::endl;

    float tiempo1=0, tiempo2=0;
    calcularbusqueda(vector1,arbol1,vectorCIFS,tiempo1);
    busquedasegundotipo(vector1,vectorCIFS,tiempo2);
    if(tiempo1 > tiempo2) {
        std::cout<<"Es mas eficiente buscar en AVL"<<std::endl;
    }else {
        if(tiempo2 > tiempo1) {
            std::cout<<"Es mas eficiente buscar en un vector dinamico"<<std::endl;
        }
    }
    if(tiempo1==tiempo2) {
        std::cout<<"Igual de eficiente"<<std::endl;
    }
    std::cout<<"\n";

    std::cout<<"La altura del arbol de farmacias es de: "<<arbol1.get_altura();
    std::cout<<"\n";

    std::cout<<"Mostrando farmacias desde inorden";
    std::cout<<"\n";

    std::vector<Farmacia> vectorInorden = arbol1.recorreInorden();
    for (int i = 0; i<100; i++) {
        std::cout<<"Farmacia numero "<< i+1<<std::endl;
        mostrarFarmacia(vectorInorden[i]);
    }
    std::cout<<"\n";
    //Prueba 2

    MediExpress medi("../pa_medicamentos.csv","../lab2.csv","../farmacias.csv");
    std::string cif[27] = {
        "37656422V","46316032N", "77092934Q", "33961602D", "B62351861",
        "B62351861","B65828113", "46138599R", "35069965W", "37579913Y",
        "37682300C","37643742X", "46112335A", "47980171D", "38116138D",
        "46315600V","37640233C", "37931842N", "33964303L", "35022080A",
        "B66046640","E66748344", "47640201W", "B66621954", "46121385Z","X6806622W","46046390E"
    };


    std::cout<<"\n";
    int id=3640;
    for (int i = 0; i<27; i++) {
        Farmacia *farmaOxido = medi.buscaFarmacia(cif[i]);//Cogemos una farmacia
        PaMedicamento *medicam = farmaOxido->buscaMedicam(id);//Nos guiamos con el id

        if (!medicam) {
            std::cout<<"Los datos de la farmacia que contiene magnesio son: "<<std::endl;
            mostrarFarmacia(*farmaOxido);
        }else {
            farmaOxido->pedidoMedicam(id);
        }
    }
    std::vector<PaMedicamento*> medicamentosOxido= medi.buscaCompuesto("MAGNESIO");
    std::list<Laboratorio*> labsOxido;
    for (int i = 0; i<medicamentosOxido.size(); i++) {
        if (medicamentosOxido[i]->getServe()) {
            Laboratorio *auxilio = medicamentosOxido[i]->getServe();
            labsOxido.push_back(auxilio);
        }
    }
//Ejercicio por parejas
    std::vector<Laboratorio*> labsVirus;

    for (int i = 0; i<27; i++) {
        Farmacia *farmasVirus = medi.buscaFarmacia(cif[i]); //Aqui buscamos la farmacia en el vector de cifs
        if (farmasVirus != 0) {
            std::vector<Laboratorio*> aux = farmasVirus->buscarLabCompuesto("VIRUS");
            //Introducimos los elementos en la lista gracias al auxiliar para no perder datos
            for (int l = 0; l< aux.size(); l++) {
                labsVirus.push_back(aux[l]);
            }
        }
    }
    std::cout<<"Laboratorios que suministran medicamentos con virus:"<<std::endl;
    for (int j=0; j<labsVirus.size(); j++) {
        std::cout<<"Nombre: "<<labsVirus[j]->getNomrbeLab()<<std::endl;
    }



    return 0;
}