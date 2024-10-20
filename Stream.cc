#include "Stream.h"

void Stream::getEdges(uint32_t uiTS, uint32_t uiTE, vector<pair<uint32_t, uint32_t>> &vDesEdges)
{
    vector<ArrayEntry>::iterator itLowB;
    vector<ArrayEntry>::iterator itUpB;

    ASSERT_STREAM(uiTS <= uiTE);
    itLowB = upper_bound(m_vE.begin(), m_vE.end(), (ArrayEntry){uiTS, 0, 0}, cmp);
    itUpB = upper_bound(m_vE.begin(), m_vE.end(), (ArrayEntry){uiTE + 1, 0, 0}, cmp);

    while (itLowB != itUpB)
    {
        vDesEdges.push_back({itLowB->x, itLowB->y});
        ++itLowB;
    }
}

int Stream::getMax(uint32_t uiTS, uint32_t uiTE)
{
    uint32_t max = 0;
    vector<ArrayEntry>::iterator itLowB;
    vector<ArrayEntry>::iterator itUpB;

    ASSERT_STREAM(uiTS <= uiTE);
    itLowB = upper_bound(m_vE.begin(), m_vE.end(), (ArrayEntry){uiTS, 0, 0}, cmp);
    itUpB = upper_bound(m_vE.begin(), m_vE.end(), (ArrayEntry){uiTE + 1, 0, 0}, cmp);

    while (itLowB != itUpB)
    {
        if ((itLowB->x) > max)
        {
            max = itLowB->x;
        }
        if ((itLowB->y) > max)
        {
            max = itLowB->y;
        }
        ++itLowB;
    }

    return max + 1;
}

// 插入边
void Stream::InsertEdge_Graph(vector<pair<uint32_t, uint32_t>> &vWEdges, int max_number)
{
    srand(time(NULL));
    for (auto edge_pair : vWEdges)
    {
        edge[edge_pair.first].push_back(edge_pair.second);
        edge[edge_pair.second].push_back(edge_pair.first);
        node[edge_pair.first].degree++;
        node[edge_pair.second].degree++;
    }
    for (int i = 0; i <= max_number; i++)
        save[i] = node[i];
}

// 删除边
void Stream::DeleteEdge_Graph(vector<pair<uint32_t, uint32_t>> &vWEdges)
{
    for (auto edge_pair : vWEdges)
    {
        edge[edge_pair.first].erase(std::remove(edge[edge_pair.first].begin(), edge[edge_pair.first].end(), edge_pair.second), edge[edge_pair.first].end());
        edge[edge_pair.second].erase(std::remove(edge[edge_pair.second].begin(), edge[edge_pair.second].end(), edge_pair.first), edge[edge_pair.second].end());
    }
}

void Stream::readFromFile(const char *pcFile)
{
    FILE *fp = fopen(pcFile, "rt");
    char acBuffer[100];
    ASSERT_MSG(NULL != fp, "invalid graph file");
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t t = 0;
    m_uiN = 0;
    m_uiM = 0;
    bool bFirst = true;
    while (!feof(fp))
    {
        char *pPos = fgets(acBuffer, 100, fp);
        if (NULL == pPos)
        {
            break;
        }

        int res = sscanf(acBuffer, "%d%d%d", &x, &y, &t);
        ASSERT_MSG(3 == res, "wrong file");

        // m_mpE[t].push_back({x, y});
        if (x != y)
        {
            m_vE.push_back({t, x, y});

            ++m_uiM;
            m_uiN = (m_uiN > x) ? m_uiN : x;
            m_uiN = (m_uiN > y) ? m_uiN : y;
            if (bFirst)
            {
                bFirst = false;
                m_uiTS = t;
            }
            else
            {
                m_uiTS = (m_uiTS < t) ? m_uiTS : t;
            }

            m_uiTE = (m_uiTE > t) ? m_uiTE : t;
            ASSERT_MSG(x != y, "loops exist in the graph" << x << y);
        }
    }
    fclose(fp);
    std::sort(m_vE.begin(), m_vE.end(), cmp);
}

void Stream::writeToFile(char *pcFile, vector<pair<uint32_t, uint32_t>> &vEdges) const
{
    FILE *fp = fopen(pcFile, "w+");
    ASSERT_MSG(NULL != fp, "invalid output file");
    for (const auto atE : vEdges)
    {
        fprintf(fp, "%d %d\n", atE.first, atE.second);
    }
    fclose(fp);
}