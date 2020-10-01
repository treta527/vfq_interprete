/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "utilities.h"
#include "persona.h"
#include "convert.h"

char *parse(char *rawData) {
    Persona p;
    char *output = new char[1024];
    try {
        //    cout << "\n\nEntrada:\n\n" << rawData;
        int len = getSize(rawData);
        p = getCedulaColombianaData(rawData, len);
    } catch (...) {
        char e[]="Algo pasó ... :(";
        p.addError(e);
    }

    strcat(output, "{\"resultado\": \"");
    strcat(output, p.status);
    strcat(output, "\",\"documentID\": \"");
    strcat(output, p.documentID);
    strcat(output, "\",\"documentType\": \"");
    strcat(output, p.documentType);
    strcat(output, "\",\"surename\": \"");
    strcat(output, p.surename);
    strcat(output, "\", \"secondSurename\": \"");
    strcat(output, p.secondSurename);
    strcat(output, "\", \"firstName\": \"");
    strcat(output, p.firstName);
    strcat(output, "\", \"secondName\": \"");
    strcat(output, p.secondName);
    strcat(output, "\", \"birthday\": \"");
    strcat(output, p.birthday);
    strcat(output, "\", \"bloodType\": \"");
    strcat(output, p.bloodType);
    strcat(output, "\", \"gender\": \"");
    strcat(output, p.gender);
    strcat(output, "\", \"placeBirth\": \"");
    strcat(output, p.placeBirth);
    strcat(output, "\", \"message\": \"");
    strcat(output, p.message);
    strcat(output, "\", \"cedulaType\": \"");
    strcat(output, p.cedulaType);
    strcat(output, "\"}");
    //    cout <<"Salida json: " << output << "\n";
    int size = getSize(output);
    int ind = 0;
    char *response = new char[1024] {
        0
    };
    for (int i = 0; i < size; i++) {
        uint8_t ch = output[i];
        if (ch == 0x3A || ch >= 0x41 && ch <= 0x5A || ch >= 0x61 && ch <= 0x7A
                || ch == 0x7B || ch == 0x7D || ch == 0x22 || ch == 0x2C
                || ch == 0x20 || ch == 0x2B || ch == 0x2D || ch >= 0x30 && ch <= 0x39) {
            response[ind++] = output[i];
        }
    }
    return response;
}