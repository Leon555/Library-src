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

int main(int argc, char *argv[])
{
    int cases;
    
    freopen(argv[1], "r", stdin);
    
    scanf("%d", &cases);
#ifdef DEBUG
            cout << "cases:" << cases << endl;
#endif
    
    for(int i = 0; i < cases; i++) {
        int cityN;
        scanf("%d", &cityN);
        char **start = (char**) malloc (cityN * sizeof(char*));
        char **end = (char**) malloc (cityN * sizeof(char*));
        for(int j = 0; j < cityN; j++){
            start[j] = (char*) malloc(4 * sizeof(char));
            end[j] = (char*) malloc(4 * sizeof(char));
            scanf("%s", start[j]);
            scanf("%s", end[j]);
#ifdef DEBUG
            cout << start[j] << " " << end[j] << " ";
#endif
        }
        printf("Case #%d:", i+1);
        
        // find the start city
        int j = 0;
        for(j = 0; j < cityN; j++){
            int k;
            for(k = 0; k < cityN; k++){
                if(strcmp(start[j], end[k]) == 0)
                    break;
            }
            if(k == cityN)
                break;
        }
        for(int k = 0; k < cityN; k++){
            cout << " " << start[j] << "-" << end[j];
            int n;
            for(n = 0; n < cityN; n++){
                if(strcmp(end[j], start[n]) == 0)
                    break;
            }
            j = n;
        }
        
        cout << endl;
        for(int j = 0; j < cityN; j++){
            free(start[j]);
            free(end[j]);
        }
        free(start);
        free(end);
    }
}