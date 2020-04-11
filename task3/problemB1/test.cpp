#include "test.h"

MatrixGraph Generate(int vertices_count) {   //генерируем точки на плоскости, вводим их в наш граф
    MatrixGraph A(vertices_count);
    random_device rd{};
    mt19937 gen{rd()};
    normal_distribution <double> Distribution(0.0, 1);
    vector<pair <double, double> > Points;
    for (int i = 0; i < vertices_count; ++i) {   //генрируем
        double x = Distribution(gen);
        double y = Distribution(gen);
        Points.push_back({x, y});
    }
    for (int i = 0; i < vertices_count; ++i) {            //вводим
        for (int j = i + 1; j < vertices_count; ++j) {
            double x1 = Points[i].first - Points[j].first;
            double y1 = Points[i].second - Points[j].second;
            double weight = sqrt(x1 * x1 + y1 * y1);
            A.AddEdge(i, j, weight);
        }
    }
    return A;
}