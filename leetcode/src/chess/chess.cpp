#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cstring>

using std::cout;
using std::map;
using std::vector;
using std::endl;
using std::list;

int main(int argc, char *argv[])
{
    int cases;
    
    freopen(argv[1], "r", stdin);
    
    scanf("%d", &cases);
#ifdef DEBUG
            cout << "cases:" << cases << endl;
#endif
    int square = 9;

    char **mat = (char**) malloc (square * sizeof(char*));
    for(int j = 0; j < square; j++){
        mat[j] = (char*) malloc(square * sizeof(char));
    }
    
    char line[5];
    for(int i = 0; i < cases; i++) {
        for(int j = 1; j < square; j++)
            memset(mat[j], 0, square);
        
        int pn;
        scanf("%d", &pn);
        for(int j = 0; j < pn; j++){
            scanf("%s", line);
            int row = line[1] - '0';
            int col = square - 1 - (line[0] - 'A');
            mat[row][col] = line[3];
        }

#ifdef DEBUG
        for(int j = 1; j < square; j++){
            cout << j;
            for(int k = 1; k < square; k++) {
                printf(" %c |", mat[j][k] > 0 ? mat[j][k] : ' ');
            }
            cout << endl;
        }
        for(int k = 1; k < square; k++) {
            printf("   %c", 'I'-k);
        }
        cout << endl << endl;
#endif
        int num = 0;
        for(int j = 1; j < square; j++){
            int tj = j;
            for(int k = 1; k < square; k++) {
                int tk = k;
                char ch = mat[j][k];
                switch(ch){
                    case 'K':
                    for(int row = 8; row > 0 && tj - row; row--)
                        if(mat[row][tk] > 0)
                            num++;
                    for(int row = tj; row >= 1; row--)
                        if(mat[row][tk] > 0)
                            num++;
                    
                        
                }
        //printf("Case #%d:", i+1);
    }
}