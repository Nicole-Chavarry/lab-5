#include <iostream>
#include <fstream>
#include <vector>

struct Matrix {
    int rows;
    int cols;
    std::vector<std::vector<int>> data;
};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << matrix.rows << " " << matrix.cols << std::endl;
    for (const auto& row : matrix.data) {
        for (int val : row) {
            os << val << " ";
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix) {
    int rows, cols;
    is >> rows >> cols;
    matrix.data.resize(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            is >> matrix.data[i][j];
        }
    }
    return is;
}

void writeMatricesToFile(const std::string& filename, const std::vector<Matrix>& matrices) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const Matrix& matrix : matrices) {
        file << matrix << std::endl;
    }

    file.close();
}

std::vector<Matrix> readMatricesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }

    std::vector<Matrix> matrices;
    Matrix matrix;
    while (file >> matrix) {
        matrices.push_back(matrix);
    }

    file.close();
    return matrices;
}

int main() {
    std::vector<Matrix> matrices = {
        {{3, 3}, {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        }},
        {{2, 2}, {
            {10, 20},
            {30, 40}
        }}
    };

    std::string filename = "Matriz.txt";
    writeMatricesToFile(filename, matrices);

    std::vector<Matrix> readMatrices = readMatricesFromFile(filename);
    if (!readMatrices.empty()) {
        std::cout << "Read matrices from file:" << std::endl;
        for (const Matrix& matrix : readMatrices) {
            std::cout << matrix << std::endl;
        }
    }

    return 0;
}