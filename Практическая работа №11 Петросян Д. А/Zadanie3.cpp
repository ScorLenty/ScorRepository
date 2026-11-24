#include <iostream>
#include <vector>
#include <algorithm>
#include <clocale>

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");

    int n, k, l;
    if (!(cin >> n >> k >> l)) {
        return 0;
    }

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Проверяем, хватит ли вообще растений для букета размера K
    if (1LL * n * l < k) {
        cout << -1 << "\n";
        return 0;
    }

    // Сортируем стоимости растений по убыванию
    sort(a.rbegin(), a.rend());

    long long total_cost = 0;
    int remaining = k; // Сколько растений еще нужно добавить в букет

    for (int i = 0; i < n && remaining > 0; ++i) {
        // Берем либо максимально разрешенное количество L, либо столько, сколько осталось до K
        int take = min(l, remaining);
        total_cost += 1LL * take * a[i];
        remaining -= take;
    }

    cout << total_cost << "\n";

    return 0;
}
