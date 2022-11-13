//
//  main.c
//  un11
//
//  Created by Fausto Saporito on 29/10/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define check(x) if((x) == NULL){printf("Alloc error %s\n",#x);exit(100);}

char* rA;
char* rX;
char* rF;
char* rL;

char** rW;
char** rZ;

char** rO;
char** rI;

char* CC;
char* SR;
char* CR;

char* half;
char* halfi;
char* one;

char** mem;

int hlt = 0;
int ovf = 0;

char umap[] = {
//   0  1  2  3  4  5  6  7  8  9
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 1
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 2
     0, 0,47, 0,32,30,46,62,15,14, // 3
    16,36,44,52,17, 3,19,53, 4, 5, // 4
     6, 7, 8, 9,10,11,12,13,51,20, // 5
     0,63, 0,48,32,21,22,23,24,25, // 6
    26,27,28,29,37,38,39,40,41,42, // 7
    43,44,45,54,55,56,57,58,59,60, // 8
    61, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 9
     0, 0, 0, 0, 0, 1, 0, 0, 0, 0, // 10
     0, 0, 0, 0,16, 0,31, 0, 0, 0, // 11
     0, 0, 0, 0,35, 0, 0, 0        // 12
};

char fromchr[64] = { 0, };

FILE* t1;
FILE* t2;
FILE* t3;
FILE* t4;
FILE* t5;
FILE* t6;
FILE* t7;
FILE* t8;
FILE* t9;
FILE* t10;

void zero(char* a)
{
    for(int _i=0;_i<12;_i++)
        a[_i] = '0';
}

FILE* tn(char c)
{
    switch(c) {
        case '-':
            return t10;
            break;
        case '1':
            return t1;
            break;
        case '2':
            return t2;
            break;
        case '3':
            return t3;
            break;
        case '4':
            return t4;
            break;
        case '5':
            return t5;
            break;
        case '6':
            return t6;
            break;
        case '7':
            return t7;
            break;
        case '8':
            return t8;
            break;
        case '9':
            return t9;
            break;
        default:
            return NULL;
            break;
    }
}

#define SG(x) a[0]=(x); break

void neg(char* a)
{
    char d = a[0];
    switch(d) {
        case '0':
            SG('-');
        case '-':
            SG('0');
        case 'i':
            SG(' ');
        case ' ':
            SG('i');
        case 'r':
            SG(',');
        case ',':
            SG('r');
        case 't':
            SG('"');
        case '"':
            SG('t');
        case '.':
            SG(';');
        case ';':
            SG('.');
        case '|':
            SG(')');
        case ')':
            SG('|');
        case ':':
            SG('+');
        case '+':
            SG(':');
        case 'A':
            SG('B');
        case 'B':
            SG('A');
        case 'J':
            SG('K');
        case 'K':
            SG('J');
        case '/':
            SG('S');
        case 'S':
            SG('/');
        case 'C':
            SG('D');
        case 'D':
            SG('C');
        case 'L':
            SG('M');
        case 'M':
            SG('L');
        case 'T':
            SG('U');
        case 'U':
            SG('T');
        case 'E':
            SG('F');
        case 'F':
            SG('E');
        case 'N':
            SG('O');
        case 'O':
            SG('N');
        case 'V':
            SG('W');
        case 'W':
            SG('V');
        case 'G':
            SG('H');
        case 'H':
            SG('G');
        case 'P':
            SG('Q');
        case 'Q':
            SG('P');
        case 'X':
            SG('Y');
        case 'Y':
            SG('X');
        case 'I':
            SG('#');
        case '#':
            SG('I');
        case 'R':
            SG('$');
        case '$':
            SG('R');
        case 'Z':
            SG('%');
        case '%':
            SG('Z');
        case '&':
            SG('(');
        case '(':
            SG('&');
        case '*':
            SG('?');
        case '?':
            SG('*');
        default:
            break;
    }
}

// compare magnitude
// returns 1 if a > b
// returns -1 if a < b
// returns 0 if a = b
int cmp(char* a, char* b)
{
    if ((a[0] == '0') && (b[0] == '-')) {
        return 1;
    } else if ((a[0] == '-') && (b[0] == '0')) {
        return -1;
    } else {
        for (int i=0;i<12;i++) {
            if (umap[a[i]] > umap[b[i]]) {
                return 1;
            } else if (umap[a[i]] < umap[b[i]]) {
                return -1;
            }
        }
    }
    return 0;
}

// including sign bit
void shr(char* a)
{
    for(int i=11;i>=1;i--)
        a[i] = a[i-1];
    a[0] = '0';
}

// including sign bit
void shl(char* a)
{
    for(int i=0;i<11;i++)
        a[i] = a[i+1];
    a[11] = '0';
}

// excluding sign bit
void sshr(char* a)
{
    for(int i=11;i>=2;i--)
        a[i] = a[i-1];
    a[1] = '0';
}

// excluding sign bit
void sshl(char* a)
{
    for(int i=1;i<11;i++)
        a[i] = a[i+1];
    a[11] = '0';
}

// shift left extend
// move rA digits to the corresponding rX digits
void shle(int j)
{
    rX[j] = rA[11];
    for(int i=11;i>=1;i--)
        rA[i] = rA[i-1];
}

void set(char* a, long v)
{
    char s = (v < 0) ? '-' : '0';
    
    for(int i=11;i>=0;i--) {
        a[i] = (v % 10) + '0';
        v /= 10;
    }
    if (a[0] != '0') {
        shr(a);
        a[0] = s;
    }
}

void cpy(char* d, char* s)
{
    for(int i=0;i<12;i++)
        d[i] = s[i];
}

void cpl(char* a)
{
    int t = 0;
    
    if (a[11] == '0') {
        t = 1;
    } else {
        t = 10 - (a[11] - '0');
        a[11] = t + '0';
        t = 0;
    }
    
    for(int i=10;i>=0;i--) {
        if (a[i] == '0') {
            t = t + (9 - (a[i] - '0'));
            a[i] = t + '0';
            t = 1;
        } else {
            t = t + (9 - (a[i] - '0'));
            a[i] = t + '0';
            t = 0;
        }
    }
}

