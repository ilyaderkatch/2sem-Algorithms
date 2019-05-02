#include "MinWay.h"
#include "test.h"
#include <fstream>

using std::ofstream;
ofstream fout;

int main()
{
    fout.open("output.txt");
    fout << "TEST LOG" << endl;
    fout.close();
    cout << "enter the boundaries of the number of vertices of the graph" << endl;

    int min_vertex, max_vertex;
    cin >> min_vertex >> max_vertex; //границы колва вершин
    int test_count = 10; //колво тестов
    int num_test = 0;
    while(min_vertex < max_vertex)
    {
        double standard_deviation = 0;
        double mean_value = 0;
        for (int i = 0; i < test_count; ++i)
        {
            ++num_test;
            MatrixGraph G = Generate(min_vertex);
            double correct_ans = CorrectMinCycle(G);
            double ans = MinCycle(G);
            standard_deviation += (ans - correct_ans) * (ans - correct_ans); //абсолютная погрешность
            mean_value += ans / correct_ans; //относительная погрешность

            //логирование
            fout.open("output.txt", ios::app);
            fout << "----------------TEST " << num_test << "----------------" << endl;
            fout.close();
            G.Foutput("output.txt");
            fout.open("output.txt", ios::app);
            fout << "correct ans: " << correct_ans << " program ans: " << ans << endl;
            fout << endl;
            fout.close();
        }
        cout << "Quantity of vertices = " << min_vertex << endl;
        cout << "Standard deviation = " << sqrt(standard_deviation / test_count) << endl; //средняя абсолютная, для информативности
        cout << "Mean relative deviation = " << mean_value / test_count << endl; //средняя относитеьная, должна быть меньше 2
        cout << endl;
        ++min_vertex;
    }
    return 0;
}
