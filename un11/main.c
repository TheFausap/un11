//
//  main.c
//  un11
//
//  Created by Fausto Saporito on 29/10/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char* rA;
char* rX;
char* rF;
char* rL;
char** mem;

void zero(char* a)
{
    for(int i=0;i<12;i++)
        a[i] = '0';
}

void shr(char* a)
{
    for(int i=11;i>=1;i--)
        a[i] = a[i-1];
    a[0] = '0';
}

void shl(char* a)
{
    for(int i=0;i<11;i++)
        a[i] = a[i+1];
    a[11] = '0';
}

// shift left extend
// move rA digits to the corresponding rX digits
void shle(int i)
{
    rX[i] = rA[11];
    for(int i=11;i>=1;i--)
        rA[i] = rA[i-1];
}

void set(char* a, long v)
{
    int s = (v < 0) ? 1 : 0;
    
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

void init(void)
{
    rA=calloc(12,sizeof(char));
    rX=calloc(12,sizeof(char));
    rF=calloc(12,sizeof(char));
    rL=calloc(12,sizeof(char));
    
    mem=calloc(1000,sizeof(char));
    for(int i=0;i<1000;i++) {
        mem[i] = calloc(12,sizeof(char));
        zero(mem[i]);
    }
    zero(rA); zero(rX);
    zero(rF); zero(rL);
}

void addAX(void)
{
    int t = 0;
    int c = 0;
    
    for(int i=11;i>=0;i--) {
        t = (rA[i]-'0') + (rX[i] - '0') + c;
        if (t > 9) {
            t -= 10;
            c = 1;
        } else {
            c = 0;
        }
        rA[i] = t + '0';
    }
}

void addAL(void)
{
    int t = 0;
    int c = 0;
    
    for(int i=11;i>=0;i--) {
        t = (rA[i]-'0') + (rL[i] - '0') + c;
        if (t > 9) {
            t -= 10;
            c = 1;
        } else {
            c = 0;
        }
        rA[i] = t + '0';
    }
}

void addAF(void)
{
    int t = 0;
    int c = 0;
    
    for(int i=11;i>=0;i--) {
        t = (rA[i]-'0') + (rF[i] - '0') + c;
        if (t > 9) {
            t -= 10;
            c = 1;
        } else {
            c = 0;
        }
        rA[i] = t + '0';
    }
}

void subAX(void)
{
    int t = 0;
    int c = 0;
    
    for(int i=11;i>=0;i--) {
        t = (rA[i]-'0') - (rX[i] - '0') - c;
        if (t < 0) {
            t = 10 - abs(t);
            c = 1;
        } else {
            c = 0;
        }
        rA[i] = t + '0';
    }
}

void subAL(void)
{
    int t = 0;
    int c = 0;
    
    for(int i=11;i>=0;i--) {
        t = (rA[i]-'0') - (rL[i] - '0') - c;
        if (t < 0) {
            t = 10 - abs(t);
            c = 1;
        } else {
            c = 0;
        }
        rA[i] = t + '0';
    }
}

void mul(int addr)
{
    char mqc;
    
    zero(rA);
    rL[0] = '0';
    addAL(); addAL(); addAL();
    cpy(rF,rA);
    cpy(rX,mem[addr]);
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
}

void divv(int addr)
{
    int mqc = 0;
    cpy(rA,mem[addr]);
    zero(rX);
    
    rL[0] = '0';
    rA[0] = '0';
    for (int i=0;i<11;i++) {
        shl(rA);
        while(rA[0] != '9') {
            subAL();
            mqc++;
        }
        rX[11] = (mqc-1) + '0';
        shl(rX); shl(rA);
        mqc = -9;
        while(rA[0] == '9') {
            addAL();
            mqc++;
        }
        rX[11] = abs(mqc) + '0';
        shl(rX);
    }
}

void dump(void)
{
    printf("rA ");
    for(int i=0;i<12;i++)
        printf("%c",rA[i]);
    printf("\n");
    
    printf("rX ");
    for(int i=0;i<12;i++)
        printf("%c",rX[i]);
    printf("\n");
}

int main(int argc, const char * argv[]) {
    init();
    
    set(rA,345);
    set(rL,455);
    set(mem[300],345);
    
    divv(300);
    
    dump();
    printf("Hello, World!\n");
    return 0;
}