void init(void)
{
    rA = (char*)calloc(12, sizeof(char)); check(rA);
    rX = (char*)calloc(12, sizeof(char)); check(rX);
    rF = (char*)calloc(12, sizeof(char)); check(rF);
    rL = (char*)calloc(12, sizeof(char)); check(rL);
    
    rW = (char**)calloc(10, sizeof(char*)); check(rW);
    rZ = (char**)calloc(60, sizeof(char*)); check(rZ);
    rO = (char**)calloc(60, sizeof(char*)); check(rO);
    rI = (char**)calloc(60, sizeof(char*)); check(rI);
    
    CC = (char*)calloc(12, sizeof(char)); check(CC);
    CR = (char*)calloc(12, sizeof(char)); check(CR);
    SR = (char*)calloc(6, sizeof(char)); check(SR);
    
    one = (char*)calloc(12, sizeof(char)); check(one);
    half = (char*)calloc(12, sizeof(char)); check(half);
    halfi = (char*)calloc(12, sizeof(char)); check(halfi);
    
    mem = (char**)calloc(10000, sizeof(char*)); check(mem);

    for(int i=0;i<10000;i++) {
        mem[i] = (char*)calloc(12,sizeof(char));
        zero(mem[i]);
    }
    
    for(int i=0;i<9;i++) {
        rW[i] = (char*)calloc(12,sizeof(char));
        zero(rW[i]);
    }
    
    for(int i=0;i<60;i++) {
        rZ[i] = (char*)calloc(12,sizeof(char));
        rO[i] = (char*)calloc(12,sizeof(char));
        rI[i] = (char*)calloc(12,sizeof(char));
        zero(rZ[i]); zero(rO[i]);
        zero(rI[i]);
    }
    
    zero(rA); zero(rX);
    zero(rF); zero(rL);
    zero(one); zero(half);
    zero(halfi);
    
    zero(CC); zero(CR);
    
    one[11] = '1';
    half[11] = '5';
    halfi[1] = '5';
    
    t1=fopen("tape1.tp","r+");
    t2=fopen("tape2.tp","r+");
    t3=fopen("tape3.tp","r+");
    t4=fopen("tape4.tp","r+");
    t5=fopen("tape5.tp","r+");
    t6=fopen("tape6.tp","r+");
    t7=fopen("tape7.tp","r+");
    t8=fopen("tape8.tp","r+");
    t9=fopen("tape9.tp","r+");
    t10=fopen("tape-.tp","r+");
    
    fromchr[0] = 'i';
    fromchr[020] = '\r';
    fromchr[040] = '\t';
    fromchr[1] = ' ';
    fromchr[021] = ',';
    fromchr[041] = '"';
    fromchr[2] = '-';
    fromchr[022] = '.';
    fromchr[042] = '|';
    fromchr[062] = ':';
    fromchr[3] = '0';
    fromchr[023] = ';';
    fromchr[043] = ')';
    fromchr[063] = '+';
    fromchr[4] = '1';
    fromchr[024] = 'A';
    fromchr[044] = 'J';
    fromchr[064] = '/';
    fromchr[5] = '2';
    fromchr[025] = 'B';
    fromchr[045] = 'K';
    fromchr[065] = 'S';
    fromchr[6] = '3';
    fromchr[026] = 'C';
    fromchr[046] = 'L';
    fromchr[066] = 'T';
    fromchr[7] = '4';
    fromchr[027] = 'D';
    fromchr[047] = 'M';
    fromchr[067] = 'U';
    fromchr[010] = '5';
    fromchr[030] = 'E';
    fromchr[050] = 'N';
    fromchr[070] = 'V';
    fromchr[011] = '6';
    fromchr[031] = 'F';
    fromchr[051] = 'O';
    fromchr[071] = 'W';
    fromchr[012] = '7';
    fromchr[032] = 'G';
    fromchr[052] = 'P';
    fromchr[072] = 'X';
    fromchr[013] = '8';
    fromchr[033] = 'H';
    fromchr[053] = 'Q';
    fromchr[073] = 'Y';
    fromchr[014] = '9';
    fromchr[034] = 'I';
    fromchr[054] = 'R';
    fromchr[074] = 'Z';
    fromchr[015] = 39;
    fromchr[035] = '#';
    fromchr[055] = '$';
    fromchr[075] = '%';
    fromchr[016] = '&';
    fromchr[036] = '^';
    fromchr[056] = '*';
    fromchr[076] = '=';
    fromchr[017] = '(';
    fromchr[037] = '@';
    fromchr[057] = '?';
    
}

int isN(char a){
    switch(a) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '&':
        case 39:
        case '(':
            return 1;
            break;
        default:
            return 0;
    }
}

int tochr(char c)
{
    switch(c) {
        case 'i':
            return 0;
            break;
        case '\r':
            return 020;
            break;
        case '\t':
            return 040;
            break;
        case ' ':
            return 1;
            break;
        case ',':
            return 021;
            break;
        case '"':
            return 041;
            break;
        case '-':
            return 2;
            break;
        case '.':
            return 022;
            break;
        case '|':
            return 042;
            break;
        case ':':
            return 062;
            break;
        case '0':
            return 3;
            break;
        case ';':
            return 023;
            break;
        case ')':
            return 043;
            break;
        case '+':
            return 063;
            break;
        case '1':
            return 4;
            break;
        case 'A':
            return 024;
            break;
        case 'J':
            return 044;
            break;
        case '/':
            return 064;
            break;
        case '2':
            return 5;
            break;
        case 'B':
            return 025;
            break;
        case 'K':
            return 045;
            break;
        case 'S':
            return 065;
            break;
        case '3':
            return 6;
            break;
        case 'C':
            return 026;
            break;
        case 'L':
            return 046;
            break;
        case 'T':
            return 066;
            break;
        case '4':
            return 7;
            break;
        case 'D':
            return 027;
            break;
        case 'M':
            return 047;
            break;
        case 'U':
            return 067;
            break;
        case '5':
            return 010;
            break;
        case 'E':
            return 030;
            break;
        case 'N':
            return 050;
            break;
        case 'V':
            return 070;
            break;
        case '6':
            return 011;
            break;
        case 'F':
            return 031;
            break;
        case 'O':
            return 051;
            break;
        case 'W':
            return 071;
            break;
        case '7':
            return 012;
            break;
        case 'G':
            return 032;
            break;
        case 'P':
            return 052;
            break;
        case 'X':
            return 072;
            break;
        case '8':
            return 013;
            break;
        case 'H':
            return 033;
            break;
        case 'Q':
            return 053;
            break;
        case 'Y':
            return 073;
            break;
        case '9':
            return 014;
            break;
        case 'I':
            return 034;
            break;
        case 'R':
            return 054;
            break;
        case 'Z':
            return 074;
            break;
        case 39:
            return 015;
            break;
        case '#':
            return 035;
            break;
        case '$':
            return 055;
            break;
        case '%':
            return 075;
            break;
        case '&':
            return 016;
            break;
        case '^':
            return 036;
            break;
        case '*':
            return 056;
            break;
        case '=':
            return 076;
            break;
        case '(':
            return 017;
            break;
        case '@':
            return 037;
            break;
        case '?':
            return 057;
            break;
        default:
            break;
    }
    return 0;
}

