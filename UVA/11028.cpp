#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    int n, nc = 1, cases[]={0,1,1,1,3,8,21,43,69,102,145,197,261,336,425,527,645,778,929,1097,1285};
   	while(scanf("%d", &n), n) printf("Case #%d: %d\n", nc++, cases[n]);
    return 0;
}
