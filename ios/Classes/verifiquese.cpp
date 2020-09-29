#include <cstdlib>
#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <string>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include "verifiquese.h"

#include "document.h"
using namespace std;

extern "C" __attribute__((visibility("default"))) __attribute__((used))
int32_t
native_add(int32_t x, int32_t y)
{
  return x + y;
}

extern "C" __attribute__((visibility("default"))) __attribute__((used)) char *convert(char *size, char *arr_, char *user, char *license)
{
try{
  int len = atoi(size);

  //return parse(len, arr_, user, license);
  return parse(arr_);
}catch(...){
char *response = new char[50];
 strcpy(response, "{ \"resultado\" = \"ERROR\" }");
        return response;
}
}