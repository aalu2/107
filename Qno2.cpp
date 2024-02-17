#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>

class CustomMatrix {
private:
    std::vector<std::vector<int>> matrixData;
    bool isMatrixInvalid;

public:
    CustomMatrix(const std::string& matrixString) {
        std::istringstream matrixStream(matrixString);
        char discardCharacter;
        int matrixElement;
        std::vector<int> rowVector;
        while (matrixStream >> discardCharacter) {
            if (discardCharacter == '(') {
                while (matrixStream >> matrixElement) {
                    rowVector.push_back(matrixElement);
                    if (matrixStream.peek() == ',')
                        matrixStream.ignore();
                    else if (matrixStream.peek() == ')') {
                        matrixStream.ignore();
                        break;
                    }
                }
                matrixData.push_back(rowVector);
                rowVector.clear();
            }
        }
        isMatrixInvalid = false;
        int matrixColumns = matrixData[0].size();
        for (size_t i = 1; i < matrixData.size(); ++i) {
            if (matrixData[i].size() != matrixColumns) {
                isMatrixInvalid = true;
                break;
            }
        }
    }

    bool IsMatrixInvalid() const {
        return isMatrixInvalid;
    }

    int& operator()(size_t row, size_t col) {
        return matrixData[row][col];
    }

    std::vector<std::vector<int>> GetMatrixData() const {
        return matrixData;
    }

    CustomMatrix MatrixSum(const CustomMatrix& other) const {
        if (matrixData.size() != other.matrixData.size() || matrixData[0].size() != other.matrixData[0].size())
            throw std::invalid_argument("Matrix dimensions are not compatible for addition.");

        CustomMatrix resultMatrix("(");
        for (size_t i = 0; i < matrixData.size(); ++i) {
            std::vector<int> rowVector;
            for (size_t j = 0; j < matrixData[i].size(); ++j) {
                rowVector.push_back(matrixData[i][j] + other.matrixData[i][j]);
            }
            resultMatrix.matrixData.push_back(rowVector);
        }
        return resultMatrix;
    }

    CustomMatrix MatrixDifference(const CustomMatrix& other) const {
        if (matrixData.size() != other.matrixData.size() || matrixData[0].size() != other.matrixData[0].size())
            throw std::invalid_argument("Matrix dimensions are not compatible for subtraction.");

        CustomMatrix resultMatrix("(");
        for (size_t i = 0; i < matrixData.size(); ++i) {
            std::vector<int> rowVector;
            for (size_t j = 0; j < matrixData[i].size(); ++j) {
                rowVector.push_back(matrixData[i][j] - other.matrixData[i][j]);
            }
            resultMatrix.matrixData.push_back(rowVector);
        }
        return resultMatrix;
    }

    CustomMatrix MatrixProduct(const CustomMatrix& other) const {
        if (matrixData[0].size() != other.matrixData.size())
            throw std::invalid_argument("Matrix dimensions are not compatible for multiplication.");

        CustomMatrix resultMatrix("(");
        for (size_t i = 0; i < matrixData.size(); ++i) {
            std::vector<int> rowVector;
            for (size_t j = 0; j < other.matrixData[0].size(); ++j) {
                int sum = 0;
                for (size_t k = 0; k < other.matrixData.size(); ++k) {
                    sum += matrixData[i][k] * other.matrixData[k][j];
                }
                rowVector.push_back(sum);
            }
            resultMatrix.matrixData.push_back(rowVector);
        }
        return resultMatrix;
    }

    void Display() const {
        for (size_t i = 0; i < matrixData.size(); ++i) {
            std::cout << "(";
            for (size_t j = 0; j < matrixData[i].size(); ++j) {
                std::cout << matrixData[i][j];
                if (j < matrixData[i].size() - 1)
                    std::cout << " ";
            }
            std::cout << ")" << std::endl;
        }
    }
};

int main() {
    try {
        CustomMatrix matrixA("(10,11,16),(18,14,13),(12,17,19)");
        CustomMatrix matrixB("(23,31,19),(21,13,34),(37,23,17)");
        CustomMatrix matrixC("(14,28,32),(48,50),(22,57,1)");
        CustomMatrix matrixD("(54,21,36),(61,69,1),(37,21)");

        std::cout << "Matrix A:" << std::endl;
        matrixA.Display();

        std::cout << "\nMatrix B:" << std::endl;
        matrixB.Display();

        std::cout << "\nMatrix C:" << std::endl;
        matrixC.Display();

        std::cout << "\nMatrix D:" << std::endl;
        matrixD.Display();

        if (matrixA.IsMatrixInvalid() || matrixB.IsMatrixInvalid()) {
            std::cout << "Matrix A and Matrix B are valid." << std::endl;
        } else {
            std::cout << "\nPerforming calculations for Matrix A and Matrix B:" << std::endl;

            CustomMatrix resultSumAB = matrixA.MatrixSum(matrixB);
            std::cout << "\nMatrix Addition Result (A + B):" << std::endl;
            resultSumAB.Display();

            CustomMatrix resultDifferenceAB = matrixA.MatrixDifference(matrixB);
            std::cout << "\nMatrix Subtraction Result (A - B):" << std::endl;
            resultDifferenceAB.Display();

            CustomMatrix resultProductAB = matrixA.MatrixProduct(matrixB);
            std::cout << "\nMatrix Multiplication Result (A * B):" << std::endl;
            resultProductAB.Display();
        }

        if (matrixC.IsMatrixInvalid() || matrixD.IsMatrixInvalid()) {
            std::cout << "\nMatrix C and Matrix D are invalid (Not a Matrix)." << std::endl;
        } else {
            std::cout << "\nPerforming calculations for Matrix C and Matrix D:" << std::endl;

            auto matrixCData = matrixC.GetMatrixData();
            auto matrixDData = matrixD.GetMatrixData();

            if (matrixCData[0].size() != matrixDData.size()) {
                std::cout << "Matrix dimensions are not compatible for addition and subtraction." << std::endl;
            } else {
                CustomMatrix resultSumCD = matrixC.MatrixSum(matrixD);
                std::cout << "\nMatrix Addition Result (C + D):" << std::endl;
                resultSumCD.Display();

                CustomMatrix resultDifferenceCD = matrixC.MatrixDifference(matrixD);
                std::cout << "\nMatrix Subtraction Result (C - D):" << std::endl;
                resultDifferenceCD.Display();

                try {
                    CustomMatrix resultProductCD = matrixC.MatrixProduct(matrixD);
                    std::cout << "\nMatrix Multiplication Result (C * D):" << std::endl;
                    resultProductCD.Display();
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    std::cout << "Matrix C and Matrix D multiplication is invalid." << std::endl;
                }
            }
        }

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
