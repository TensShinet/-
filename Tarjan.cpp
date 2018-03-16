#include <stdio.h>
#include <malloc.h>

#define VEXNUM 10001
struct ArcNode {
    int v;
    struct ArcNode* next;
};
struct ArcCell {
    struct ArcNode* first;
};
struct GraphStruct {
    int vexnum, arcnum;
    struct ArcCell a[VEXNUM];
};
// stack
struct StackStruct {
    int top;
    int a[VEXNUM];
};
//
typedef struct GraphStruct* Graph;
typedef struct StackStruct* Stack;
typedef struct ArcNode* Arc;

Graph G = (Graph)malloc(sizeof(struct GraphStruct));
Stack S = (Stack)malloc(sizeof(struct StackStruct));

int visite[VEXNUM];
int dfn[VEXNUM];
int low[VEXNUM];
int runNum = 0;

void inputData();
void insertList(int v1, int v2);
void Tarjan(int s);
int min(int a, int b);
void quickSort(int s, int f);
int randPartition(int s, int f);
int Partition(int s, int f);
void swap(int a, int b);

void test_low();
void test_data();
int main(void) {
    inputData();
    // test_data();
    // initialize Stack
    S->top = -1;
    Tarjan(1);
    test_low();
    quickSort(1, G->vexnum);
    test_low();
    return 0;
}
void inputData() {
    int i;
    int vexnum, arcnum;
    int v1, v2;
    FILE* fp = fopen("tarjanNum2.txt", "r");
    fscanf(fp, "%d %d", &vexnum, &arcnum);
    G->vexnum = vexnum;
    G->arcnum = arcnum;
    // 初始化 first
    for(i = 1; i <= G->vexnum; i++) {
        G->a[i].first = NULL;
    }
    //
    fp = fopen("tarjanData2.txt", "r");
    for(i = 0; i < G->arcnum; i++) {
        // 无向图
        fscanf(fp, "%d %d", &v1, &v2);
        insertList(v1, v2);
    }
}
void insertList(int v1, int v2) {
    Arc n = G->a[v1].first;
    Arc newNode = (Arc)malloc(sizeof(struct ArcNode));
    newNode->v = v2;
    newNode->next = NULL;

    G->a[v1].first = newNode;
    newNode->next = n;
}
void Tarjan(int s) {
    visite[s] = 1;
    ++runNum;
    low[s] = dfn[s] = runNum;
    Arc n = G->a[s].first;
    int v;
    while(n) {
        v = n->v;
        // enter
        if(visite[v] == 0) { Tarjan(v); }
        // back or meet visitedNode
        if(visite[v] == 1) {
            low[s] = min(dfn[s], low[v]);
        }
        n = n->next;
    }
}
int min(int a, int b) {
    if(a > b) {
        return b;
    }

    return a;
}
void quickSort(int s, int f) {
    if(s >= f) {
        return;
    }
    int m = randPartition(s, f);
    quickSort(s, m-1);
    quickSort(m+1, f);
}
int randPartition(int s, int f) {
    int m;
    m = rand() % (f-s) + s;
    swap(m, f);
    return Partition(s, f);
}
int Partition(int s, int f) {
    int x = low[f];
    int i = s-1;
    int j;
    for(j = s; j < f; j++) {
        if(low[j] < x) {
            i++;
            swap(i, j);
        }
    }
    i++;
    swap(i, f);
    return i;
}
void swap(int a, int b) {
    int c = low[a];
    low[a] = low[b];
    low[b] = c;
}
void test_low() {
    int i;
    for(i = 1; i <= G->vexnum; i++) {
        printf("%d ", low[i]);
    }
    printf("\n");

}
void test_data() {
    Arc n;
    int i;

    for(i = 1; i <= G->vexnum; i++) {
        printf("%d ", i);
        n = G->a[i].first;
        while(n) {
            printf("%d ", n->v);
            n = n->next;
        }
        printf("\n");
    }
}