int isC(char a)
{
    if (!isN(a) && (a != '0') && (a != '-'))
        return 1;
    return 0;
}

int value(char a){
    switch(a) {
        case '0':
        case ';':
        case ')':
        case '+':
            return 0;
            break;
        case '1':
        case 'A':
        case 'J':
        case '/':
            return 1;
            break;
        case '2':
        case 'B':
        case 'K':
        case 'S':
            return 2;
            break;
        case '3':
        case 'C':
        case 'L':
        case 'T':
            return 3;
            break;
        case '4':
        case 'D':
        case 'M':
        case 'U':
            return 4;
            break;
        case '5':
        case 'E':
        case 'N':
        case 'V':
            return 5;
            break;
        case '6':
        case 'F':
        case 'O':
        case 'W':
            return 6;
            break;
        case '7':
        case 'G':
        case 'P':
        case 'X':
            return 7;
            break;
        case '8':
        case 'H':
        case 'Q':
        case 'Y':
            return 8;
            break;
        case '9':
        case 'I':
        case 'R':
        case 'Z':
            return 9;
            break;
        case '-':
        case '.':
        case '|':
        case ':':
            return -1;
            break;
        case '&':
        case '^':
        case '*':
        case '=':
            return 11;
            break;
        case 39:
        case '#':
        case '$':
        case '%':
            return 10;
            break;
        case '(':
        case '@':
        case '?':
            return 12;
            break;
        default:
            return 0;
    }
}

void addAX(void)
{
    int t = 0;
    int c = 0;
    
    hlt = 0;
    
    for(int i=11;i>=0;i--) {
        t = value(rA[i]) + value(rX[i]) + c;
        if (t > 9) {
            t -= 10;
            c = 1;
        } else if (t == -1 ){
            t = -3;
        } else {
            c = 0;
        }
        rA[i] = t + '0';
        if (isN(rA[i]) && isN(rX[i])) {
            // nothing
        } else if (isN(rA[i]) && isC(rX[i])) {
            rA[i] = rX[i];
        } else if (isN(rA[i]) && (rX[i] == '0')) {
            // nothing
        } else if (isN(rA[i]) && (rX[i] == '-')) {
            rA[i] = rA[i] - 1;
        } else if (isC(rA[i]) && isN(rX[i])) {
            // nothing
        } else if (isC(rA[i]) && isC(rX[i])) {
            hlt = 2*i;
        } else if (isC(rA[i]) && (rX[i] == '0')) {
            // nothing
        } else if (isC(rA[i]) && (rX[i] == '-')) {
            // nothing
        } else if ((rA[i] == '0') && isN(rX[i])) {
            //rA[i] = rX[i];
        } else if ((rA[i] == '0') && isC(rX[i])) {
            rA[i] = rX[i];
        } else if ((rA[i] == '0') && (rX[i] == '0')) {
            // nothing
        } else if ((rA[i] == '0') && (rX[i] == '-')) {
            rA[i] = '-';
        } else if ((rA[i] == '-') && isN(rX[i])) {
            //rA[i] -= 1;
        } else if ((rA[i] == '-') && isC(rX[i])) {
            rA[i] = rX[i];
        } else if ((rA[i] == '-') && (rX[i] == '0')) {
            // nothing
        } else if ((rA[i] == '-') && (rX[i] == '-')) {
            rA[i] = ' ';
        }
    }
    ovf = c;
}

void addAL(void)
{
    int t = 0;
    int c = 0;
    
    for(int i=11;i>=0;i--) {
        t = value(rA[i]) + value(rL[i]) + c;
        if (t > 9) {
            t -= 10;
            c = 1;
        } else if (t == -1) {
            t = -3;
        } else {
            c = 0;
        }
        rA[i] = t + '0';
        if (isN(rA[i]) && isN(rL[i])) {
            // nothing
        } else if (isN(rA[i]) && isC(rL[i])) {
            rA[i] = rL[i];
        } else if (isN(rA[i]) && (rL[i] == '0')) {
            // nothing
        } else if (isN(rA[i]) && (rL[i] == '-')) {
            rA[i] = rA[i] - 1;
        } else if (isC(rA[i]) && isN(rL[i])) {
            // nothing
        } else if (isC(rA[i]) && isC(rL[i])) {
            hlt = 2;
        } else if (isC(rA[i]) && (rL[i] == '0')) {
            // nothing
        } else if (isC(rA[i]) && (rL[i] == '-')) {
            // nothing
        } else if ((rA[i] == '0') && isN(rL[i])) {
            //rA[i] = rL[i];
        } else if ((rA[i] == '0') && isC(rL[i])) {
            rA[i] = rL[i];
        } else if ((rA[i] == '0') && (rL[i] == '0')) {
            // nothing
        } else if ((rA[i] == '0') && (rL[i] == '-')) {
            rA[i] = '-';
        } else if ((rA[i] == '-') && isN(rL[i])) {
            //rA[i] -= 1;
        } else if ((rA[i] == '-') && isC(rL[i])) {
            rA[i] = rX[i];
        } else if ((rA[i] == '-') && (rL[i] == '0')) {
            // nothing
        } else if ((rA[i] == '-') && (rL[i] == '-')) {
            rA[i] = ' ';
        }
    }
    ovf = c;
}

