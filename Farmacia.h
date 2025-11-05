//
// Created by admin on 21/10/2025.
//

#ifndef PRACTICA3_FARMACIA_H
#define PRACTICA3_FARMACIA_H
#include <iostream>
#include <set>
#include "Stock.h"
#include "Lista.h"
#include "PaMedicamento.h"
#include <vector>
class MediExpress;

/**
 * @brief Definicion de la clase Farmacia
 */
class Farmacia {
private:
    std::string cif_="-",provincia_="-",localidad_="-",
    nombre_="-",direccion_="-",codPostal_="-";
    MediExpress* linkMedi;
    std::set<Stock>order;
    int buscaMedicam(int& id_num);
public:
    Farmacia(std::string cif="-",std::string provincia="-",std::string localidad="-",
    std::string nombre="-",std::string direccion="-",std::string codPostal="-", MediExpress *link=0);
    Farmacia(const Farmacia &orig);
    virtual ~Farmacia();

    std::string get_cif() const;
    void set_cif(const std::string &cif);
    std::string get_provincia() const;
    void set_provincia(const std::string &provincia);
    std::string get_localidad() const;
    void set_localidad(const std::string &localidad);
    std::string get_nombre() const;
    void set_nombre(const std::string &nombre);
    std::string get_direccion() const;
    void set_direccion(const std::string &direccion);
    std::string get_cod_postal() const;
    void set_cod_postal(const std::string &cod_postal);

    Farmacia &operator=(const Farmacia& orig);
    bool operator==(const Farmacia &orig) const;
    bool operator<(const Farmacia &orig) const;
    bool operator>(const Farmacia &orig) const;
    void pedidoMedicam(int& id_num, int& robin);
    PaMedicamento* comprarMedicam(int& id_num, int& robin);
    void nuevoStock(PaMedicamento* batmelatonina,int& robin);
    bool eliminarStock(int& id_num);
};


#endif //PRACTICA3_FARMACIA_H