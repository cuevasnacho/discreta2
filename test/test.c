#include <stdio.h>

int main() {
    char c;
    int m, n, x, y;

    while ((c = getchar()) != EOF) {
        if (c == 'c') {
            while (c != '\n')
                c = getchar();
        } else if (c == 'p') {
            char word[5];
            scanf("%4s", word);
            scanf("%d %d\n", &n, &m);
            printf("%d %d\n",n,m);
            break;
        } else 
            printf("error");
    }
    for(int i = 0; i < m; i++){
        if(i!=m-1)
            scanf("%c %d %d\n",&c, &x, &y);
        else
            scanf("%c %d %d",&c, &x, &y);
        printf("%d %d\n",x,y);
    }

    return 0;
}