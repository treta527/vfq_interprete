/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "persona.h"
#include <string>
#include <cstring>
#include <memory>
#include "utilities.h"
using namespace std;

Persona getCedulaColombianaData(char * rawDataOriginal, int length) {
    char *response;
    long documentID;
    char *verification;
    Persona p;
    if (length > 531) {
        char *rawData = new char[1400] {
            0
        };

        int posRel = 0;
        for (int j = 0; j < length; j++) {
            if (rawDataOriginal[j] == -64 || rawDataOriginal[j] == -81 || rawDataOriginal[j] == -62) {
                j++;
                rawData[posRel++] = ' ';
            } else {
                rawData[posRel++] = rawDataOriginal[j];
            }
        }
        response = getTextoData(rawData, 48, 10);
        documentID = strtol(response, &verification, 10);
        delete[] response;
        int cedulaType = getTipoCedula(rawData, length);
        cout << "Cédula tipo: " << cedulaType << "\n\n";
        switch (cedulaType) {
            case TARJETA_IDENTIDAD_TIPO_I3:
                response = getTextoData(rawData, 24, 8);
                if (!strcmp("PubDSK_1", response)) {
                    p.extraer(rawData, 1, 1);
                } else {
                    response = limpiarArray(rawDataOriginal);
                    p.extraerNombres(getTextoData(response, 16, 100));
                    response = limpiarNumeros(rawDataOriginal);
                    p.extraerNumeros(getTextoData(response, 19, 100));
                }
                strcpy(p.documentType, "TI");
                break;
            case CEDULA_TIPO_02:
                response = getTextoData(rawData, 22, 12);
                strtol(response, &verification, 10);
                if (*verification) {
                    char e[70] = "No se pudo procesar cédula tipo 2 algopasó con verification";
                    p.addError(e);
                } else {
                    p.extraer(rawData, 0, 1);
                    strcpy(p.documentType, "CC");
                }
                delete[] verification;
                break;
            case CEDULA_TIPO_03:
                response = getTextoData(rawData, 24, 8);
                if (!strcmp("PubDSK_1", response)) {
                    p.extraer(rawData, 0, 0);
                } else {
                    response = limpiarArray(rawDataOriginal);
                    p.extraerNombres(getTextoData(response, 16, 100));
                    response = limpiarNumeros(rawDataOriginal);
                    p.extraerNumeros(getTextoData(response, 19, 100));
                }
                strcpy(p.documentType, "CC");
                break;
            default:
                response = limpiarArray(rawDataOriginal);
                char *ce = getTextoData(response, 19, 3);
                if (!strcmp("CE*", ce) || !strcmp("*CE", ce)) {
//                    cout << "Nombres: " << response << "\n";
                    p.extraerNombres(getTextoData(response, 24, 70));
                    response = limpiarNumeros(rawDataOriginal);
//                     cout << "Numeros: " << response << "\n";
                    p.extraerNumeros(getTextoData(response, 19, 100));
                    strcpy(p.documentType, "CE");
                    p.secondName[0]='\0';
                    p.birthday[0]='\0';
//                    p.bloodType[0]='\0';
//                    p.gender[0]='\0';
                    p.placeBirth[0]='\0';
                } else {
                    char e[50] = "Tipo de cédula no identificado";
                    p.addError(e);
                }
        }
        delete[] rawData;
        //        delete[] rawDataOriginal;

    } else {
        char e[50] = "Tamaño de array no compatible";
        p.addError(e);
    }
    return p;
}