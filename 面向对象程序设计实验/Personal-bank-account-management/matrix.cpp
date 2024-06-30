#include <iostream>
#include <vector>
#include <initializer_list>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Matrix;

class MatrixIndex {
private:
    const Matrix& source;
    const Matrix& rows;
    const Matrix& columns;

public:
    MatrixIndex(const Matrix& source, const Matrix& rows, const Matrix& columns);
    MatrixIndex& operator=(const Matrix& m1);
    MatrixIndex& operator=(double a);
    MatrixIndex& operator=(std::initializer_list<double> vector);
    friend class Matrix;
};

class Matrix {
private:
    int nRow;
    int nColumn;
    vector<double> data;

public:
    Matrix(int x, int y);
    Matrix(int x, int y, const char* type);
    Matrix(const Matrix& m1);
    Matrix(std::initializer_list<double> vector);
    Matrix(const MatrixIndex& index);
    ~Matrix() = default;

    MatrixIndex operator()(const Matrix& m1, const Matrix& m2);
    Matrix& operator=(const Matrix& m1);
    Matrix& operator=(double a);
    Matrix& operator=(std::initializer_list<double> vector);
    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    friend Matrix operator-(const Matrix& m1, const Matrix& m2);
    friend Matrix operator*(const Matrix& m1, const Matrix& m2);
    friend ostream& operator<<(ostream& out, const Matrix& m1);
    friend class MatrixIndex;
};

Matrix::Matrix(int x, int y) : nRow(x), nColumn(y), data(x * y, 0) {}

Matrix::Matrix(int x, int y, const char* type) : nRow(x), nColumn(y), data(x * y) {
    if (strcmp(type, "zero") == 0) {
        fill(data.begin(), data.end(), 0);
    } else if (strcmp(type, "one") == 0) {
        fill(data.begin(), data.end(), 1);
    } else if (strcmp(type, "rand") == 0) {
        srand((unsigned)time(0));
        generate(data.begin(), data.end(), []() { return rand() % 100; });
    } else {
        throw invalid_argument("无效的类型");
    }
}

Matrix::Matrix(const Matrix& m1) : nRow(m1.nRow), nColumn(m1.nColumn), data(m1.data) {}

Matrix::Matrix(std::initializer_list<double> vector) : nRow(1), nColumn(vector.size()), data(vector) {}

Matrix::Matrix(const MatrixIndex& index) : nRow(index.rows.nColumn), nColumn(index.columns.nColumn), data(nRow * nColumn) {
    for (int i = 0; i < nRow; ++i) {
        for (int j = 0; j < nColumn; ++j) {
            data[i * nColumn + j] = index.source.data[index.source.nColumn * index.rows.data[i] + index.columns.data[j]];
        }
    }
}

MatrixIndex Matrix::operator()(const Matrix& m1, const Matrix& m2) {
    return MatrixIndex(*this, m1, m2);
}

Matrix& Matrix::operator=(const Matrix& m1) {
    if (this != &m1) {
        nRow = m1.nRow;
        nColumn = m1.nColumn;
        data = m1.data;
    }
    return *this;
}

Matrix& Matrix::operator=(double a) {
    fill(data.begin(), data.end(), a);
    return *this;
}

Matrix& Matrix::operator=(std::initializer_list<double> vector) {
    if (vector.size() != data.size()) {
        throw invalid_argument("尺寸不匹配");
    }
    copy(vector.begin(), vector.end(), data.begin());
    return *this;
}

Matrix operator+(const Matrix& m1, const Matrix& m2) {
    if (m1.nRow != m2.nRow || m1.nColumn != m2.nColumn) {
        throw invalid_argument("矩阵必须具有相同的维度");
    }
    Matrix result(m1.nRow, m1.nColumn);
    for (size_t i = 0; i < m1.data.size(); ++i) {
        result.data[i] = m1.data[i] + m2.data[i];
    }
    return result;
}

