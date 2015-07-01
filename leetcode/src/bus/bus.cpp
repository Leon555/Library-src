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
        int busN;
        scanf("%d", &busN);
        int *start = (int*) malloc (busN * sizeof(int));
        int *end = (int*) malloc (busN * sizeof(int));
        for(int j = 0; j < busN; j++){
            scanf("%d", &start[j]);
            scanf("%d", &end[j]);
#ifdef DEBUG
            cout << start[j] << " " << end[j] << " ";
#endif
        }
        printf("Case #%d:", i+1);
        int cityN;
        scanf("%d", &cityN);
        int *cities = (int*) malloc (cityN * sizeof(int));
        for(int k = 0; k < cityN; k++){
            scanf("%d", &cities[k]);
            int cn = 0;
            for(int j = 0; j < busN; j++){
                if(start[j] <= cities[k] && cities[k] <= end[j])
                    cn++;
            }
            cout << " " << cn;
        }
        cout << endl;
        free(start);
        free(end);
        free(cities);
    }
}