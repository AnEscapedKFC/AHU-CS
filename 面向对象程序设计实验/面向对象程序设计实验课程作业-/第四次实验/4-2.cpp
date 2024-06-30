#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
    vector<vector<int>> data;
    int rows;
    int cols;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data.resize(r, vector<int>(c));
    }

    void input() {
        cout << "请输入一个 " << rows << "*" << cols << " 的矩阵：" << endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                cin >> data[i][j];
    }

    void display() const {
        cout << "矩阵为：" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                cout << data[i][j] << " ";
            cout << endl;
        }
    }

    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[j][i] = data[i][j];
        return result;
    }
};

int main() {
    int rows, cols;
    cout << "请输入矩阵的行数和列数：" << endl;
    cin >> rows >> cols;

    Matrix matrix(rows, cols);

    matrix.input();
    cout << "输入的矩阵：" << endl;
    matrix.display();

    Matrix transposedMatrix = matrix.transpose();
    cout << "转置后的矩阵：" << endl;
    transposedMatrix.display();

    return 0;
}