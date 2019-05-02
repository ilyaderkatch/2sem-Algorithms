#include "MST.h"

ListGraph Prim(const MatrixGraph &A)      //находим мин остов
{
    ListGraph result(A.VerticesCount());
    vector <bool> IsVisited(A.VerticesCount(), false);
    set <Edge> NotVisitedPairs;
    NotVisitedPairs.insert(Edge(0, 0, 0));
    while (NotVisitedPairs.size() != 0)
    {
        Edge NewVertex = *NotVisitedPairs.begin();
        NotVisitedPairs.erase(NotVisitedPairs.begin());
        while (IsVisited[NewVertex.to] == true && NotVisitedPairs.size() != 0)
        {
            NewVertex = *NotVisitedPairs.begin();
            NotVisitedPairs.erase(NotVisitedPairs.begin());
        }
        if (IsVisited[NewVertex.to] == false)
        {
            IsVisited[NewVertex.to] = true;
            result.AddEdge(NewVertex.from, NewVertex.to, NewVertex.weight);
            vector <Edge> Children;
            A.GetNextVertices(NewVertex.to, Children);
            for (int i = 0; i < Children.size(); ++i)
            {
                if (!IsVisited[Children[i].to])
                {
                    NotVisitedPairs.insert(Children[i]);
                }
            }
        }

    }
    return result;
}
