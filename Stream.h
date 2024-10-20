#ifndef STREAM_H_
#define STREAM_H_

#include <iostream>
#include <vector>
#include <assert.h>
#include "comm.h"
#include "Experiment.h"

using namespace std;

class Stream final
{
private:
    // edge array entry
    typedef struct final
    {
        uint32_t t;
        uint32_t x;
        uint32_t y;
    } ArrayEntry;
    // order
    static bool cmp(const ArrayEntry &e1, const ArrayEntry &e2)
    {
        if (e1.t != e2.t)
        {
            return e1.t < e2.t;
        }
        else if (e1.x != e2.x)
        {
            return e1.x < e2.x;
        }
        else
        {
            return e1.y < e2.y;
        }
    }
    // the set of edges <timestamps, <edges> >
    // map<int, vector<pair<uint32_t, uint32_t> > > m_mpE;
    vector<ArrayEntry> m_vE;

public:
    uint32_t m_uiN;  // the # of vertices
    uint32_t m_uiM;  // the # of edges
    uint32_t m_uiTS=0; // start timestamps
    uint32_t m_uiTE=0; // end timestamps

    void getEdges(uint32_t uiTS, uint32_t uiTE, vector<pair<uint32_t, uint32_t>> &vDesEdges);

    // 插入边
    void InsertEdge_Graph(vector<pair<uint32_t, uint32_t>> &vWEdges,int max_number);

    // 删除边
    void DeleteEdge_Graph(vector<pair<uint32_t, uint32_t>> &vWEdges);

    void readFromFile(const char *pcFile);

    void writeToFile(char *pcFile, vector<pair<uint32_t, uint32_t>> &vEdges) const;

    int getMax(uint32_t uiTS, uint32_t uiTE);
};

#endif