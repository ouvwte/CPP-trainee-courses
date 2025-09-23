/*Описать класс, реализующий тип данных «вещественная матрица» и работу с ними.
Класс должен реализовывать следующие операции над матрицами :
• сложение, вычитание(как с другой матрицей, так и с числом);
• комбинированные операции присваивания(+=, -= );
• операции сравнения на равенство / неравенство;
• операции вычисления обратной и транспонированной матрицы;
• доступ к элементу по индексам.
Написать программу, демонстрирующую все разработанные элементы класса.
*/

#include <iostream>
#include <vector>

    class RealMatrix {
    private:
        std::vector<std::vector<double>> m_data;
        size_t m_rows, m_cols;

    public:
        // Default constructor
        RealMatrix() : m_rows(0), m_cols(0) {}

        // Constructor with dimensions and default value
        RealMatrix(size_t rows, size_t cols, double value = 0) : m_rows(rows), m_cols(cols) {
            m_data.resize(rows, std::vector<double>(cols, value));
        }

        // Copy constructor
        RealMatrix(const RealMatrix& other) : m_rows(other.m_rows), m_cols(other.m_cols),
            m_data(other.m_data) {}

        // Move constructor
        RealMatrix(RealMatrix&& other) : m_rows(other.m_rows), m_cols(other.m_cols),
            m_data(std::move(other.m_data)) {}

        // Addition operator (matrix)
        RealMatrix operator +(const RealMatrix& rhs) const {
            if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
                throw std::invalid_argument("Matrix dimensions do not match.");
            }
            RealMatrix result(m_rows, m_cols);
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    result.m_data[i][j] = m_data[i][j] + rhs.m_data[i][j];
                }
            }
            return result;
        }

        // Subtraction operator (matrix)
        RealMatrix operator -(const RealMatrix& rhs) const {
            if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
                throw std::invalid_argument("Matrix dimensions do not match.");
            }
            RealMatrix result(m_rows, m_cols);
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    result.m_data[i][j] = m_data[i][j] - rhs.m_data[i][j];
                }
            }
            return result;
        }

        // Addition operator (scalar)
        RealMatrix operator +(const double& scalar) const {
            RealMatrix result(m_rows, m_cols);
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    result.m_data[i][j] = m_data[i][j] + scalar;
                }
            }
            return result;
        }

        // Subtraction operator (scalar)
        RealMatrix operator -(const double& scalar) const {
            RealMatrix result(m_rows, m_cols);
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    result.m_data[i][j] = m_data[i][j] - scalar;
                }
            }
            return result;
        }

        // Combined assignment operator (+=)
        RealMatrix& operator +=(const RealMatrix& rhs) {
            if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
                throw std::invalid_argument("Matrix dimensions do not match.");
            }
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    m_data[i][j] += rhs.m_data[i][j];
                }
            }
            return *this;
        }

        // Combined assignment operator (-=)
        RealMatrix& operator -=(const RealMatrix& rhs) {
            if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
                throw std::invalid_argument("Matrix dimensions do not match.");
            }
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    m_data[i][j] -= rhs.m_data[i][j];
                }
            }
            return *this;
        }

        // Comparison operator (equality)
        bool operator ==(const RealMatrix& rhs) const {
            if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
                return false;
            }
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    if (m_data[i][j] != rhs.m_data[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        // Comparison operator (inequality)
        bool operator !=(const RealMatrix& rhs) const {
            return !(*this == rhs);
        }

        // Inverse matrix
        RealMatrix inverse() const {
            if (m_rows != m_cols) {
                    throw std::invalid_argument("Matrix must be square.");
            }
            RealMatrix result(m_rows, m_cols);
            // code to calculate inverse goes here
            return result;
        }

        // Transposed matrix
        RealMatrix transpose() const {
            RealMatrix result(m_cols, m_rows);
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    result.m_data[j][i] = m_data[i][j];
                }
            }
            return result;
        }

        // Access operator
        double& operator ()(size_t row, size_t col) {
            if (row >= m_rows || col >= m_cols) {
                throw std::out_of_range("Index out of range.");
            }
            return m_data[row][col];
        }

        // Constant access operator
        const double& operator ()(size_t row, size_t col) const {
            if (row >= m_rows || col >= m_cols) {
                throw std::out_of_range("Index out of range.");
            }
            return m_data[row][col];
        }

        // Print matrix
        void print() const {
            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    std::cout << m_data[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
};

// Example program
int main() {
    RealMatrix mat1(3, 3, 1);
    RealMatrix mat2(3, 3, 2);

    std::cout << "Matrix 1:" << std::endl;
    mat1.print();

    std::cout << "Matrix 2:" << std::endl;
    mat2.print();

    std::cout << "Matrix 1 + Matrix 2:" << std::endl;
    RealMatrix mat3 = mat1 + mat2;
    mat3.print();

    std::cout << "Matrix 1 - Matrix 2:" << std::endl;
    RealMatrix mat4 = mat1 - mat2;
    mat4.print();

    std::cout << "Matrix 1 + 2.0:" << std::endl;
    RealMatrix mat5 = mat1 + 2.0;
    mat5.print();

    std::cout << "Matrix 1 - 2.0:" << std::endl;
    RealMatrix mat6 = mat1 - 2.0;
    mat6.print();

    std::cout << "Matrix 1 += Matrix 2:" << std::endl;
    mat1 += mat2;
    mat1.print();

    std::cout << "Matrix 1 -= Matrix 2:" << std::endl;
    mat1 -= mat2;
    mat1.print();

    std::cout << "Matrix 1 == Matrix 2:" << std::endl;
    if (mat1 == mat2) {
        std::cout << "true" << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }

    std::cout << "Matrix 1 != Matrix 2:" << std::endl;
    if (mat1 != mat2) {
        std::cout << "true" << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }

    std::cout << "Matrix 1 transposed:" << std::endl;
    RealMatrix mat7 = mat1.transpose();
    mat7.print();

    std::cout << "Matrix 1 inverse:" << std::endl;
    try {
        RealMatrix mat8 = mat1.inverse();
        mat8.print();
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "Element (0,0) of Matrix 1: " << mat1(0, 0) << std::endl;
}