Matrix operator-(const Matrix& m1, const Matrix& m2) {
    if (m1.nRow != m2.nRow || m1.nColumn != m2.nColumn) {
        throw invalid_argument("矩阵必须具有相同的维度");
    }
    Matrix result(m1.nRow, m1.nColumn);
    for (size_t i = 0; i < m1.data.size(); ++i) {
        result.data[i] = m1.data[i] - m2.data[i];
    }
    return result;
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    if (m1.nColumn != m2.nRow) {
        throw invalid_argument("矩阵维度不兼容，无法进行乘法运算");
    }
    Matrix result(m1.nRow, m2.nColumn);
    for (int i = 0; i < m1.nRow; ++i) {
        for (int j = 0; j < m2.nColumn; ++j) {
            result.data[i * m2.nColumn + j] = 0;
            for (int k = 0; k < m1.nColumn; ++k) {
                result.data[i * m2.nColumn + j] += m1.data[i * m1.nColumn + k] * m2.data[k * m2.nColumn + j];
            }
        }
    }
    return result;
}

ostream& operator<<(ostream& out, const Matrix& m1) {
    for (int i = 0; i < m1.nRow; ++i) {
        for (int j = 0; j < m1.nColumn; ++j) {
            out << m1.data[i * m1.nColumn + j] << " ";
        }
        out << endl;
    }
    return out;
}

MatrixIndex::MatrixIndex(const Matrix& source, const Matrix& rows, const Matrix& columns)
        : source(source), rows(rows), columns(columns) {}

MatrixIndex& MatrixIndex::operator=(const Matrix& m1) {
    if (rows.nColumn * columns.nColumn != m1.nRow * m1.nColumn) {
        throw invalid_argument("子矩阵和被赋值矩阵必须具有相同数量的元素");
    }
    for (int i = 0; i < rows.nColumn; ++i) {
        for (int j = 0; j < columns.nColumn; ++j) {
            const_cast<Matrix&>(source).data[source.nColumn * rows.data[i] + columns.data[j]] = m1.data[m1.nColumn * i + j];
        }
    }
    return *this;
}

MatrixIndex& MatrixIndex::operator=(double a) {
    for (int i = 0; i < rows.nColumn; ++i) {
        for (int j = 0; j < columns.nColumn; ++j) {
            const_cast<Matrix&>(source).data[source.nColumn * rows.data[i] + columns.data[j]] = a;
        }
    }
    return *this;
}

MatrixIndex& MatrixIndex::operator=(std::initializer_list<double> vector) {
    if (vector.size() != static_cast<size_t>(rows.nColumn * columns.nColumn)) {
        throw invalid_argument("向量大小必须与子矩阵大小相匹配");
    }
    auto it = vector.begin();
    for (int i = 0; i < rows.nColumn; ++i) {
        for (int j = 0; j < columns.nColumn; ++j) {
            const_cast<Matrix&>(source).data[source.nColumn * rows.data[i] + columns.data[j]] = *it++;
        }
    }
    return *this;
}

int main(int argc, char* argv[]) {
    // 生成元素为10,9,8,7,6,5的1x6矩阵m
    Matrix m({ 10, 9, 8, 7, 6, 5 });

    // 生成元素为4,3,2,1的1x4矩阵p
    Matrix p({ 4, 3, 2, 1 });

    // 生成元素全为零的3x4矩阵k
    Matrix k(3, 4);

    // 将矩阵k的第1行第0,1,2列的数据改为
    // 矩阵m的第0行第0,1,2列元素与矩阵m
    // 的第0行第3,4,5列元素之差
    k({ 1 }, { 0, 1, 2 }) = m({ 0 }, { 0, 1, 2 }) - m({ 0 }, { 3, 4, 5 });

    // 将矩阵k的第2行第x列的数据改为
    // 矩阵m的第0行第0,1,2列元素与矩阵m
    // 的第0行第3,4,5列元素之和
    k({ 2 }, { 0, 1, 2 }) = m({ 0 }, { 0, 1, 2 }) + m({ 0 }, { 3, 4, 5 });

    // 输出矩阵k
    cout << k;

    return 0;
}