void addAF(void)
{
    int t = 0;
    int c = 0;
    
    for(int i=11;i>=0;i--) {
        t = value(rA[i]) + value(rF[i]) + c;
        if (t > 9) {
            t -= 10;
            c = 1;
        } else if (t == -1) {
            t = -3;
        } else {
            c = 0;
        }
        rA[i] = t + '0';
        if (isN(rA[i]) && isN(rF[i])) {
            // nothing
        } else if (isN(rA[i]) && isC(rF[i])) {
            rA[i] = rF[i];
        } else if (isN(rA[i]) && (rF[i] == '0')) {
            // nothing
        } else if (isN(rA[i]) && (rF[i] == '-')) {
            rA[i] = rA[i] - 1;
        } else if (isC(rA[i]) && isN(rF[i])) {
            // nothing
        } else if (isC(rA[i]) && isC(rF[i])) {
            hlt = 2;
        } else if (isC(rA[i]) && (rF[i] == '0')) {
            // nothing
        } else if (isC(rA[i]) && (rF[i] == '-')) {
            // nothing
        } else if ((rA[i] == '0') && isN(rF[i])) {
            //rA[i] = rF[i];
        } else if ((rA[i] == '0') && isC(rF[i])) {
            rA[i] = rF[i];
        } else if ((rA[i] == '0') && (rF[i] == '0')) {
            // nothing
        } else if ((rA[i] == '0') && (rF[i] == '-')) {
            //rA[i] = '-';
        } else if ((rA[i] == '-') && isN(rF[i])) {
            //rA[i] -= 1;
        } else if ((rA[i] == '-') && isC(rF[i])) {
            rA[i] = rF[i];
        } else if ((rA[i] == '-') && (rF[i] == '0')) {
            // nothing
        } else if ((rA[i] == '-') && (rF[i] == '-')) {
            rA[i] = ' ';
        }
    }
    
    ovf = c;
}

void addn(char* n)
{
    int t = 0;
    int c = 0;
    
    for(int i=11;i>=0;i--) {
        t = value(rA[i]) + value(n[i]) + c;
        if (t > 9) {
            t -= 10;
            c = 1;
        } else if (t == -1) {
            t = -3;
        } else {
            c = 0;
        }
        rA[i] = t + '0';
        if (isN(rA[i]) && isN(n[i])) {
            //nothing
        } else if (isN(rA[i]) && isC(n[i])) {
            rA[i] = n[i];
        } else if (isN(rA[i]) && (n[i] == '0')) {
            // nothing
        } else if (isN(rA[i]) && (n[i] == '-')) {
            rA[i] = rA[i] - 1;
        } else if (isC(rA[i]) && isN(n[i])) {
            // nothing
        } else if (isC(rA[i]) && isC(n[i])) {
            hlt = 2;
        } else if (isC(rA[i]) && (n[i] == '0')) {
            // nothing
        } else if (isC(rA[i]) && (n[i] == '-')) {
            // nothing
        } else if ((rA[i] == '0') && isN(n[i])) {
            //rA[i] = n[i];
        } else if ((rA[i] == '0') && isC(n[i])) {
            rA[i] = n[i];
        } else if ((rA[i] == '0') && (n[i] == '0')) {
            // nothing
        } else if ((rA[i] == '0') && (n[i] == '-')) {
            //rA[i] = '-';
        } else if ((rA[i] == '-') && isN(n[i])) {
            //rA[i] -= 1;
        } else if ((rA[i] == '-') && isC(n[i])) {
            rA[i] = n[i];
        } else if ((rA[i] == '-') && (n[i] == '0')) {
            // nothing
        } else if ((rA[i] == '-') && (n[i] == '-')) {
            rA[i] = ' ';
        }
    }
    ovf = c;
}

void addnn(char* d, char* n)
{
    int t = 0;
    int c = 0;
    
    for(int i=11;i>=0;i--) {
        t = value(d[i]) + value(n[i]) + c;
        if (t > 9) {
            t -= 10;
            c = 1;
        } else {
            c = 0;
        }
        d[i] = t + '0';
        if (isN(d[i]) && isN(n[i])) {
            // nothing
        } else if (isN(d[i]) && isC(n[i])) {
            d[i] = n[i];
        } else if (isN(d[i]) && (n[i] == '0')) {
            // nothing
        } else if (isN(d[i]) && (n[i] == '-')) {
            d[i] = d[i] - 1;
        } else if (isC(d[i]) && isN(n[i])) {
            // nothing
        } else if (isC(d[i]) && isC(n[i])) {
            hlt = 2;
        } else if (isC(d[i]) && (n[i] == '0')) {
            // nothing
        } else if (isC(d[i]) && (n[i] == '-')) {
            // nothing
        } else if ((d[i] == '0') && isN(n[i])) {
            //d[i] = n[i];
        } else if ((d[i] == '0') && isC(n[i])) {
            d[i] = n[i];
        } else if ((d[i] == '0') && (n[i] == '0')) {
            // nothing
        } else if ((d[i] == '0') && (n[i] == '-')) {
            // d[i] = '-';
        } else if ((d[i] == '-') && isN(n[i])) {
            //d[i] -= 1;
        } else if ((d[i] == '-') && isC(n[i])) {
            d[i] = n[i];
        } else if ((d[i] == '-') && (n[i] == '0')) {
            // nothing
        } else if ((d[i] == '-') && (n[i] == '-')) {
            d[i] = ' ';
        }
    }
}

void subAX(void)
{
    int t = 0;
    int c = 0;
    
    for(int i=11;i>=0;i--) {
        t = value(rA[i]) - value(rX[i]) - c;
        if (t < 0) {
            t = 10 - abs(t);
            c = 1;
        } else {
            c = 0;
        }
        rA[i] = t + '0';
        if (isN(rA[i]) && isN(rX[i])) {
            // nothing
        } else if (isN(rA[i]) && isC(rX[i])) {
            rA[i] = rX[i];
        } else if (isN(rA[i]) && (rX[i] == '0')) {
            // nothing
        } else if (isN(rA[i]) && (rX[i] == '-')) {
            rA[i] = rA[i] - 1;
        } else if (isC(rA[i]) && isN(rX[i])) {
            // nothing
        } else if (isC(rA[i]) && isC(rX[i])) {
            hlt = 2;
        } else if (isC(rA[i]) && (rX[i] == '0')) {
            // nothing
        } else if (isC(rA[i]) && (rX[i] == '-')) {
            // nothing
        } else if ((rA[i] == '0') && isN(rX[i])) {
            //rA[i] = rX[i];
        } else if ((rA[i] == '0') && isC(rX[i])) {
            rA[i] = rX[i];
        } else if ((rA[i] == '0') && (rX[i] == '0')) {
            // nothing
        } else if ((rA[i] == '0') && (rX[i] == '-')) {
            rA[i] = '-';
        } else if ((rA[i] == '-') && isN(rX[i])) {
            //rA[i] -= 1;
        } else if ((rA[i] == '-') && isC(rX[i])) {
            rA[i] = rX[i];
        } else if ((rA[i] == '-') && (rX[i] == '0')) {
            // nothing
        } else if ((rA[i] == '-') && (rX[i] == '-')) {
            rA[i] = ' ';
        }
    }
}

