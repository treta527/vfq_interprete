/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "utilities.h"
#include "persona.h"
#include "convert.h"

char *parse(char *rawData) {
    char *output = new char[1024];
    //    cout << "\n\nEntrada:\n\n" << rawData;
    int len = getSize(rawData);
    Persona p = getCedulaColombianaData(rawData, len);

    strcat(output, "{\"resultado\": \"OK\",\"documentID\": \"");
    strcat(output, p.documentID);
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
    strcat(output, "\"}");
    int size = getSize(output);
    int ind = 0;
    char *response = new char[1024] {
        0
    };
    for (int i = 0; i < size; i++) {
        uint8_t ch = output[i];
        if (ch < 0x80) {
//            cout << output[i] << " ";
            response[ind++] = output[i];
        }
    }
    return response;
}