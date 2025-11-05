#include "MediExpress.h"

#include <map>


/**
 * @brief Constructor por defecto de la clase MediExpress
 * @post Se crea un objeto con los valores asignados por defecto
 */
MediExpress::MediExpress():
medication(),labs(),pharmacy() {
}

/**
 * @brief Constructor parametrizado de la clase MediExpress
 * @param medicamentos pasados por referencia
 * @param laboratorios pasador por referencia
 * @post Se crea un objeto de la clase MediExpress con los valores pasados por cabecera, que son leidos de varios ficheros .csv
 */
MediExpress::MediExpress(const std::string &medicamentos, const std::string &laboratorios, const std::string &farmacias) {
    std::ifstream is;
    std::stringstream  columnas;
    std::string fila;
    int contador=0;

    std::string id_number_string = "";
    std::string id_alpha="";
    std::string nombre="";


    is.open(medicamentos); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, id_number_string, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, id_alpha,';');
                getline(columnas, nombre,';');

                int id_num = 0;
                try {
                    id_num = std::stoi(id_number_string); ///Esta funcion pasa de string a int
                }catch (std::invalid_argument &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                PaMedicamento medicamento(id_num,id_alpha,nombre);
                try {
                    medication.push_back(medicamento);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.clear();

                std::cout << ++contador
                          << " Medicamento: ( Id_number=" << id_num
                          << " id_alpha=" << id_alpha << " Nombre=" << nombre
                          << ")" << std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    //Leemos el segundo fichero

    std::string id_numero_string = "";
    std::string nombreLab_ = "";
    std::string direccion_="";
    std::string codigPostal_="";
    std::string localidad_="";


    is.open(laboratorios); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_;direccion;codigPostal_;localidad_

                getline(columnas, id_numero_string, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, nombreLab_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, direccion_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, codigPostal_,';');
                getline(columnas, localidad_,';');

                int id_numero = 0;
                try {
                    id_numero = std::stoi(id_numero_string); ///Esta funcion pasa de string a int
                }catch (std::invalid_argument &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.clear();

                Laboratorio lab(id_numero,nombreLab_,direccion_,codigPostal_,localidad_);
                try {
                    std::list<Laboratorio>::iterator it = labs.begin();
                    while (it != labs.end() && it->getId() < id_numero) {
                        it++;
                    }
                    labs.insert(it,lab);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }


                std::cout << ++contador
                          << " Laboratorio: ( Id= " << id_numero
                          << " Nombre= " << nombreLab_ << " Direccion= " << direccion_
                          << " Codigo Postal= " <<codigPostal_
                          << " Localidad= "<< localidad_ <<std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    //Enlazamos cada laboratorio con 2 PAmedicamentos
    std::list<Laboratorio>::iterator itLaboratorio = labs.begin();
    int tam = 0;
//hay que cambiar esto por los corchetes, hacerlo con un iterador
    std::map<int,PaMedicamento>::iterator it_Medication = medication.begin();
    while (itLaboratorio != labs.end() && it_Medication != medication.end()) {
        this->suministrarMed(&it_Medication.first,&(*itLaboratorio));
        this->suministrarMed(&it_Medication.second,&(*itLaboratorio));
        it_Medication++;
        itLaboratorio++;
    }
    //int cont=0;
    /*for (int i=0; i<medication.tamlog_(); i++){
        if (medication[i].getServe()) {
            std::cout << "ID del PaMedicamento: " << medication[i].get_id_num()<<
                ", ID del Laboratorio asociado: " << medication[i].getServe()->getId() << std::endl;
        }else{
            cont++;
        }
    }
    */
    //La comprobacion sobra ya que el tamaño logico de sinLabs es el contador
    std::vector<Laboratorio*> labsMadrid = this->buscarLabCiudad("Madrid");
    std::vector<PaMedicamento*> medSin = this->getMedicamentoSinLab();
    std::cout << "Medicamentos sin asignar: " << medSin.size() << std::endl;

    for (int i = 0; i < medSin.size(); i++) {
        medSin[i]->servidoPor(labsMadrid[i]);
    }/* Comprobamos que ya no hay PAmedicamentos sin laboratorio asignado
    int cont2=0;
    for (int i=0; i<medication.tamlog_(); i++) {
        if (!medication[i].getServe()) {
            cont2++;
        }
    }
    std::cout<<cont2<<std::endl;
    */ //Comprobacion de que no hay ninguno sin asignar ahora


    //Leemos el tercer archivo
    std::string cif_ = "";
    std::string provincia_= "";
    std::string localidadLab_= "";
    std::string nombre_= "";
    std::string direccionLab_= "";
    std::string codPostal_= "";

    is.open(farmacias); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, cif_, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia_,';');
                getline(columnas, localidadLab_,';');
                getline(columnas, nombre_,';');
                getline(columnas, direccionLab_,';');
                getline(columnas, codPostal_,';');


                Farmacia farmacia_(cif_,provincia_,localidadLab_,nombre_, direccionLab_, codPostal_,this);
                try {
                    pharmacy.insertar(farmacia_);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.str(std::string());
                columnas.clear();
                columnas.str(fila);

                std::cout << ++contador
                          << " Farmacia: ( CIF = " << cif_
                          << " Provincia = " << provincia_ << " Localidad = " << localidadLab_
                          << " Nombre = " << nombre_ << " Direccion = " << direccionLab_ << " CodPostal = " << codPostal_
                          << ")" << std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    //abrir fichero para meter vector de string
    std::vector<std::string> vectorCIFS;
    is.open(farmacias); //carpeta de proyecto
    if ( is.good() ) {

        clock_t t_ini = clock();

        while ( getline(is, fila ) ) {

            //¿Se ha leído una nueva fila?
            if (fila!="") {

                columnas.str(fila);

                //formato de fila: id_number;id_alpha;nombre;

                getline(columnas, cif_, ';'); //leemos caracteres hasta encontrar y omitir ';'

                try {
                    vectorCIFS.push_back(cif_);
                }catch (std::out_of_range &e) {
                    std::cerr<<e.what()<<std::endl;
                }

                fila="";
                columnas.str(std::string());
                columnas.clear();
                columnas.str(fila);

                std::cout << ++contador
                          << " CIF de Farmacia = " << cif_
                          <<  std::endl;
            }
        }

        is.close();

        std::cout << "Tiempo de lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


    //Aniadimos todos los cifs a cada farmacia
    //hay que cambiar esto, no vale j vale iterador cuando llegue al final
    std::map<int,PaMedicamento>::iterator it_asignar_LabsMedi = medication.begin();

    for (int i= 0; i<vectorCIFS.size();i++) {
        Farmacia farmaciaInsercion;
        farmaciaInsercion.set_cif(vectorCIFS[i]);
        Farmacia *farmacia_auxiliar = pharmacy.buscaRec(farmaciaInsercion);
        int contador=0;
        while (contador<100) {
            suministrarFarmacia(farmacia_auxiliar,medication[indiceBucle].get_id_num());
            if (indiceBucle==medication.size()-1) {
                indiceBucle=0;
            }else {
                indiceBucle++;
                contador++;
            }
        }
    }

}

/**
 * @brief Constructor de copia de la clase MediExpress
 * @param orig objeto que vamos a copiar
 * @post Se crea un objeto de la clase MediExpress copiando el objeto pasado por cabecera
 */
MediExpress::MediExpress(const MediExpress &orig):
medication(orig.medication),labs(orig.labs), pharmacy(orig.pharmacy)
{}
/**
 * @brief Operador de igualacion
 * @param orig objeto de la clase MediExpress del que quieren coger los datos
 * @return Devuelve *this ya modificado o no
 * @post El metodo asigna los mismos valores del objeto pasado por cabecera
 */
MediExpress &MediExpress::operator=(const MediExpress &orig) {
    if(this!=&orig) {
        medication = orig.medication;
        labs = orig.labs;
        pharmacy = orig.pharmacy;
    }
    return *this;
}

/**
 * @brief Funcion para establecer un valor al atributo medication
 * @param medication valor que queremos asignar a medication
 * @post El atributo medication es modificado por un nuevo valor
 */
void MediExpress::set_medication(const std::vector<PaMedicamento> &medication) {
    this->medication = medication;
}


/**
 * @brief Funcion para establecer un valor al atributo labs
 * @param labs valor que queremos asignar a nuestro atributo labs
 * @post El atributo labs es modificado por un nuevo valor
 */
void MediExpress::set_labs(const std::list<Laboratorio> &labs) {
    this->labs = labs;
}

/**
 * @brief Destructor de los objetos MediExpress
 * @post Se libera la memoria
 */
MediExpress::~MediExpress() {
}

/**
 * @brief Funcion para asociar un laboratorio a un medicamento
 * @param pa Puntero de Pamedicamento
 * @param l Puntero de Laboratorio
 * @post PaMedicamento pasado por cabecera es asociado con un laboratorio
 */
void MediExpress::suministrarMed(PaMedicamento *pa, Laboratorio *l) {
    if (pa && l != 0 )
    pa->servidoPor(l);
}

/**
 * @brief Funcion para buscar un laboratorio
 * @param nombreLab pasado por referencia
 * @return &aux.dato si se ha encontrado el laboratorio o 0 si no se ha encontrado
 */
Laboratorio *MediExpress::buscarLab(const std::string &nombreLab) {
    std::list<Laboratorio>::iterator aux=labs.begin();
    while (aux!=labs.end()) {
        if(aux->getNomrbeLab().find(nombreLab) != std::string::npos) {
            return &(*aux);
        }
        aux++;
    }
    return 0;
}

/**
 * @brief Funcion para buscar laboratorios de una ciudad
 * @param nombreCiudad pasada por referencia
 * @return vector con los laboratorios que se encuentran en la ciudad pasada por cabecera
 */
std::vector<Laboratorio*> MediExpress::buscarLabCiudad(const std::string &nombreCiudad) {
    std::vector<Laboratorio*> vector;
    std::list<Laboratorio>::iterator aux=labs.begin();
    while (aux!=labs.end()) {
        if(aux->getLocalidad().find(nombreCiudad) != std::string::npos) {
            vector.push_back(&(*aux));
        }
        aux++;
    }
    return vector;
    }

}

/**
 * @brief Funcion para buscar compuestos en un vector dinamico de PaMedicamento
 * @param nombrePA  pasado por referencia
 * @return vector con los medicamentos que contienen el nombre pasado por referencia
 * @post se crea un vector auxiliar y se inserta en el lo medicametnos convenientes
 */
std::vector<PaMedicamento*> MediExpress::buscaCompuesto(const std::string &nombrePA) {
    std::vector<PaMedicamento*>auxiliar;

    for(std::map<int,PaMedicamento>::iterator aux = medication.begin();aux != medication.end();aux++) {
        if(aux->second.get_nombre().find(nombrePA) != std::string::npos) {
            auxiliar.push_back(&(aux->second));
        }
    }
    return auxiliar;
}

/**
 * @brief Funcion para leer un vector de medicamentos que no tienen asociados un laboratorio
 * @return aux, vector con todos los medicamentos sin laboratorio asociado
 * @post se crea y se modifica un vector con medicamentos dentro del él
 */
std::vector<PaMedicamento*> MediExpress::getMedicamentoSinLab() {
    std::vector<PaMedicamento*> aux;
    std::map<int,PaMedicamento>::iterator it_busca_SinLab = medication.begin();
    while (it_busca_SinLab != medication.end()) {
        if (!it_busca_SinLab->second.servidoPor())
        aux.push_back(&(it_busca_SinLab->second));
    }
    return aux;
}

/**
 * @brief Funcion para borrar laboratorios de forma correcta
 * @param nombreCiudad pasado por referencia
 * @post se borran todos los medicamentos que coinciden con el nombre pasado por referencia y desenlaza el laboratorio de sus medicamentos
 */
void MediExpress::borrarLaboratorio(const std::string &nombreCiudad) {
    std::list<Laboratorio>::iterator encontrado=labs.begin();

    int cont=0;
    for(int i=0;i<medication.size();i++) {
        if(medication[i].getServe() !=nullptr && medication[i].getServe()->getLocalidad().find(nombreCiudad) != std::string::npos) {
            medication[i].servidoPor(nullptr);
        }else {
            cont++;
        }
    }
    if(cont==medication.size()) {
        throw std::invalid_argument("Error al localizar la localidad");
    }
    while(encontrado != labs.end()) {
        if(encontrado->getLocalidad().find(nombreCiudad) != std::string::npos) {
            encontrado = labs.erase(encontrado);
        }else
            encontrado++;
    }
}

/**
 * @brief Metodo que se encarga de buscar un medicamento segun su id
 * @param ID_ Id del PAmedicamento a buscar
 * @return PAmedicamento que se quiere buscar
 * @post El medicamento buscado es encontrado y devuelto, en caso de no encontrarse, se devuelve un puntero a null
 */
PaMedicamento *MediExpress::buscaCompuesto(const int &ID_) {
    for(std::map<int,PaMedicamento>::iterator it_Batman = medication.begin();it_Batman != medication.end();it_Batman++) {
        if(it_Batman->second.get_id_num() == ID_) {
            return &(it_Batman->second);
        }
    }
    return 0;
}

/**
 * @brief El metodo permite suministrar un PAmedicamento en caso de que la farmacia no lo tenga
 * @param farma Farmacia sobre la que queremos añadir el PAmedicamento
 * @param ID_ ID del PAmedicamento que se quiere buscar
 */
void MediExpress::suministrarFarmacia(Farmacia *farma, int ID_) {
    PaMedicamento *medicam = buscaCompuesto(ID_);
    if (medicam) {
        farma->nuevoStock(medicam,n);
    // }else {
    //     throw std::invalid_argument("Error al suministrar farmacia: Medicamrnto no encontrado");
    }
}

/**
 * @brief Funcion para buscar una farmacia en funcion de su cif
 * @param cif_ cif de la Farmacia
 * @return puntero de la farmacia encontrada
 */
Farmacia *MediExpress::buscaFarmacia(const std::string &cif_) {
    Farmacia auxiliar;
    auxiliar.set_cif(cif_);
    return pharmacy.buscaRec(auxiliar);
}

/**
 * @brief Funcion para buscar laboratorios en funcion de nombrePA
 * @param nombrePA PaMedicamento
 * @return lista de laboratorios encontrados
 */
std::list<Laboratorio*> MediExpress::buscarLabs(const std::string &nombrePA) {
   std::list<Laboratorio*> lista;
   for (int i =0; i<medication.size();i++) {
       Laboratorio *auxilio = medication[i].getServe();
       if (medication[i].get_nombre() == nombrePA) {
           lista.push_back(auxilio);
       }
   }
    return lista;
}
