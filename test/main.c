#include <stdio.h>
#include <stdlib.h>

char buf[100]={0};
char number[100]={0};

int ignore_blank(int j) {
    while(buf[j]==' ') ++j;
    return j;
}

int get_number(int j) {
    int v, n=0;
    while(buf[j]!=' ' && buf[j]!='\0') {
        number[n] = buf[j];
        ++n; ++j;
    }
    number[n]='\0';
    v = atoi(number);
    return v;
}

int main() {
    int e, v;
    buf[0]='p';
    for(int i=0; i<5; ++i) {
        fgets(buf,"%s",stdin);
        if (buf[0]=='p'){
            int j=7;
            v=get_number(j);
            j=ignore_blank(j);
            e=get_number(j);
            printf("\n%d %d",v,e);
        } else if (buf[0]=='e'){
            int j=2;
            v=get_number(j);
            j=ignore_blank(j);
            e=get_number(j);
            printf("\n%d %d",v,e);
        } else continue;
    }

    return 0;
}