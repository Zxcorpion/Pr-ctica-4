//
// Created by marco on 05/11/2025.
//

#ifndef STOCK_H
#define STOCK_H

#include "PaMedicamento.h"

class Stock {
private:
    int id_Pa_Med=0;
    int num_stock=0;
    PaMedicamento* number=nullptr;
public:
    Stock();
    Stock(int id=0, int num=0);
    Stock(const Stock& orig);
    virtual ~Stock();
    int getId_Pa_Med()const;
    int getNumStock()const;
    void setId_Pa_Med(int& parametro);
    void setNumStock(int& parametro);
    void incrementa(int cantidad);
    void decrementa(int cantidad);
    bool operator<(const Stock& parametro);
    bool operator==(const Stock& parametro);
    void set_PaMedicamento(PaMedicamento* aux);
};



#endif //STOCK_H