void subAL(void)
{
    int t = 0;
    int c = 0;
    
    for(int i=11;i>=0;i--) {
        t = value(rA[i]) - value(rL[i]) - c;
        if (t < 0) {
            t = 10 - abs(t);
            c = 1;
        } else {
            c = 0;
        }
        rA[i] = t + '0';
        if (isN(rA[i]) && isN(rL[i])) {
            // nothing
        } else if (isN(rA[i]) && isC(rL[i])) {
            rA[i] = rL[i];
        } else if (isN(rA[i]) && (rL[i] == '0')) {
            // nothing
        } else if (isN(rA[i]) && (rL[i] == '-')) {
            rA[i] = rA[i] - 1;
        } else if (isC(rA[i]) && isN(rL[i])) {
            // nothing
        } else if (isC(rA[i]) && isC(rL[i])) {
            hlt = 2;
        } else if (isC(rA[i]) && (rL[i] == '0')) {
            // nothing
        } else if (isC(rA[i]) && (rL[i] == '-')) {
            // nothing
        } else if ((rA[i] == '0') && isN(rL[i])) {
            //rA[i] = rL[i];
        } else if ((rA[i] == '0') && isC(rL[i])) {
            rA[i] = rL[i];
        } else if ((rA[i] == '0') && (rL[i] == '0')) {
            // nothing
        } else if ((rA[i] == '0') && (rL[i] == '-')) {
            rA[i] = '-';
        } else if ((rA[i] == '-') && isN(rL[i])) {
            //rA[i] -= 1;
        } else if ((rA[i] == '-') && isC(rL[i])) {
            rA[i] = rL[i];
        } else if ((rA[i] == '-') && (rL[i] == '0')) {
            // nothing
        } else if ((rA[i] == '-') && (rL[i] == '-')) {
            rA[i] = ' ';
        }
    }
}

void roundd(void)
{
    addnn(rX,halfi);
    if (rX[0] == '1')
        addn(one);
}

void mul(char sgn)
{
    char mqc;
    
    zero(rA);
    if ((rL[0] == '&') || (rL[0] == 39) || (rL[0] == '(')) {
        ovf = 1;
        // overflow
    }
    addAL(); addAL(); addAL();
    cpy(rF,rA);
    zero(rA);
    
    for(int i=11;i>=1;i--) {
        mqc = rX[i];
        while (mqc != '0') {
            if (mqc < '3') {
                addAL();
                mqc--;
            } else {
                addAF();
                mqc -= 3;
            }
        }
        shle(i);
    }
    
    rA[0] = sgn;
    rX[0] = sgn;
}

void divv(char sgn)
{
    int mqc = 0;
    zero(rX);
    
    for (int i=0;i<11;i=i+2) {
        mqc = 0;
        shl(rA);shl(rX);
        subAL();
        while(rA[0] != '9') {
            subAL();
            mqc++;
        }
        rX[11] = (mqc) + '0';
        shl(rX); shl(rA);
        mqc = -9;
        addAL();
        while(rA[0] == '9') {
            addAL();
            mqc++;
        }
        rX[11] = abs(mqc) + '0';
    }
    cpy(rA,rX);
    addn(half);
    shr(rA);shr(rX);
    rA[0] = sgn;
    rX[0] = sgn;
}

void D0(void)
{
    int s = 0;
    int Lneg = 0;
    
    if (isN(rX[0]) && isN(rL[0])) {
        hlt = 3;
    } else if (isN(rX[0]) && isC(rL[0])) {
        hlt = 4;
    } else if (isN(rX[0]) && (rL[0] == '0')) {
        s = rX[0];
    } else if (isN(rX[0]) && (rL[0] == '-')) {
        s = rX[0];
    } else if (isC(rX[0]) && isN(rL[0])) {
        hlt = 5;
    } else if (isC(rX[0]) && isC(rL[0])) {
        hlt = 6;
    } else if (isC(rX[0]) && (rL[0] == '0')) {
        s = rX[0];
    } else if (isC(rX[0]) && (rL[0] == '-')) {
        s = rX[0];
    } else if ((rX[0] == '0') && isN(rL[0])) {
        s = rL[0];
    } else if ((rX[0] == '0') && isC(rL[0])) {
        s = rL[0];
    } else if ((rX[0] == '0') && (rL[0] == '0')) {
        s = '0';
    } else if ((rX[0] == '0') && (rL[0] == '-')) {
        s = '-';
    } else if ((rX[0] == '-') && isN(rL[0])) {
        s = rL[0];
    } else if ((rX[0] == '-') && isC(rL[0])) {
        s = rL[0];
    } else if ((rX[0] == '-') && (rL[0] == '0')) {
        s = '-';
    } else if ((rX[0] == '-') && (rL[0] == '-')) {
        s = '-';
    }
    
    /*if (rA[0] == rL[0]) {
        // always positive
        s = '0';
    } else {
        // result is always negative
        s = '-';
    }
    rA[0] = '0';*/
    
    if (rL[0] == '-') {
        Lneg = 1;
        rL[0] = '0';
    }
    divv(s);
    if (Lneg == 1)
        rL[0] = '-';
}

void P0(void)
{
    int s = 0;
    int Lneg = 0;
    
    if (isN(rX[0]) && isN(rL[0])) {
        hlt = 3;
    } else if (isN(rX[0]) && isC(rL[0])) {
        hlt = 4;
    } else if (isN(rX[0]) && (rL[0] == '0')) {
        s = rX[0];
    } else if (isN(rX[0]) && (rL[0] == '-')) {
        s = rX[0];
    } else if (isC(rX[0]) && isN(rL[0])) {
        hlt = 5;
    } else if (isC(rX[0]) && isC(rL[0])) {
        hlt = 6;
    } else if (isC(rX[0]) && (rL[0] == '0')) {
        s = rX[0];
    } else if (isC(rX[0]) && (rL[0] == '-')) {
        s = rX[0];
    } else if ((rX[0] == '0') && isN(rL[0])) {
        s = rL[0];
    } else if ((rX[0] == '0') && isC(rL[0])) {
        s = rL[0];
    } else if ((rX[0] == '0') && (rL[0] == '0')) {
        s = '0';
    } else if ((rX[0] == '0') && (rL[0] == '-')) {
        s = '-';
    } else if ((rX[0] == '-') && isN(rL[0])) {
        s = rL[0];
    } else if ((rX[0] == '-') && isC(rL[0])) {
        s = rL[0];
    } else if ((rX[0] == '-') && (rL[0] == '0')) {
        s = '-';
    } else if ((rX[0] == '-') && (rL[0] == '-')) {
        s = '-';
    }
    
    /*if (rX[0] == rL[0]) {
        // always positive
        s = '0';
    } else {
        // result is always negative
        s = '-';
    }*/
    
    rX[0] = '0';
    if (rL[0] == '-') {
        Lneg = 1;
        rL[0] = '0';
    }
    mul(s);
    if (Lneg == 1)
        rL[0] = '-';
}

