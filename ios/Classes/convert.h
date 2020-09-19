/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   converter.h
 * Author: leonardo
 *
 * Created on 11 de septiembre de 2020, 11:28 AM
 */

#ifndef CONVERTER_H
#define CONVERTER_H

const int CEDULA_TIPO_02 = 2;
const int CEDULA_TIPO_03 = 3;
const int TARJETA_IDENTIDAD_TIPO_I3 = 4;

char* getCedulaColombianaData(char * rawDataOriginal, int length);

char* getTextoData(const char * datos, int i, int j);

char* decode(char* arr, char* response, int length);

int getTipoCedula(const char* rawData, int length);

#endif /* CONVERTER_H */

