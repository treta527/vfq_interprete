/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   persona.h
 * Author: leonardo
 *
 * Created on 25 de septiembre de 2020, 09:59 AM
 */
#ifdef __cplusplus
#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include "utilities.h"
#include <cstring>

using namespace std;
#endif

class Persona {
public:
    char documentID[23];
    char documentType[3];
    char surename[23];
    char secondSurename[23];
    char firstName[23];
    char secondName[23];
    char birthday[23];
    char bloodType[23];
    char gender[23];
    char placeBirth[23];
    char status[23];
    char message[93];
    char cedulaType[2];

    void extraerNombres(char *nombres) {
        strcpy(cedulaType, "3");
        int len = getSize(nombres);
        int n = 0;
        int isLetter = 0;
        int index = 0;
        bool nfull, afull;
        for (int i = 0; i < len; i++) {
            if ((nombres[i] & 0x0ff) != 42 && nombres[i] > 0x40 && nombres[i] <= 0x5A || nombres[i] == 0x20 || nombres[i] == 0x2B || nombres[i] == 0x2D) {
                isLetter = 1;
                switch (n) {
                    case 0:
                        surename[index++] = nombres[i];
                        surename[index + 1] = '\0';
                        break;
                    case 1:
                        secondSurename[index++] = nombres[i];
                        secondSurename[index + 1] = '\0';
                        //                        afull = (index > 2) ? true : false;
                        break;
                    case 2:
                        firstName[index++] = nombres[i];
                        firstName[index + 1] = '\0';
                        break;
                    case 3:
                        secondName[index++] = nombres[i];
                        secondName[index + 1] = '\0';
                        nfull = (index > 2) ? true : false;
                        break;
                    case 4:
                        if (!nfull) {
                            cout << "falto un dato";
                            secondName[0] = '\0';
                            cout << " indice " << n;
                            i = i - 7;
                            nfull = true;
                            break;
                        }
                        // cout << "Genero\n" ;
                        gender[index++] = nombres[i];
                        gender[index + 1] = '\0';
                        break;
                    case 5:
                        bloodType[index++] = nombres[i];
                        bloodType[index + 1] = '\0';
                        break;
                    default:
                        cout << "Valor dafault no manejado\n";
                }

            } else {

                if (isLetter == 1) {
                    isLetter = 0;
                    n++;
                    index = 0;
                }
            }

        }
        strcpy(status, "OK");
        message[0] = '\0';
    }

    void extraer(char *rawData, int delta, int delta2) {
        strcpy(cedulaType, "2");
        strcpy(status, "OK");
        message[0] = '\0';
        strcpy(documentID, getTextoData(rawData, 48 + delta, 10));
        strcpy(surename, getTextoData(rawData, 58 + delta, 23));
        strcpy(secondSurename, getTextoData(rawData, 81 + delta, 23));
        strcpy(firstName, getTextoData(rawData, 104 + delta, 23));
        strcpy(secondName, getTextoData(rawData, 127 + delta, 23));
        strcpy(birthday, getTextoData(rawData, 152 + delta, 8));
        strcpy(bloodType, getTextoData(rawData, 166 + delta, 3));
        strcpy(gender, getTextoData(rawData, 151 + delta, 1));
        strcpy(placeBirth, getTextoData(rawData, 160 + delta2, 5));
    }

    void extraerNumeros(char *data) {

        char *ced = getTextoData(data, 0, 24);
        int len = getSize(ced);
        char *xx = new char[len];
        int in = 0;
        for (int i = 0; i < len; i++) {
            uint8_t ch = ced[i];
            if ((ch & 0x0ff) != 42 && ch >= 0x30 && ch <= 0x39) {
                xx[in++] = ced[i];
                xx[in + 1] = '\0';
            }
        }
        len = getSize(xx);
        strcpy(documentID, getTextoData(xx, len - 10, len));
        // strcpy(documentID,xx);
        delete[] ced;
        delete[] xx;
        ced = getTextoData(data, 25, 46);
        len = getSize(ced);
        in = 0;
        for (int i = 0; i < len; i++) {
            uint8_t ch = ced[i];
            if ((ch & 0x0ff) != 42 && ch >= 0x30 && ch <= 0x39) {
                xx[in++] = ced[i];
                xx[in + 1] = '\0';
            }
        }
        strcpy(birthday, getTextoData(xx, 1, 8));
        strcpy(placeBirth, getTextoData(xx, 9, 5));
    }

    void addError(char *error) {
        strcpy(status, "ER");
        strcpy(message, error);
        documentID[0] = '\0';
        surename[0] = '\0';
        secondSurename[0] = '\0';
        firstName[0] = '\0';
        secondName[0] = '\0';
        bloodType[0] = '\0';
        gender[0] = '\0';
        birthday[0] = '\0';
        placeBirth[0] = '\0';
        cedulaType[0] = '\0';
    }

    Persona();
    Persona(const Persona& orig);
    virtual ~Persona();
private:

};

#endif /* PERSONA_H */



