#include "Farmacia.h"
#include "MediExpress.h"

/**
 * @brief Constructor por defecto y parametrizado
 * @param cif CIF de la farmacia
 * @param provincia Provincia donde se encuantra la farmacia
 * @param localidad Localidad donde se encuantra la farmacia
 * @param nombre Nombre de la farmacia
 * @param direccion Direccion de la farmacia
 * @param codPostal Codigo postal de la farmacia
 * @param link Atributo que asocia una farmacia con MediExpress
 * @post Se crea un objeto Farmacia con los atributos pasados por cabecera
 */
Farmacia::Farmacia(std::string cif, std::string provincia, std::string localidad,
                   std::string nombre, std::string direccion, std::string codPostal, MediExpress *link):
cif_(cif),
provincia_(provincia),
localidad_(localidad),
nombre_(nombre),
direccion_(direccion),
codPostal_(codPostal),
linkMedi(link) {
}

/**
 * @brief Constructor copia de un objeto Farmacia
 * @param orig Objeto Farmacia que vamos a copiar
 * @post Se crea un objeto Farmacia asignando a sus atributos los valores de los atributos orig pasado por cabecera
 */
Farmacia::Farmacia(const Farmacia &orig):
cif_(orig.cif_),
provincia_(orig.provincia_),
localidad_(orig.localidad_),
nombre_(orig.nombre_),
direccion_(orig.direccion_),
codPostal_(orig.codPostal_),
linkMedi(orig.linkMedi)
{}

/**
 * @brief Destructor de Farmacia
 * @post Se libera la memoria correspondiente
 */
Farmacia::~Farmacia() {
    linkMedi = 0;
}
/**
 * @brief Función para leer el atributo cif_
 * @return Devuelve el atributo cif_
 */
std::string Farmacia::get_cif() const {
    return cif_;
}
/**
 * @brief Función para establecer un  cif_
 * @param cif nuevo valor al atributo cif_
 */
void Farmacia::set_cif(const std::string &cif) {
    cif_ = cif;
}
/**
 * @brief Función para leer el atributo provincia_
 * @return Devuelve el atributo provincia_
 */
std::string Farmacia::get_provincia() const {
    return provincia_;
}
/**
 * @brief Función para establecer un provincia_
 * @param provincia nuevo valor al atributo provincia_
 */
void Farmacia::set_provincia(const std::string &provincia) {
    provincia_ = provincia;
}
/**
 * @brief Función para leer el atributo localidad_
 * @return Devuelve el atributo localidad_
 */
std::string Farmacia::get_localidad() const {
    return localidad_;
}
/**
 * @brief Función para establecer un localidad_
 * @param localidad nuevo valor al atributo localidad_
 */
void Farmacia::set_localidad(const std::string &localidad) {
    localidad_ = localidad;
}
/**
 * @brief Función para leer el atributo nombre_
 * @return Devuelve el atributo nombre_
 */
std::string Farmacia::get_nombre() const {
    return nombre_;
}
/**
 * @brief Función para establecer un nombre_
 * @param nombre nuevo valor al atributo nombre_
 */
void Farmacia::set_nombre(const std::string &nombre) {
    nombre_ = nombre;
}
/**
 * @brief Función para leer el atributo direccion_
 * @return Devuelve el atributo direccion_
 */
std::string Farmacia::get_direccion() const {
    return direccion_;
}
/**
 * @brief Función para establecer un codigo direccion_
 * @param direccion nuevo valor al atributo direccion_
 */
void Farmacia::set_direccion(const std::string &direccion) {
    direccion_ = direccion;
}
/**
 * @brief Función para leer el atributo codPostal_
 * @return Devuelve el atributo codPostal_
 */
std::string Farmacia::get_cod_postal() const {
    return codPostal_;
}
/**
 * @brief Función para establecer un codigo postal
 * @param cod_postal nuevo valor al atributo codpostal_
 */
void Farmacia::set_cod_postal(const std::string &cod_postal) {
    codPostal_ = cod_postal;
}

/**
 * @brief Operador de asignacion de la clase Farmacia
 * @param orig  Objeto que usamos de referencia para asignar valores a nuestro objeto
 * @return Farmacia con los atributos de otra farmacia
 * @post Objeto this cambia los valores de sus atributos
 */
Farmacia &Farmacia::operator=(const Farmacia &orig) {
    if (this != &orig) {
        cif_ = orig.cif_;
        provincia_ = orig.provincia_;
        localidad_ = orig.localidad_;
        nombre_ = orig.nombre_;
        direccion_ = orig.direccion_;
        codPostal_ = orig.codPostal_;
    }
    return *this;
}

/**
 * @brief Operador <
 * @param orig Objeto pasado por referencia
 * @return bool si this->cif_ es menor al de orig
 */
bool Farmacia::operator<(const Farmacia &orig) const {
    return cif_ < orig.cif_;
}
/**
 * @brief Operador ==
 * @param orig Objeto pasado por referencia
 * @return bool si this->cif_ es igual al de orig
 */
bool Farmacia::operator==(const Farmacia &orig) const {
    return cif_ == orig.cif_;
}
/**
 * @brief Operador >
 * @param orig Objeto pasado por referencia
 * @return bool si this->cif_ es mayor al de orig
 */
bool Farmacia::operator>(const Farmacia &orig) const {
    return cif_ > orig.cif_;
}

/**
 * @brief Funcion para pedir un medicamento
 * @param ID Id del PAmedicamento a buscar
 * @post La farmacia es suministrada con un nuevo PAmedicamento
 */
void Farmacia::pedidoMedicam(const int &ID) {
    linkMedi->suministrarFarmacia(this, ID);
}

/**
 * @brief Fucnion para encontrar un medicamento segun su ID
 * @param ID del PAmedicamento a buscar
 * @return PAmedicamento a buscar segun su ID
 * @post El PAmedicamento a buscar es devuelto, en casod e no encontrarlo se devuelve nullptr
 */
PaMedicamento *Farmacia::buscaMedicam(const int &ID) {
    for (int i = 0; i < dispense.size(); i++) {
        if (ID == dispense[i]->get_id_num()) {
            return dispense[i];
        }
    }
    //     pedidoMedicam(ID);
    //
    return 0;
}


/**
 * @brief Funcion para buscar medicamentos y meterl en una lista los laboratorios que usan esos PaMedicamentos
 * @param  nombre_PAmed
 * @return Devuelve una lista con todos los laboratorios que tienen un determinado PAmedicamento
 */
std::vector<Laboratorio*> Farmacia::buscarLabCompuesto(const std::string &nombre_PAmed) {
    std::vector<Laboratorio *> listaWayne;
    for (int i = 0; i < this->dispense.tamlog_(); i++) {
        PaMedicamento *med = dispense[i];
        if (med && med->get_nombre().find(nombre_PAmed) != std::string::npos) {
            Laboratorio *aux = med->getServe();
            if (aux)
                listaWayne.push_back(aux);
        }
    }
    return listaWayne;
}
