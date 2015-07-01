#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <cstdlib>
#include <string>
#include <cstdio>

using std::cout;
using std::map;
using std::vector;
using std::endl;
using std::list;

void getMax(int **mat, int row, int *person, int *num)
{
    int tp = 0;
    int tn = 1;
    for(int i = 0; i < row; i++){
        int ti = i;
        for(int j = 0; j < row; j++){
            int tj = j;
            tp = mat[i][j];
            while(1){
                if(ti - 1 >= 0 && mat[ti-1][tj] == mat[ti][tj] + 1)
                    ti--;
                else if(ti + 1 < row && mat[ti+1][tj] == mat[ti][tj] + 1)
                    ti++;
                else if(tj - 1 >= 0 && mat[ti][tj-1] == mat[ti][tj] + 1)
                    tj--;
                else if(tj + 1 < row && mat[ti][tj+1] == mat[ti][tj] + 1)
                    tj++;
                else
                    break;
                tn++;
            }
            if(tn > *num || (tn == *num && tp < *person)){
                *num = tn;
                *person = tp;
            }
            tn = 1;
            ti = i;
        }
    }
}

int main(int argc, char *argv[])
{
    int cases;
    
    freopen(argv[1], "r", stdin);
    
    scanf("%d", &cases);
#ifdef DEBUG
            cout << "cases:" << cases << endl;
#endif
    
    for(int i = 0; i < cases; i++) {
        int row;
        scanf("%d", &row);
#ifdef DEBUG
        cout << "case:" << i  << "  row:" << row << endl;
#endif
        int **mat = (int**) malloc (row * sizeof(int *));
        for(int j = 0; j < row; j++){
            mat[j] = (int*) malloc(row * sizeof(int));
            for(int k = 0; k < row; k++){
                scanf("%d", &mat[j][k]);
#ifdef DEBUG
                cout << mat[j][k] << " ";
#endif
            }
#ifdef DEBUG
                cout << endl;
#endif
        }
        int person = 0;
        int num = 0;
        getMax(mat, row, &person, &num);
        printf("Case #%d: %d %d\n", i, person, num);
    }
}