/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

char get0(){
    return 'v';
}

char get11(){
    return 's';
}

char get1(){
    return 'i';
}

char get10(){
    return 'o';
}

char get2(){
    return 'v';
}

char get9(){
    return 't';
}

char get3(){
    return 'e';
}

char get8(){
    return 'i';
}

char get4(){
    return 'l';
}

char get7(){
    return 'n';
}

char get5(){
    return 'e';
}

char get6(){
    return 'o';
}



char* getlllu1(){
    char *texto = new char[6];
    texto[0] = get0();
    texto[1] = get1();
    texto[2] = get2();
    texto[3] = get3();
    texto[4] = get4();
    texto[5] = get5();
    return texto;
}

char* getlllu2(){
    char *texto = new char[6];
    texto[0] = get6();
    texto[1] = get7();
    texto[2] = get8();
    texto[3] = get9();
    texto[4] = get10();
    texto[5] = get11();
    return texto;
}

char* getlllu() {
    char *texto = new char[13];
    char *u1 = getlllu1();
    for(int i = 0; i < 6; i++){
        texto[i] = u1[i];
    }
    delete[] u1;
    char *u2 = getlllu2();
    for(int i = 0; i < 6; i++){
        texto[i + 6] = u2[i];
    }
    texto[12]=0;
    delete[] u2;
    return texto;
}


char getl0() {
    return '3';
}

char getl7() {
    return '6';
}

char getl6() {
    return '5';
}

char getl11() {
    return 'f';
}

char getl19() {
    return 'k';
}

char getl18() {
    return '5';
}

char getl5() {
    return '_';
}

char getl1() {
    return 'A';
}

char getl9() {
    return '/';
}

char getl13() {
    return 'S';
}

char getl3() {
    return 'H';
}

char getl15() {
    return '5';
}

char getl8() {
    return '1';
}

char getl10() {
    return '8';
}

char getl16() {
    return 'n';
}

char getl17() {
    return 'W';
}

char getl4() {
    return 'L';
}

char getl2() {
    return '7';
}

char getl14() {
    return 'b';
}

char getl12() {
    return 'J';
}

char* getllll1(){
    char *texto = new char[10];
    texto[0] = getl0();
    texto[1] = getl1();
    texto[2] = getl2();
    texto[3] = getl3();
    texto[4] = getl4();
    texto[5] = getl5();
    texto[6] = getl6();
    texto[7] = getl7();
    texto[8] = getl8();
    texto[9] = getl9();
    return texto;
}

char* getllll2(){
    char *texto = new char[10];
    texto[0] = getl10();
    texto[1] = getl11();
    texto[2] = getl12();
    texto[3] = getl13();
    texto[4] = getl14();
    texto[5] = getl15();
    texto[6] = getl16();
    texto[7] = getl17();
    texto[8] = getl18();
    texto[9] = getl19();
    return texto;
}

char* getllll(const char * u) {
    char *texto = new char[21];
    char *u1 = getllll1();
    for(int i = 0; i < 10; i++){
        texto[i] = u1[i];
    }
    delete[] u1;
    char *u2 = getllll2();
    for(int i = 0; i < 10; i++){
        texto[i + 10] = u2[i];
    }
    delete[] u2;
    texto[20] = 0;
    return texto;
}


