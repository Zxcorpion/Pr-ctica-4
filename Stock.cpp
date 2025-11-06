#include "Stock.h"

Stock::Stock(int id, int num, PaMedicamento *number_):
id_Pa_Med(id),num_stock(num), number(number_)
{}
Stock::Stock(const Stock& orig):
id_Pa_Med(orig.id_Pa_Med),num_stock(orig.num_stock),number(orig.number)
{}
Stock::~Stock() {

}

int Stock::get_id_pa_med() const {
    return id_Pa_Med;
}

void Stock::set_id_pa_med(int id_pa_med) {
    id_Pa_Med = id_pa_med;
}

int Stock::get_num_stock() const {
    return num_stock;
}

void Stock::set_num_stock(int num_stock) {
    this->num_stock = num_stock;
}

PaMedicamento * Stock::get_number() const {
    return number;
}

void Stock::set_number(PaMedicamento *number) {
    this->number = number;
}

bool Stock::operator<(const Stock &parametro) const{
    return id_Pa_Med < parametro.id_Pa_Med;
}
bool Stock::operator==(const Stock &parametro) const{
    return id_Pa_Med == parametro.id_Pa_Med;
}

void Stock::incrementa(const int &cantidad) {
    num_stock+=cantidad;
}

void Stock::decrementa(const int &cantidad) {
    num_stock-=cantidad;
}
