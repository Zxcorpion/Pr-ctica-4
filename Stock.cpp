//
// Created by marco on 05/11/2025.
//

#include "Stock.h"
Stock::Stock():
id_Pa_Med(0),num_stock(0)
{}
Stock::Stock(int id, int num):
id_Pa_Med(id),num_stock(num)
{}
Stock::Stock(const Stock& orig):
id_Pa_Med(orig.id_Pa_Med),num_stock(orig.num_stock)
{}
Stock::~Stock() {

}
int Stock::getId_Pa_Med()const{
    return id_Pa_Med;
}
int Stock::getNumStock()const{
    return num_stock;
}
void Stock::setId_Pa_Med(int& parametro) {
    id_Pa_Med = parametro;
}
void Stock::setNumStock(int& parametro) {
    num_stock = parametro;
}
void Stock::decrementa(int cantidad) {
    num_stock=num_stock-cantidad;
}
void Stock::incrementa(int cantidad) {
    num_stock=num_stock+cantidad;
}
bool Stock::operator<(const Stock &parametro) {
    return id_Pa_Med < parametro.id_Pa_Med;
}
bool Stock::operator==(const Stock &parametro) {
    return id_Pa_Med == parametro.id_Pa_Med;
}
void Stock::set_PaMedicamento(PaMedicamento *aux) {
    number=aux;
}
