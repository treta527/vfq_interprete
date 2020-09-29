/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   utilities.h
 * Author: leonardo
 *
 * Created on 25 de septiembre de 2020, 02:54 PM
 */
#include <string>

#ifndef UTILITIES_H
#define UTILITIES_H
const int CEDULA_TIPO_02 = 2;
const int CEDULA_TIPO_03 = 3;
const int TARJETA_IDENTIDAD_TIPO_I3 = 4;

using namespace std;

char *limpiarArray(char *array);
char *limpiarNumeros(char *array);
int getSize(std::string str);
char* getTextoData(const char * datos, int i, int j);
int getTipoCedula(const char* rawData, int length);
#endif /* UTILITIES_H */


