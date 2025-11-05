//
// Created by admin on 21/10/2025.
//

#ifndef PRACTICA3_MEDIEXPRESS_H
#define PRACTICA3_MEDIEXPRESS_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

#include "AVL.h"
#include "PaMedicamento.h"
#include "Laboratorio.h"
#include <vector>
#include <list>
#include "Farmacia.h"


/**
 * @brief Definicion de la clase MediExpress
 */
class MediExpress {
private:
    std::map<int,PaMedicamento> medication;
    std::list<Laboratorio> labs;
    AVL<Farmacia> pharmacy;
public:
    MediExpress();
    MediExpress(const std::string &medicamentos, const std::string &laboratorios, const std::string &farmacias);
    MediExpress(const MediExpress &orig);
    ~MediExpress();

    MediExpress& operator=(const MediExpress &orig);


    void set_medication(const std::vector<PaMedicamento> &medication);
    void set_labs(const std::list<Laboratorio> &labs);

    void suministrarMed(PaMedicamento *pa,Laboratorio *l);
    Laboratorio *buscarLab(const std::string &nombreLab);
    std::list<Laboratorio*> buscarLabs(const std::string &nombrePA);
    std::vector<Laboratorio*> buscarLabCiudad(const std::string &nombreCiudad);
    std::vector<PaMedicamento*> buscaCompuesto(const std::string &nombrePA);
    std::vector<PaMedicamento*> getMedicamentoSinLab();
    void borrarLaboratorio(const std::string &nombreCiudad);
    PaMedicamento* buscaCompuesto(const int &ID_);
    void suministrarFarmacia(Farmacia *farma, int ID_);
    Farmacia* buscaFarmacia(const std::string &nombreFar);

};

#endif //PRACTICA3_MEDIEXPRESS_H