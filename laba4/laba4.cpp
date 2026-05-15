#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// Уравнение: x * ln(x+1) - 1 = 0 
auto f = [](double x) { return x * log(x + 1) - 1.0; };
auto df = [](double x) { return log(x + 1) + x / (x + 1); };
auto phi = [](double x) { return 1.0 / log(x + 1); }; // x = 1/ln(x+1)

void print_table_header(const string& method) {
    cout << "\n=== " << method << " ===\n";
    cout << "n\txn\t\txn+1\t\t|xn+1 - xn|\n";
}

void bisection(double a, double b, double eps) {
    cout << "\n=== Метод половинного деления ===\n";
    cout << "an\t\tbn\t\t(bn-an)\n";
    
    vector<pair<double, double>> intervals;
    while ((b - a) > eps) {
        intervals.push_back({a, b});
        double c = (a + b) / 2;
        (f(a) * f(c) < 0) ? b = c : a = c;
    }
    
    for (auto [l, r] : intervals) 
        cout << fixed << setprecision(6) << l << "\t" << r << "\t" << (r - l) << "\n";
    
    cout << "\nКорень: " << (a + b) / 2 << "\nИтераций: " << intervals.size() << "\n";
}

void newton(double x0, double eps) {
    print_table_header("Метод Ньютона");
    
    vector<tuple<int, double, double, double>> iter;
    int n = 0;
    double x = x0;
    
    while (true) {
        double x_next = x - f(x) / df(x);
        iter.push_back({n, x, x_next, fabs(x_next - x)});
        if (fabs(x_next - x) < eps) break;
        x = x_next;
        n++;
    }
    
    for (auto [i, xn, xnp1, diff] : iter)
        cout << i << "\t" << fixed << setprecision(6) << xn << "\t" << xnp1 << "\t" << diff << "\n";
    
    cout << "\nКорень: " << get<2>(iter.back()) << "\nИтераций: " << iter.size() << "\n";
}

void fixed_point(double x0, double eps) {
    print_table_header("Метод простых итераций");
    
    vector<tuple<int, double, double, double>> iter;
    int n = 0;
    double x = x0;
    
    while (true) {
        double x_next = phi(x);
        iter.push_back({n, x, x_next, fabs(x_next - x)});
        if (fabs(x_next - x) < eps) break;
        x = x_next;
        n++;
    }
    
    for (auto [i, xn, xnp1, diff] : iter)
        cout << i << "\t" << fixed << setprecision(6) << xn << "\t" << xnp1 << "\t" << diff << "\n";
    
    cout << "\nКорень: " << get<2>(iter.back()) << "\nИтераций: " << iter.size() << "\n";
}

int main() {
    cout << "Уравнение: x * ln(x+1) - 1 = 0\nИнтервал: [1, 2]\nТочность: 1e-4\n";
    
    bisection(1.0, 2.0, 1e-4);
    newton(1.5, 1e-4);
    fixed_point(1.5, 1e-4);
    
    return 0;
}