void S0(void)
{
    char sgn = 0;
    int done = 0;
    
    if (isN(rA[0]) && isN(rX[0])) {
        hlt = 3;
    } else if (isN(rA[0]) && isC(rX[0])) {
        hlt = 4;
    } else if (isN(rA[0]) && (rX[0] == '0')) {
        sgn = rA[0];
    } else if (isN(rA[0]) && (rX[0] == '-')) {
        sgn = rA[0];
    } else if (isC(rA[0]) && isN(rX[0])) {
        hlt = 5;
    } else if (isC(rA[0]) && isC(rX[0])) {
        hlt = 6;
    } else if (isC(rA[0]) && (rX[0] == '0')) {
        sgn = rA[0];
    } else if (isC(rA[0]) && (rX[0] == '-')) {
        sgn = rA[0];
    } else if ((rA[0] == '0') && isN(rX[0])) {
        sgn = rX[0];
    } else if ((rA[0] == '0') && isC(rX[0])) {
        sgn = rX[0];
    } else if ((rA[0] == '0') && (rX[0] == '0')) {
        // is addition
        sgn = rX[0];
        rA[0] = '0';
        rX[0] = '0';
        addAX();
        if (rA[0] != '0') {
            // overflow into sign position
            ovf = 1;
            shr(rA);
        }
        rA[0] = sgn;
        rX[0] = sgn;
        done = 1;
    } else if ((rA[0] == '0') && (rX[0] == '-')) {
        switch(cmp(rA,rX)) {
            case 1:
                sgn = '0';
                break;
            case -1:
                sgn = '-';
                break;
        }
    } else if ((rA[0] == '-') && isN(rX[0])) {
        sgn = rX[0];
    } else if ((rA[0] == '-') && isC(rX[0])) {
        sgn = rX[0];
    } else if ((rA[0] == '-') && (rX[0] == '0')) {
        switch(cmp(rA,rX)) {
            case 1:
                sgn = '0';
                break;
            case -1:
                sgn = '-';
                break;
        }
    } else if ((rA[0] == '-') && (rX[0] == '-')) {
        // is addition
        sgn = rX[0];
        rA[0] = '0';
        rX[0] = '0';
        addAX();
        if (rA[0] != '0') {
            // overflow into sign position
            ovf = 1;
            shr(rA);
        }
        rA[0] = sgn;
        rX[0] = sgn;
        done = 1;
    }
    
    if (done == 0) {
        rA[0] = '0';
        rX[0] = '0';
        subAX();
        if (rA[0] == '9') {
            cpl(rA);
        }
        if (rA[0] != '0') {
            // overflow into sign position
            ovf = 1;
            shr(rA);
        }
        rA[0] = sgn;
    }
    
    /*if (rX[0] == rA[0]) {
        // is addition
        sgn = rX[0];
        rA[0] = '0';
        rX[0] = '0';
        addAX();
        if (rA[0] != '0') {
            // overflow into sign position
            shr(rA);
        }
        rA[0] = sgn;
        rX[0] = sgn;
    }
    else {
        switch(cmp(rA,rX)) {
            case 0:
                zero(rA);
                sgn = '0';
                done = 1;
                break;
            case 1:
                sgn = '0';
                break;
            case -1:
                sgn = '-';
                break;
        }
        if (done == 0) {
            rA[0] = '0';
            rX[0] = '0';
            subAX();
            if (rA[0] == '9') {
                cpl(rA);
            }
            rA[0] = sgn;
        }
    }*/
}

void A0(void)
{
    char sgn = 0;
    int done = 0;
    
    if (isN(rA[0]) && isN(rX[0])) {
        hlt = 3;
    } else if (isN(rA[0]) && isC(rX[0])) {
        hlt = 4;
    } else if (isN(rA[0]) && (rX[0] == '0')) {
        sgn = rA[0];
    } else if (isN(rA[0]) && (rX[0] == '-')) {
        sgn = rA[0];
    } else if (isC(rA[0]) && isN(rX[0])) {
        hlt = 5;
    } else if (isC(rA[0]) && isC(rX[0])) {
        hlt = 6;
    } else if (isC(rA[0]) && (rX[0] == '0')) {
        sgn = rA[0];
    } else if (isC(rA[0]) && (rX[0] == '-')) {
        sgn = rA[0];
    } else if ((rA[0] == '0') && isN(rX[0])) {
        sgn = rX[0];
    } else if ((rA[0] == '0') && isC(rX[0])) {
        sgn = rX[0];
    } else if ((rA[0] == '0') && (rX[0] == '0')) {
        sgn = '0';
    } else if ((rA[0] == '0') && (rX[0] == '-')) {
        switch(cmp(rA,rX)) {
            case 1:
                sgn = '0';
                break;
            case -1:
                sgn = '-';
                break;
        }
        rA[0] = '0';
        rX[0] = '0';
        subAX();
        if (rA[0] == '9') {
            cpl(rA);
        }
        if (rA[0] != '0') {
            // overflow into sign position
            ovf = 1;
            shr(rA);
        }
        rA[0] = sgn;
        done = 1;
    } else if ((rA[0] == '-') && isN(rX[0])) {
        sgn = rX[0];
    } else if ((rA[0] == '-') && isC(rX[0])) {
        sgn = rX[0];
    } else if ((rA[0] == '-') && (rX[0] == '0')) {
        switch(cmp(rA,rX)) {
            case 1:
                sgn = '0';
                break;
            case -1:
                sgn = '-';
                break;
        }
        rA[0] = '0';
        rX[0] = '0';
        subAX();
        if (rA[0] == '9') {
            cpl(rA);
        }
        if (rA[0] != '0') {
            // overflow into sign position
            ovf = 1;
            shr(rA);
        }
        rA[0] = sgn;
        done = 1;
    } else if ((rA[0] == '-') && (rX[0] == '-')) {
        sgn = '-';
    }
    
    if (done == 0) {
        rA[0] = '0';
        rX[0] = '0';
        addAX();
        if (rA[0] != '0') {
            // overflow into sign position
            ovf = 1;
            shr(rA);
        }
        rA[0] = sgn;
        rX[0] = sgn;
    }

    
    
    /*if (rX[0] == rA[0]) {
        // is addition
        sgn = rX[0];
        rA[0] = '0';
        rX[0] = '0';
        addAX();
        if (rA[0] != '0') {
            // overflow into sign position
            shr(rA);
        }
        rA[0] = sgn;
        rX[0] = sgn;
    }
    else {
        switch(cmp(rA,rX)) {
            case 0:
                zero(rA);
                sgn = 0;
                done = 1;
                break;
            case 1:
                sgn = '0';
                break;
            case -1:
                sgn = '-';
                break;
        }
        if (done == 0) {
            rA[0] = '0';
            rX[0] = '0';
            subAX();
            if (rA[0] == '9') {
                cpl(rA);
            }
            rA[0] = sgn;
        }
    }*/
}

