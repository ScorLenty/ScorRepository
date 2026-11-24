#include <iostream>
#include <vector>
#include <algorithm>
#include <clocale>

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");

    int n, m;
    // Считываем размеры поля (N строк, M столбцов)
    if (!(cin >> n >> m) || n <= 0 || m <= 0) {
        return 0;
    }

    // Исходная матрица с баллами
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    // Таблица для хранения максимальной суммы баллов до каждой клетки
    vector<vector<long long>> dp(n, vector<long long>(m, 0));

    // Базовый случай: стартовая клетка (0, 0)
    dp[0][0] = grid[0][0];

    // Заполняем первый столбец (двигаться можно только сверху)
    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    // Заполняем первую строку (двигаться можно только слева)
    for (int j = 1; j < m; ++j) {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    // Заполняем остальную часть таблицы
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            // Выбираем, откуда выгоднее прийти: сверху (i-1, j) или слева (i, j-1)
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }

    // Восстанавливаем путь от финиша (n-1, m-1) к старту (0, 0)
    vector<pair<int, int>> path;
    int r = n - 1;
    int c = m - 1;

    while (r > 0 || c > 0) {
        path.push_back({ r, c });
        if (r == 0) {
            // Если мы на верхней границе, могли прийти только слева
            c--;
        }
        else if (c == 0) {
            // Если мы на левой границе, могли прийти только сверху
            r--;
        }
        else {
            // Иначе идем туда, где накопленная сумма была больше
            if (dp[r - 1][c] > dp[r][c - 1]) {
                r--;
            }
            else {
                c--;
            }
        }
    }
    // Добавляем стартовую точку
    path.push_back({ 0, 0 });

    // Разворачиваем путь, так как собирали его с конца
    reverse(path.begin(), path.end());

    // Выводим результат
    for (const auto& cell : path) {
        cout << cell.first << " " << cell.second << "\n";
    }

    return 0;
}
