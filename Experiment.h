#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <bits/stdc++.h>
#include "glist.h"

#define PII pair<int,int>
#define inf 0x3fffffff
using namespace std;

extern const int maxn,maxm;
extern int n,m,ppp[],pre[],followers[],collapsed[],update[],critical[];

struct nodes{
    int coreness,degree,binpos,valid;
};
extern struct nodes node[],tmp[],save[],tmp2[];

struct Sort{
    int l,r;
};
extern struct Sort a[];

extern vector<int> edge[];

struct Edge{
    vector<int> More,Equal,Less;
};
extern struct Edge edges[];

extern int budget;
extern vector<int> bin[],hier,tid_;
extern int bb[],cur_k;
extern int lowerbound[],upperbound[];

struct LCPSTreeVertex{
	vector<int> delta;
	vector<LCPSTreeVertex*> son;
	LCPSTreeVertex *p;
	int id;
	short k;
};
extern vector<LCPSTreeVertex*> t_;

struct CCT{
    int id,layer;
};
extern struct CCT tree[];
extern int nodeCCT,CCT_size[],CCT_ance_size[],CCT_child_size[],CCT_fa[];
extern vector<int> CCTchild[];


class Experiment
{
    public:
    void ReadEdgesS(int n, int m);
    void __adjust_k(int target_k);
    pair<char, int> decode_adjust(int mask);
    void get_v(LCPSTreeVertex *rt, vector<int> &res);
    vector<int> get_v(int v);
    void __build_hier(vector<vector<int>> graph, vector<int> core, int n, int max_coreness);
    void __build_tree();
    LCPSTreeVertex *dfs(LCPSTreeVertex *cur, vector<LCPSTreeVertex *> &store, LCPSTreeVertex *p);
    void __compress_tree(int n);
    void pre_LCPS(vector<vector<int>> graph, vector<int> core, int n, int max_coreness);
    void BuildCCT(int n, vector<int> G, vector<int> core, int fa, int Min_core);
    int ub(int x);
    int upper_bound(int n, int x, vector<int> core);
    int lower_bound(int x);
};


#endif