/*
void X0(void)
{
    char sgn = 0;
    int done = 0;
    
    if (rX[0] == rA[0]) {
        // is addition
        sgn = rX[0];
        rA[0] = '0';
        rX[0] = '0';
        addAX();
        if (rA[0] != '0') {
            // overflow into sign position
            zero(SR);
            shr(rA);
        }
        rA[0] = sgn;
        rX[0] = sgn;
    }
    else {
        switch(cmp(rA,rX)) {
            case 0:
                zero(rA);
                sgn = 0;
                done = 1;
                break;
            case 1:
                sgn = '0';
                break;
            case -1:
                sgn = '-';
                break;
        }
        if (done == 0) {
            rA[0] = '0';
            rX[0] = '0';
            subAX();
            if (rA[0] == '9') {
                cpl(rA);
            }
            rA[0] = sgn;
        }
    }
}
*/

void dump(int t)
{
    printf("Dumping registries...\n");

    printf("rA ");
    for(int i=0;i<12;i++)
        printf("%c",rA[i]);
    printf("\n");
    
    printf("rX ");
    for(int i=0;i<12;i++)
        printf("%c",rX[i]);
    printf("\n");
    
    printf("rL ");
    for(int i=0;i<12;i++)
        printf("%c",rL[i]);
    printf("\n");
    
    printf("rF ");
    for(int i=0;i<12;i++)
        printf("%c",rF[i]);
    printf("\n");
    
    printf("CC ");
    for(int i=0;i<12;i++)
        printf("%c",CC[i]);
    printf("\n");
    
    if (t == 1) {
        for(int i=0;i<2000;i++) {
            printf("[%04d]\t",i);
            for(int j=0;j<12;j++) {
                printf("%c",mem[i][j]);
            }
            printf("\n");
        }
    }
    else if (t == 2) {
        for (int i = 0; i < 10000; i++) {
            printf("[%04d]\t", i);
            for (int j = 0; j < 12; j++) {
                printf("%c", mem[i][j]);
            }
            printf("\n");
        }
    }
}

