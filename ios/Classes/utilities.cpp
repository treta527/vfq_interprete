/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <string>
#include <iostream>
#include "utilities.h"


using namespace std;

char *limpiarArray(char *array) {
    char *salida = new char[1024];
    int size = getSize(array);
    int ind = 0;
    int x = 0;
    for (int i = 0; i < size; i++) {
        uint8_t ch = array[i];
        //        std::cout << ch << " = " <<(ch & 0xff) << " " << i << "\n";
        if (ch > 0x40 && ch <= 0x5A) {
            //            std::cout << ch << " = " << i << "\n";
            salida[ind++] = array[i];
            x = 0;
        } else if ((ch && 0x0ff) == 32 || ch == 0x20) {
            //            std::cout << ch << " = " << i << "\n";
            salida[ind++] = array[i];
            x = 0;
        } else if (ch == 0xD1 || (ch & 0xff) == 145) {
            //            std::cout << ch << " = " << i << "\n";
            salida[ind++] = 78;
            x = 0;
        } else if (ch == 0x2B || ch == 0x2D) {
            //            std::cout << ch << " + - " << i << "\n";
            salida[ind++] = array[i];
            x = 0;
        } else if (ch >= 0x61 && ch <= 0x7A) {
            //            std::cout << ch << " = " << i << "\n";
            salida[ind++] = array[i];
            x = 0;
        } else {
            if ((ch & 0xff) != 195) {
                if (x < 5) {
                    //                    std::cout << array[i] << " = " << i << "\n";
                    salida[ind++] = 42;
                    x++;
                }
            }
        }
    }
    return salida;
}

char *limpiarNumeros(char *array) {
    char *salida = new char[1024];
    int size = getSize(array);
    int ind = 0;
    int x = 0;
    for (int i = 0; i < size; i++) {
        uint8_t ch = array[i];
        if (ch >= 0x30 && ch <= 0x39) {
            salida[ind++] = array[i];
//            std::cout << ch << " = " << i << "\n";
            x=0;
        } else {
              if (x < 5) {
                    //                    std::cout << array[i] << " = " << i << "\n";
                    salida[ind++] = 42;
                    x++;
                }
        }
    }
    return salida;
}

int getSize(std::string str) {
    return str.size();
}

char* getTextoData(const char * datos, int i, int j) {
    char *texto = new char[100];
    int posicion = i + j - 1;
    for (; posicion >= i; posicion--) {
        if ((datos[posicion]) == 0 || (datos[posicion]) == 32) {
        } else {
            goto romper;
        }
    }
romper:
    int pos = 0;
    for (int k = i; k <= posicion; k++) {
        if (datos[k] + 128 != 0) {
            texto[pos++] = datos[k];
        }

    }
    texto[pos] = 0;
    return texto;
}

int getTipoCedula(const char* rawData, int length) {
    if (rawData[0] == 48 && rawData[1] == 50)
        return CEDULA_TIPO_02;
    if (rawData[0] == 48 && rawData[1] == 51)
        return CEDULA_TIPO_03;
    if (rawData[0] == 73 && rawData[1] == 51)
        return TARJETA_IDENTIDAD_TIPO_I3;
    return 0;
}