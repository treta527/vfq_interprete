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
        string msg = base64_decode(_arr);
        int n = msg.length();
        char char_array[n + 1];
        strcpy(char_array, msg.c_str());
        char *output = getCedulaColombianaData(char_array, n);
        int l = getSize34(output);
       char *texto = new char[l] {
        0
    };
        int x=0;
        for (int i = 0; i < l; i++) {
            //aqui pretendo remplazar la basura
            if (int(output[i]) == -17
                    || int(output[i]) == -65
                    || int(output[i]) == -67
                    || int(output[i]) == -17
                    || int(output[i]) == -65
                    || int(output[i]) == -67
                    || int(output[i]) == -17
                    || int(output[i]) == -65
                    || int(output[i]) == -67
                    || int(output[i]) == -17
                    || int(output[i]) == -65
                    || int(output[i]) == -67
                    || int(output[i]) == -17
                    || int(output[i]) == -65
                    || int(output[i]) == -67) {
            } else {
                texto[x++]=output[i];
            }

        }
        return texto;
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