void ex(void)
{
    int ad;
    int d;
    int cells;
    int ilock[58] = { 0, };
    
    ad = (SR[2]-'0')*1000 + (SR[3]-'0')*100 + (SR[4]-'0')*10 + (SR[5]-'0');
    d = SR[1];
    cells = d - '0';
    
    switch(SR[0]) {
        case 'B':
            if (d == 'F') {
                for(int i=0;i<12;i++) {
                    if (rF[i] == '1') {
                        rA[i] = mem[ad][i];
                    } else {
                        rA[i] = '0';
                    }
                }
            } else {
                cpy(rA,mem[ad]);
                cpy(rX,mem[ad]);
            }
            break;
        case 'C':
            cpy(mem[ad],rA);
            zero(rA);
            break;
        case 'H':
            cpy(mem[ad],rA);
            break;
        case 'J':
            cpy(mem[ad],rX);
            break;
        case 'F':
            cpy(rF,mem[ad]);
            break;
        case 'G':
            cpy(mem[ad],rF);
            break;
        case 'E':
            if (d == '0') {
                for(int i=0;i<12;i++) {
                    if (rF[i] == '1') {
                        rA[i] = mem[ad][i];
                    }
                }
            }
            else if (d == 'F') {
                for(int i=0;i<12;i++) {
                    if (rF[i] == '0') {
                        rA[i] = mem[ad][i];
                    }
                }
                cpy(mem[ad], rA);
            }
            break;
        case 'A':
            if (d == 'H') {
                cpy(rX,mem[ad]);
                A0();
                cpy(mem[ad],rA);
            }
            else if (d == 'F') {
                for(int i=0;i<12;i++) {
                    if (rF[i] == '1') {
                        rX[i] = mem[ad][i];
                    }
                }
                A0();
            }
            else {
                cpy(rX,mem[ad]);
                A0();
            }
            break;
        case 'X':
            A0();
            break;
        case 'S':
            if (d == 'H') {
                cpy(rX,mem[ad]);
                neg(rX);
                S0();
                cpy(mem[ad],rA);
            }
            else if (d == 'F') {
                for(int i=0;i<12;i++) {
                    if (rF[i] == '1') {
                        rX[i] = mem[ad][i];
                    }
                }
                neg(rX);
                S0();
            }
            else {
                cpy(rX,mem[ad]);
                neg(rX);
                S0();
            }
            break;
        case '0':
            if (SR[1] != '0') {
                for (int i=0;i<d-'0';i++)
                    sshl(rA);
            }
            break;
        case '1':
            if (d == '0') {
                for(int i=0;i<12;i++)
                    printf("%c",mem[ad][i]);
            } else {
                if (ilock[d] != 1) {
                    for(int i=0;i<60;i++) {
                        for(int j=0;j<12;j++) {
                            rI[i][j]=fgetc(tn(d));
                        }
                    }
                } else {
                    hlt = d;
                }
            }
            break;
        case '2':
            if (d != '0') {
                if (ilock[d] != 1) {
                    for(int i=59;i>=0;i--) {
                        for(int j=0;j<12;j++) {
                            rI[i][j]=fgetc(tn(d));
                        }
                    }
                } else {
                    hlt = d;
                }
            }
            break;
        case '3':
            if (d == '0') {
                for(int i=0;i<59;i++) {
                    for(int j=0;j<12;j++)
                        mem[ad+i][j]=rI[i][j];
                }
            } else {
                for(int i=0;i<59;i++) {
                    for(int j=0;j<12;j++)
                        mem[ad+i][j]=rI[i][j];
                }
                if (ilock[d] != 1) {
                    for(int i=0;i<60;i++) {
                        for(int j=0;j<12;j++) {
                            rI[i][j]=fgetc(tn(d));
                        }
                    }
                } else {
                    hlt = d;
                }
            }
            break;
        case '4':
            if (d == '0') {
                for(int i=0;i<59;i++) {
                    for(int j=0;j<12;j++)
                        mem[ad+i][j]=rI[i][j];
                }
            } else {
                for(int i=0;i<59;i++) {
                    for(int j=0;j<12;j++)
                        mem[ad+i][j]=rI[i][j];
                }
                if(ilock[d] != 1) {
                    for(int i=59;i>=0;i--) {
                        for(int j=0;j<12;j++) {
                            rI[i][j]=fgetc(tn(d));
                        }
                    }
                } else {
                    hlt = d;
                }
            }
            break;
        case '5':
            if (d == '0') {
                for(int i=0;i<12;i++)
                    printf("%c",mem[ad][i]);
            } else {
                if (ilock[d] != 1) {
                    for(int i=0;i<60;i++) {
                        for(int j=0;j<12;j++)
                            fputc(mem[ad+i][j],tn(d));
                    }
                } else {
                    hlt = d;
                }
            }
            break;
        case '6':
            rewind(tn(d));
            break;
        case '7':
            if (ilock[d] != 1) {
                for(int i=0;i<60;i++) {
                    for(int j=0;j<12;j++)
                        fputc(mem[ad+i][j],tn(d));
                }
            } else {
                hlt = d;
            }
            break;
        case '8':
            rewind(tn(d));
            ilock[d] = 1;
            break;
        case '9':
            hlt = 1;
            break;
        case 'L':
            if (d == 'F') {
                for(int i=0;i<12;i++) {
                    if (rF[i] == '1') {
                        rL[i] = mem[ad][i];
                        rX[i] = mem[ad][i];
                    } else {
                        rL[i] = '0';
                        rX[i] = '0';
                    }
                }
            } else {
                cpy(rL,mem[ad]);
                cpy(rX,mem[ad]);
            }
            break;
        case 'K':
            cpy(rL,rA);
            zero(rA);
            break;
        case 'I':
            cpy(mem[ad],rL);
            break;
        case 'P':
            if (d == 'F') {
                for(int i=0;i<12;i++) {
                    if (rF[i] == '1') {
                        rX[i] = mem[ad][i];
                    } else {
                        rX[i] = '0';
                    }
                }
            } else {
                cpy(rX,mem[ad]);
                P0();
            }
            break;
        case 'M':
            cpy(rX,mem[ad]);
            P0();
            roundd();
            break;
        case 'N':
            cpy(rX,mem[ad]);
            neg(rX);
            P0();
            roundd();
            break;
        case 'D':
            if (d == 'F') {
                for(int i=0;i<12;i++) {
                    if (rF[i] == '1') {
                        rA[i] = mem[ad][i];
                    } else {
                        rA[i] = '0';
                    }
                }
            } else {
                cpy(rA,mem[ad]);
                D0();
            }
            break;
        case 'U':
            for(int i=2;i<6;i++)
                CC[6+i] = SR[i];
            break;
        case '-':
            for (int i=0;i<d-'0';i++)
                sshr(rA);
            break;
        case ';':
            for (int i=0;i<d-'0';i++)
                shl(rA);
            break;
        case '.':
            for (int i=0;i<d-'0';i++)
                shr(rA);
        case 'Q':
            if (cmp(rA,rL) == 0) {
                // U0
                for(int i=2;i<6;i++)
                    CC[6+i] = SR[i];
                break;
            }
            break;
        case 'T':
            if (cmp(rA,rL) == 1) {
                // U0
                for(int i=2;i<6;i++)
                    CC[6+i] = SR[i];
                break;
            }
            break;
        case 'V':
            for (int i=ad,j=cells-1;i<ad+cells;i++,j--)
                cpy(rW[j],mem[i]);
            break;
        case 'W':
            for (int i=ad,j=cells-1;i<ad+cells;i++,j--)
                cpy(mem[i],rW[j]);
            break;
        case 'Y':
            cells *= 10;
            for (int i=ad,j=cells-1;i<ad+cells;i++,j--)
                cpy(rZ[j],mem[i]);
            break;
        case 'Z':
            cells *= 10;
            for (int i=ad,j=cells-1;i<ad+cells;i++,j--)
                cpy(mem[i],rZ[j]);
            break;
        case 'R':
            for(int i=0;i<6;i++)
                mem[ad][i] = '0';
            mem[ad][6] = 'U';
            mem[ad][7] = '0';
            for(int i=2;i<6;i++)
                mem[ad][6+i] = CC[6+i];
            break;
    }
}

void _beta(void)
{
    int ad = 0;
    
    if (ovf == 0) {
        for(int i=0;i<6;i++)
            SR[i] = CC[6+i];
        ad = (SR[2]-'0')*1000 + (SR[3]-'0')*100 + (SR[4]-'0')*10 + (SR[5]-'0');
    } else {
        printf("OVF at CC: ");
        for(int i=0;i<12;i++)
            printf("%c",CC[i]);
        printf("\n");
        zero(SR);
        ovf = 0;
    }
    
    for(int i=0;i<12;i++)
        CR[i] = mem[ad][i];
    
    addnn(CC,one);
}

void _gamma(void)
{
    for(int i=0;i<6;i++)
        SR[i]=CR[i];
    ex();
}

void _delta(void)
{
    for(int i=0;i<6;i++)
        SR[i]=CR[6+i];
    ex();
}

void microcode(void)
{
    while(hlt == 0) {
            _beta();
            _gamma();
            _delta();
    }
    printf("\nHLT: RC%d\n", hlt-1);
}

void closetape(void) {
    if (t1 != NULL)
        fclose(t1);
    if (t2 != NULL)
        fclose(t2);
    if (t3 != NULL)
        fclose(t3);
    if (t4 != NULL)
        fclose(t4);
    if (t5 != NULL)
        fclose(t5);
    if (t6 != NULL)
        fclose(t6);
    if (t7 != NULL)
        fclose(t7);
    if (t8 != NULL)
        fclose(t8);
    if (t9 != NULL)
        fclose(t9);
    if (t10 != NULL)
        fclose(t10);
}

int main(int argc, const char * argv[]) {
    init();
    
#include "config.h"
    
    microcode();
    
    closetape();
    
    dump(0);
    
    return 0;
}
