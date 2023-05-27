#include <bits/stdc++.h>
using namespace std;

pair<int, int> MOVES[] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};

int countNeighbours(vector<vector<char>> &grid, pair<int, int> v)
{
    int res = 0;
    for (auto move : MOVES)
    {
        int y = v.first + move.first;
        int x = v.second + move.second;
        if (x == -1 || y == -1 || x == grid[0].size() || y == grid.size())
            continue;
        if (grid[y][x] == 'x')
            res++;
    }
    return res;
}

int countAllNeighbours(vector<vector<char>> &grid, vector<vector<bool>> &toUpdate)
{
    int entities = 0;
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            int neighbours = countNeighbours(grid, {i, j});
            if (grid[i][j] == '.')
            {
                if (neighbours == 3)
                    toUpdate[i][j] = true;
            }
            else
            {
                entities += 1;
                if (neighbours < 2 || neighbours > 3)
                    toUpdate[i][j] = true;
            }
        }
    }
    return entities;
}

void updateGrid(vector<vector<char>> &grid, vector<vector<bool>> &toUpdate)
{
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            if (toUpdate[i][j])
            {
                if (grid[i][j] == '.')
                    grid[i][j] = 'x';
                else
                    grid[i][j] = '.';
                toUpdate[i][j] = false;
            }
        }
    }
}

void printGrid(vector<vector<char>> &grid)
{
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

int main()
{
    fstream file;
    file.open("grid.txt");

    vector<vector<bool>> toUpdate;

    string line;
    while (file >> line)
    {
        vector<bool> row;
        for (char c : line)
        {
            if (c == '1')
                row.push_back(true);
            else
                row.push_back(false);
        }
        toUpdate.push_back(row);
    }
    vector<vector<char>> grid(toUpdate.size(), vector<char>(toUpdate[0].size(), '.'));

    do
    {
        updateGrid(grid, toUpdate);
        printGrid(grid);
        this_thread::sleep_for(chrono::milliseconds(1000));

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

    } while (countAllNeighbours(grid, toUpdate));

    file.close();
    return 0;
}
