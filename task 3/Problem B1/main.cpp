#include "MST.h"
#include <random>
#include <ctime>

using std::random_device;
using std::mt19937;
using std::normal_distribution;

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

int main()
{
    cout << "enter the boundaries of the number of vertices of the graph" << endl;
    int min_vertex, max_vertex;
    cin >> min_vertex >> max_vertex; //границы колва вершин
    int test_count = 10; //колво тестов
    while(min_vertex < max_vertex)
    {
        double standard_deviation = 0;
        double mean_value = 0;
        for (int i = 0; i < test_count; ++i)
        {
            MatrixGraph G = Generate(min_vertex);
            double correct_ans = CorrectMinCycle(G);
            double ans = MinCycle(G);
            standard_deviation += (ans - correct_ans) * (ans - correct_ans); //абсолютная погрешность
            mean_value += ans / correct_ans; //относительная погрешность
        }
        cout << "Quantity of vertices = " << min_vertex << endl;
        cout << "Standard deviation = " << sqrt(standard_deviation / test_count) << endl; //средняя абсолютная, для информативности
        cout << "Mean relative deviation = " << mean_value / test_count << endl; //средняя относитеьная, должна быть меньше 2
        cout << endl;
        ++min_vertex;
    }
    return 0;
}