#include "Experiment.h"
#include "Stream.h"

int main()
{
    // if (argc<2)
    // {
    //     printf("Usage: ./core data\n");
    //     return 0;
    // }
    int iWd = 10;
    int iStep = 1;
    // char input[100];
    char output[100];
    sprintf(output, "GCC.txt");
    freopen(output, "w", stdout);

    Stream oGraph;
    oGraph.readFromFile("/home/Axton/Our_Own_Anchor_Collapse_algorithm/BaseLine/data4paper.txt");

    // 打印边的信息
    // printf("Graph info: [%d, %d], n: %d m: %d\n", oGraph.m_uiTS, oGraph.m_uiTE,oGraph.m_uiN, oGraph.m_uiM);
    // printf("Parameters: %d, %d\n", iWd, iStep);

    // const auto beg = std::chrono::steady_clock::now();
    vector<pair<uint32_t, uint32_t>> vWEdges;

    int iEndT = oGraph.m_uiTS + iWd - 1;
    int iStartT = oGraph.m_uiTS;
    iStartT = iStartT > 0 ? iStartT : 0;
    int iBatch = iStep;

    int CurrentTime = 0;
    oGraph.getEdges(iStartT, iEndT, vWEdges);
    uint32_t max_number = oGraph.getMax(iStartT, iEndT); // 1. 获取滑动窗口内的边
    oGraph.InsertEdge_Graph(vWEdges, max_number);

    bool first_handle = false;
    while (iEndT < oGraph.m_uiTE)
    {
        const auto beg = std::chrono::steady_clock::now();
        if (first_handle)
        {
            int ProcssedEdgeNum = 0;
            iBatch = COMMON_MIN(iBatch, oGraph.m_uiTE - iEndT);

            int iRmEnd = iStartT + iBatch - 1;
            vWEdges.clear();
            oGraph.getEdges(iStartT, iRmEnd, vWEdges);
            oGraph.DeleteEdge_Graph(vWEdges); // 获取删除的边

            iStartT += iBatch;
            int iInsEnd = iEndT + iBatch;

            vWEdges.clear();
            oGraph.getEdges(iEndT + 1, iInsEnd, vWEdges); // 获得增加的边
            max_number = oGraph.getMax(iStartT, iEndT + 1);
            oGraph.InsertEdge_Graph(vWEdges, max_number);

            iEndT = iInsEnd;
            CurrentTime++;
        }
        first_handle = true;

        // 处理数据
        Experiment *ex = new Experiment();

        int n, m, m2;

        n = max_number;
        budget = n;
        m = vWEdges.size();

        // read the graph
        // ex->ReadEdgesS(n, m);
        // initialize the core component
        core::CoreMaintenance *cm = nullptr;
        cm = new core::GLIST(n);
        // create the adjacent list representation
        vector<vector<int>> graph(n);
        for (int i = 0; i < n; i++)
            graph[i] = edge[i];
        vector<int> core(n);
        cm->ComputeCore(graph, true, core);
        for (int i = 0; i < n; i++)
            ppp[i] = core[i], pre[i] = core[i];
        auto Starttime = (double)clock();
        int Max_follower = 0, Max_follower_pos = 0;
        for (int x = 0; x < n; x++)
        {
            edges[x].More.clear();
            edges[x].Less.clear();
            edges[x].Equal.clear();
            for (auto y : graph[x])
                if (core[y] > core[x])
                    edges[x].More.push_back(y);
                else if (core[y] < core[x])
                    edges[x].Less.push_back(y);
                else
                    edges[x].Equal.push_back(y);
        }
        for (int i = 0; i < n; i++)
        {
            int x = i;
            for (auto y : edges[x].Less)
            {
                if (x < y)
                    cm->Remove(x, y, graph, core);
                else
                    cm->Remove(y, x, graph, core);
            }
            for (auto y : edges[x].Equal)
            {
                if (x < y)
                    cm->Remove(x, y, graph, core);
                else
                    cm->Remove(y, x, graph, core);
            }
            followers[i] = 0;
            for (int j = 0; j < n; j++)
                if (i != j && core[j] < ppp[j])
                    followers[i]++;
            for (auto y : edges[x].Less)
            {
                if (x < y)
                    cm->Insert(x, y, graph, core);
                else
                    cm->Insert(y, x, graph, core);
            }
            for (auto y : edges[x].Equal)
            {
                if (x < y)
                    cm->Insert(x, y, graph, core);
                else
                    cm->Insert(y, x, graph, core);
            }
            collapsed[i] = 0;
            update[i] = 0;
            if (followers[i] > Max_follower)
                Max_follower = followers[i], Max_follower_pos = i;
        }
        auto Endtime = (double)clock();
        int ans = 0;

        if (budget != 1)
        {
            std::cout << "--------------------------------" << std::endl;
        }
        for (int i = 1; i <= budget; i++)
        {
            if (budget == 1)
            {
                break;
            }

            printf("%d\t%d\t", i, ans + Max_follower);
            ans += Max_follower;
            Endtime = (double)clock();
            printf("%0.5f\n", (Endtime - Starttime) / CLOCKS_PER_SEC);
            // collapse node
            int x = Max_follower_pos;
            for (auto y : edges[x].More)
                if (!collapsed[x] && !collapsed[y])
                {
                    if (x < y)
                        cm->Remove(x, y, graph, core);
                    else
                        cm->Remove(y, x, graph, core);
                }
            for (auto y : edges[x].Less)
                if (!collapsed[x] && !collapsed[y])
                {
                    if (x < y)
                        cm->Remove(x, y, graph, core);
                    else
                        cm->Remove(y, x, graph, core);
                }
            for (auto y : edges[x].Equal)
                if (!collapsed[x] && !collapsed[y])
                {
                    if (x < y)
                        cm->Remove(x, y, graph, core);
                    else
                        cm->Remove(y, x, graph, core);
                }
            collapsed[Max_follower_pos] = 1;
            // update neighbor
            for (int x = 0; x < n; x++)
            {
                edges[x].More.clear();
                edges[x].Less.clear();
                edges[x].Equal.clear();
                for (auto y : graph[x])
                    if (core[y] > core[x])
                        edges[x].More.push_back(y);
                    else if (core[y] < core[x])
                        edges[x].Less.push_back(y);
                    else
                        edges[x].Equal.push_back(y);
            }
            // get lowest coreness
            int Min_coreness = pre[Max_follower_pos];
            for (int i = 0; i < n; i++)
            {
                if (!collapsed[i] && core[i] < pre[i])
                    Min_coreness = min(Min_coreness, core[i]);
                else
                    update[i] = 1;
                bin[i].clear();
                tree[i].id = 0;
                critical[i] = 0;
            }
            bin[n].clear();
            // get critical vertex
            int Min_coreness_all = n + 100, Max_coreness = 0;
            for (int i = 0; i < n; i++)
                if (!collapsed[i])
                {
                    int More_degree = 0;
                    for (auto x : edges[i].More)
                        if (!collapsed[x])
                            More_degree++;
                    for (auto x : edges[i].Equal)
                        if (!collapsed[x])
                            More_degree++;
                    if (More_degree == core[i])
                    {
                        critical[i] = 1;
                        for (auto x : edges[i].Equal)
                            if (!collapsed[x])
                                update[x] = 1;
                        for (auto x : edges[i].More)
                            if (!collapsed[x])
                                update[x] = 1;
                    }
                    Min_coreness_all = min(Min_coreness_all, core[i]);
                    Max_coreness = max(Max_coreness, core[i]);
                    bin[core[i]].push_back(i);
                }
            // build core component tree
            vector<int> G;
            for (int i = 1; i <= n; i++)
                for (auto x : bin[i])
                    G.push_back(x);
            ex->pre_LCPS(graph, core, n, Max_coreness);
            nodeCCT = 0;
            ex->BuildCCT(n, G, core, 0, Min_coreness_all);
            for (int i = 0; i < n; i++)
                pre[i] = core[i];
            Max_follower = 0, Max_follower_pos = 0;
            int sum = 0, change_sum = 0, ub_num = 0, update_num = 0, min_coreness_num = 0, num = 0, ub2_num = 0, lb_num = 0;
            vector<vector<int>> bound(n + 1);
            for (int i = 0; i < n; i++)
                if (!collapsed[i])
                {
                    upperbound[i] = ex->upper_bound(n, i, core);
                    lowerbound[i] = ex->lower_bound(i);
                    bound[upperbound[i]].push_back(i);
                }
            for (int upb = n; upb >= 0; upb--)
                for (auto i : bound[upb])
                // for (int i=0;i<n;i++)
                {
                    int UB, LB;
                    if (!collapsed[i])
                    {
                        num++;
                        UB = upperbound[i];
                        LB = lowerbound[i];
                        if (UB <= Max_follower)
                            ub_num++;
                        if (!update[i])
                            update_num++; // follow=0
                        if (core[i] < Min_coreness)
                            min_coreness_num++; //<min change coreness
                        if (LB == UB)
                            lb_num++;
                    }
                    if (update[i]                                   // follow=0
                        && !collapsed[i] && core[i] >= Min_coreness //< Min changing nodes' coreness must not change
                        && core[i] > 0                              //&&ub(i)>Max_follower
                        && UB > Max_follower)                       // upper_bound
                    {
                        if (LB == UB)
                            followers[i] = UB; // lower_bound
                        else
                        {
                            int x = i;
                            for (auto y : edges[x].Less)
                            {
                                if (x < y)
                                    cm->Remove(x, y, graph, core);
                                else
                                    cm->Remove(y, x, graph, core);
                            }
                            for (auto y : edges[x].Equal)
                            {
                                if (x < y)
                                    cm->Remove(x, y, graph, core);
                                else
                                    cm->Remove(y, x, graph, core);
                            }
                            int pre_followers = followers[i];
                            followers[i] = 0;
                            for (int j = 0; j < n; j++)
                                if (i != j && core[j] < pre[j] && !collapsed[j])
                                    followers[i]++;
                            sum++;
                            if (pre_followers == followers[i])
                                change_sum++;
                            for (auto y : edges[x].Less)
                            {
                                if (x < y)
                                    cm->Insert(x, y, graph, core);
                                else
                                    cm->Insert(y, x, graph, core);
                            }
                            for (auto y : edges[x].Equal)
                            {
                                if (x < y)
                                    cm->Insert(x, y, graph, core);
                                else
                                    cm->Insert(y, x, graph, core);
                            }
                        }
                    }
                    if (!collapsed[i] && UB > Max_follower)
                        if (followers[i] > Max_follower)
                            Max_follower = followers[i], Max_follower_pos = i;
                }
        }
        const auto end = std::chrono::steady_clock::now();
        const auto dif = end - beg;
        auto dif_ms = std::chrono::duration_cast<std::chrono::microseconds>(dif);
        std::cout << "Duration: " << dif_ms.count() << " ms" << std::endl;
        if (budget != 1)
        {
            std::cout << "--------------------------------" << std::endl
                      << std::endl;
        }
    }

    return 0;
}
