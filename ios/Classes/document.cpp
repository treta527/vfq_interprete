/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "cstring"
#include "lll.h"
#include "document.h"
#include <vector>
#include <iostream>
#include "convert.h"
#include "base64.h"

using namespace std;

size_t getSize34(std::string str) {
    return str.size();
}

char *parse(int size, char *_arr, char *user, char *license) {
    char *response = new char[1024] {
        0
    };
    if (lll(user, license)) {
    int p=0;
        char *texto = new char[size] {
            0
        };
        int ind = 0;
        for (int i = 0; i < size; i++) {
            uint8_t ch = _arr[i];
            if (ch < 0x80) {
             if ((ch & 0xff) == 80) {
                                p=ind;
                            }
//                cout << _arr[i] << " ";
                texto[ind++] = _arr[i];
            } else {
              //  if ((ch & 0xff) == 175) {
//                    cout << _arr[i] << " ";
                   // texto[ind++] = 32;
                    texto[ind++] = _arr[i];
                //}
            }
        }

        char *output = getCedulaColombianaData(texto, size,p);
        size = getSize34(output);
        ind = 0;
         for (int i = 0; i < size; i++) {
             uint8_t ch = output[i];
             if (ch < 0x80) {
//                cout << output[i] << " ";
                response[ind++]=output[i];
             }
        }
        return response;
    } else {
        strcpy(response, "{ \"resultado\" = \"ERROR DE AUTENTICACIÓN\" }");
        return response;
    }
}

int lll(const char *user, const char *license) {
    char *userLocal = getlllu();
    if (strcmp(user, userLocal) == 0) {
        if (strcmp(license, getllll(user)) == 0) {
            return true;
        }
    }
    return false;

}