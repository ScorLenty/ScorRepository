#include <iostream>
#include <vector>
#include <algorithm>
#include <clocale>

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");

    int n, d;
    if (!(cin >> n >> d) || n <= 0 || d <= 0 || d > n) {
        return 0;
    }

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Сортируем калорийности пирожков по возрастанию
    sort(a.begin(), a.end());

    const long long INF = 4e18;
    // dp[k][i] — минимально возможная максимальная разница при распределении
    // первых i пирожков по k дням
    vector<vector<long long>> dp(d + 1, vector<long long>(n + 1, INF));

    // Базовый случай: 1 день (все первые i пирожков съедаются в один день)
    for (int i = 1; i <= n; ++i) {
        dp[1][i] = a[i - 1] - a[0];
    }

    // Заполняем таблицу для количества дней от 2 до D
    for (int k = 2; k <= d; ++k) {
        // Чтобы хватило минимум по 1 пирожку на каждый из k дней, i должно быть >= k
        for (int i = k; i <= n; ++i) {
            // Перебираем границу j: первые j пирожков идут в предыдущие (k - 1) дней,
            // а пирожки с (j + 1)-го по i-й съедаются в k-й день
            for (int j = k - 1; j < i; ++j) {
                long long current_diff = a[i - 1] - a[j];
                long long worst_diff = max(dp[k - 1][j], current_diff);
                dp[k][i] = min(dp[k][i], worst_diff);
            }
        }
    }

    cout << dp[d][n] << "\n";

    return 0;
}
