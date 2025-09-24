#include <iostream>
#include <vector>

using namespace std;

class RealMatrix {
public:
    RealMatrix(int rows, int cols);
    RealMatrix(const RealMatrix& other);
    ~RealMatrix();

    RealMatrix operator+(const RealMatrix& other) const;
    RealMatrix operator-(const RealMatrix& other) const;
    RealMatrix operator+(double scalar) const;
    RealMatrix operator-(double scalar) const;
    RealMatrix& operator+=(const RealMatrix& other);
    RealMatrix& operator-=(const RealMatrix& other);
    RealMatrix& operator+=(double scalar);
    RealMatrix& operator-=(double scalar);
    RealMatrix operator*(const RealMatrix& other) const;
    RealMatrix operator*(double scalar) const;
    bool operator==(const RealMatrix& other) const;
    bool operator!=(const RealMatrix& other) const;
    RealMatrix& operator=(const RealMatrix& other);
    double& operator()(int row, int col);
    double operator()(int row, int col) const;
    RealMatrix inverse() const;
    RealMatrix transpose() const;

private:
    vector<vector<double>> data;
    int rows;
    int cols;
};

RealMatrix::RealMatrix(int rows, int cols) : rows(rows), cols(cols)
{
    data.resize(rows, vector<double>(cols, 0.0));
}

RealMatrix::RealMatrix(const RealMatrix& other) : rows(other.rows), cols(other.cols)
{
    data = other.data;
}

RealMatrix::~RealMatrix()
{
}

RealMatrix RealMatrix::operator+(const RealMatrix& other) const
{
    RealMatrix result(rows, cols);
    if (rows == other.rows && cols == other.cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result(i, j) = (*this)(i, j) + other(i, j);
            }
        }
    }
    return result;
}

RealMatrix RealMatrix::operator-(const RealMatrix& other) const
{
    RealMatrix result(rows, cols);
    if (rows == other.rows && cols == other.cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result(i, j) = (*this)(i, j) - other(i, j);
            }
        }
    }
    return result;
}

RealMatrix RealMatrix::operator+(double scalar) const
{
    RealMatrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = (*this)(i, j) + scalar;
        }
    }
    return result;
}

RealMatrix RealMatrix::operator-(double scalar) const
{
    RealMatrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = (*this)(i, j) - scalar;
        }
    }
    return result;
}

RealMatrix& RealMatrix::operator+=(const RealMatrix& other)
{
    if (rows == other.rows && cols == other.cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                (*this)(i, j) += other(i, j);
            }
        }
    }
    return *this;
}

RealMatrix& RealMatrix::operator-=(const RealMatrix& other)
{
    if (rows == other.rows && cols == other.cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                (*this)(i, j) -= other(i, j);
            }
        }
    }
    return *this;
}

RealMatrix& RealMatrix::operator+=(double scalar)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            (*this)(i, j) += scalar;
        }
    }
    return *this;
}

RealMatrix& RealMatrix::operator-=(double scalar)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            (*this)(i, j) -= scalar;
        }
    }
    return *this;
}

RealMatrix RealMatrix::operator*(const RealMatrix& other) const
{
    RealMatrix result(rows, other.cols);
    if (cols == other.rows) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
    }
    return result;
}

RealMatrix RealMatrix::operator*(double scalar) const
{
    RealMatrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = (*this)(i, j) * scalar;
        }
    }
    return result;
}

bool RealMatrix::operator==(const RealMatrix& other) const
{
    if (rows == other.rows && cols == other.cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if ((*this)(i, j) != other(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool RealMatrix::operator!=(const RealMatrix& other) const
{
    return !(*this == other);
}

RealMatrix& RealMatrix::operator=(const RealMatrix& other)
{
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = other.data;
    }
    return *this;
}

double& RealMatrix::operator()(int row, int col)
{
    return data[row][col];
}

double RealMatrix::operator()(int row, int col) const
{
    return data[row][col];
}

RealMatrix RealMatrix::inverse() const {
    RealMatrix result(rows, cols);
    if (rows == cols) {
        double determinant = 0.0;
        // calculate determinant
        for (int i = 0; i < rows; ++i) {
            RealMatrix minor(rows - 1, cols - 1);
            for (int j = 0; j < rows - 1; ++j) {
                for (int k = 0; k < cols - 1; ++k) {
                    if (k < i) {
                        minor(j, k) = (*this)(j + 1, k);
                    }
                    else {
                        minor(j, k) = (*this)(j + 1, k + 1);
                    }
                }
            }
            double cofactor = minor.inverse()(0, 0);
            if (i % 2 == 0) {
                determinant += (*this)(0, i) * cofactor;
            }
            else {
                determinant -= (*this)(0, i) * cofactor;
            }
        }
        // calculate adjugate matrix
        RealMatrix adjugate(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                RealMatrix minor(rows - 1, cols - 1);
                for (int k = 0; k < rows - 1; ++k) {
                    for (int l = 0; l < cols - 1; ++l) {
                        if (k < i && l < j) {
                            minor(k, l) = (*this)(k, l);
                        }
                        else if (k < i && l >= j) {
                            minor(k, l) = (*this)(k, l + 1);
                        }
                        else if (k >= i && l < j) {
                            minor(k, l) = (*this)(k + 1, l);
                        }
                        else {
                            minor(k, l) = (*this)(k + 1, l + 1);
                        }
                    }
                }
                double cofactor = minor.inverse()(0, 0);
                if ((i + j) % 2 == 0) {
                    adjugate(i, j) = cofactor;
                }
                else {
                    adjugate(i, j) = -cofactor;
                }
            }
        }
        // calculate inverse matrix
        result = adjugate * (1.0 / determinant);
    }
    return result;
}

RealMatrix RealMatrix::transpose() const {
    RealMatrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

int main() {
    // create a 2x3 matrix with initial values
    RealMatrix matrix(2, 3);
    matrix(0, 0) = 1.0;
    matrix(0, 1) = 2.0;
    matrix(0, 2) = 3.0;
    matrix(1, 0) = 4.0;
    matrix(1, 1) = 5.0;
    matrix(1, 2) = 6.0;

    // create a 3x2 matrix with initial values
    RealMatrix other(3, 2);
    other(0, 0) = 7.0;
    other(0, 1) = 8.0;
    other(1, 0) = 9.0;
    other(1, 1) = 10.0;
    other(2, 0) = 11.0;
    other(2, 1) = 12.0;

    // test addition and subtraction
    RealMatrix result = matrix + other;
    result = result - other;
    result += matrix;
    result -= matrix;

    // test scalar addition and subtraction
    result = matrix + 2.0;
    result = result - 1.0;
    result += 2.0;
    result -= 1.0;
    // test multiplication
    result = matrix * other.transpose();

    // test comparison
    if (matrix == other) {
        cerr << "Error: matrices are equal." << endl;
    }

    // test access
    double value = matrix(0, 0);
    matrix(0, 0) = value + 1.0;

    // test assignment
    RealMatrix copy = matrix;
    copy(0, 0) = 0.0;
    if (copy == matrix) {
        cerr << "Error: matrices should be different." << endl;
    }

    // test inverse
    RealMatrix singular(2, 2);
    singular(0, 0) = 1.0;
    singular(0, 1) = 1.0;
    singular(1, 0) = 1.0;
    singular(1, 1) = 1.0;
    result = singular.inverse();

    // test transpose
    result = matrix.transpose();

    return 0;
}