/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <memory>
#include "convert.h"
#include <iostream>

using namespace std;

size_t getSizeArr(std::string str) {
    return str.size();
}

char* getCedulaColombianaData(char * rawDataOriginal, int length,int pdata) {
    printf("Entrando a método getCedulaColombiana ::: \n\n");
    int delta = 0;
    int deltaDepartment;
    long documentID;
    int cedulaType = 0;
    int deltaArray[9] = {48, 58, 81, 104, 127, 152, 166, 151, 160};
    char *texto = new char[531] {
        0
    };
    char *response;
    char *verification;
    char *rawData = new char[1400] {
        0
    };
    int sz = getSizeArr(rawDataOriginal);
//    std::cout << "\nTamaño converter: " << sz << "\n";

    int posRel = 0;
    for (int j = 0; j < length; j++) {
//        if (rawDataOriginal[j] == -64  ) {
        if (rawDataOriginal[j] == -64  ||  rawDataOriginal[j] == -81 || rawDataOriginal[j] == -62 ) {
           // std::cout << int(rawDataOriginal[j]) << "\n";
            j++;
            rawData[posRel++] = ' ';
        } else {
            rawData[posRel++] = rawDataOriginal[j];
        }
    }
    sz = getSizeArr(rawData);
//    std::cout << "Tamaño rawData: " << sz << "\n";
    response = getTextoData(rawData, 59, 1);
    delete[] response;
    if (length < 531) {
        strcpy(response, "{ \"resultado\": \"ERR\",\"mensaje\":\"Tamaño de array no compatible\" }");
        return response;
    } else {
        response = getTextoData(rawData, 48, 10);
        documentID = strtol(response, &verification, 10);
        delete[] response;
        cedulaType = getTipoCedula(rawData, length);
        switch (cedulaType) {
            case TARJETA_IDENTIDAD_TIPO_I3:
                response = getTextoData(rawData, 24, 8);
                if (!strcmp("PubDSK_1", response)) {
                    delta = 1;
                    deltaDepartment = 1;
               } else if (!strcmp("PubDSK_1", getTextoData(rawData, 94, 8))) {
                   deltaArray[0] = 158;
                    deltaArray[1] = 174;
                    deltaArray[2] = 277;
                    deltaArray[3] = 375;
                    deltaArray[4] = 488;
                    deltaArray[5] = 588;
                    deltaArray[6] = 602;
                    deltaArray[7] = 587;
                    deltaArray[8] = 596;
                    delta=0;
                    deltaDepartment = 0;
                } else {
                   strcat(response, "No se pudo procesar tarjeta de identidad PubDSK_1 no encontrado: ");
                   strcat(response, getTextoData(rawData, 94, 8));
                    goto error;
                }
                delete[] response;
                break;
            case CEDULA_TIPO_02:

                response = getTextoData(rawData, 22, 12);
                strtol(response, &verification, 10);
                if (*verification) {
                     strcpy(response, "No se pudo procesar cédula tipo 2 algopasó con verification");
                    goto error;
                } else {
                    delta = 0;
                    deltaDepartment = 1;
                }
                delete[] response;
                break;
            case CEDULA_TIPO_03:

                response = getTextoData(rawData, 24, 8);
                if (!strcmp("PubDSK_1", response)) {
                    delta = 0;
                    deltaDepartment = 0;
                } else if (!strcmp("PubDSK_1", getTextoData(rawData, pdata, 8))) {

                 deltaArray[0] = 158;
                    deltaArray[1] = 173;
                    deltaArray[2] = 266;
                    deltaArray[3] = 364;
                    deltaArray[4] = 477;
                    deltaArray[5] = 588;
                    deltaArray[6] = 596;
                    deltaArray[7] = 581;
                    deltaArray[8] = 590;
                    deltaDepartment = 0;
                    delta=0;
                } else {
                     strcpy(response, "No se pudo procesar cédula tipo 3 PubDSK_1 no encontrado : ");
                      strcat(response, getTextoData(rawData, pdata, 8));
                    goto error;
                }
                delete[] response;
                break;
            default:
 strcpy(response, "No se pudo definir el tipo de cédula");
                goto error;
        }

        strcat(texto, "{\"resultado\": \"OK\",\"documentID\": \"");
        strcat(texto, getTextoData(rawData, deltaArray[0]+delta, 10));
        strcat(texto, "\",\"surename\": \"");
        strcat(texto, getTextoData(rawData, deltaArray[1]+delta, 23));
        strcat(texto, "\", \"secondSurename\": \"");
        strcat(texto, getTextoData(rawData, deltaArray[2]+delta, 23));
        strcat(texto, "\", \"firstName\": \"");
        strcat(texto, getTextoData(rawData, deltaArray[3]+delta, 23));
        strcat(texto, "\", \"secondName\": \"");
        strcat(texto, getTextoData(rawData, deltaArray[4]+delta, 23));
        strcat(texto, "\", \"birthday\": \"");
        strcat(texto, getTextoData(rawData, deltaArray[5]+delta, 8));
        strcat(texto, "\", \"bloodType\": \"");
        strcat(texto, getTextoData(rawData, deltaArray[6]+delta, 3));
        strcat(texto, "\", \"gender\": \"");
        strcat(texto, getTextoData(rawData, deltaArray[7]+delta, 1));
        strcat(texto, "\", \"placeBirth\": \"");
        strcat(texto, getTextoData(rawData, deltaArray[8]+ deltaDepartment, 5));
        strcat(texto, "\"}");
      // strcat(texto, pdata+"");

        delete[] response;
        return texto;
error:
        strcat(response, "{ \"resultado\": \"ERR\",\"mensaje\":\"Error al interpretar documento\" }");
        return response;
    }
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

        if (datos[k] + 128 != 0 && datos[k] != 32) {
//            std::cout << datos[k] << "\n";
            texto[pos++] = datos[k];
        }

    }
    texto[pos] = 0;
    return texto;
}

char* decode(char* arr, char* response, int length) {
    char value[sizeof (int)*8 + 1] = "";
    char msg[60] = "";
    for (int i = 0; i < length; i++) {
        msg[i] = arr[i];
    }
    return strcpy(response, msg);
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