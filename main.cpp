#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

const int SIZE = 4; // Global variable for matrix size

class Matrix {
private:
  int data[SIZE][SIZE];  // 2D array for matrix data (using int for simplicity)

public:
  // 1. Read values from stdin into a matrix
  void readFromStdin(ifstream& file) {
    for (int i=0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        file >> data[i][j];
      }
    }
  }
  
  // 2. Display a matrix
  void display() const {
    for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
        cout << data[i][j] << " ";
      }
      cout << endl;
    }
  }

  // 3. Add two matrices (operator overloading for +)
  Matrix operator+(const Matrix& other) const {
    Matrix result;
    for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
        result.data[i][j] = data[i][j] + other.data[i][j]; // add each index
      }
    }
    return result;
  }

  // 4. Multiply two matrices (operator overloading for *)
  Matrix operator*(const Matrix& other) const {
    Matrix result;
    for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
        result.data[i][j] = 0; // reset
        for (int k=0; k < SIZE; k++) {
          result.data[i][j] += data[i][k] * other.data[k][j]; // multi and sum
        }
      }
    }
    return result;
  }

  // 5. Compute the sum of matrix diagonal elements
  int sumOfDiagonals() const {
    int sum = 0;
    for (int i=0; i < SIZE; i++) {
      sum += data[i][i]; // top left to bottom right
      sum += data[i][SIZE-1-i]; // top right to bottom left
    }
    return sum;
  }

  // 6. Swap matrix rows
  void swapRows(int row1, int row2) {
    if (row1 < 0 || row2 < 0 || row1 >= SIZE || row2 >= SIZE) {
      cout << "Error: row indexes not valid." << endl;
      return;
    }
    for (int i=0; i < SIZE; i++) {
      int temp = data[row1][i]; // hold row temp
      data[row1][i] = data[row2][i]; // replace
      data[row2][i] = temp; // put back temp
    }
  }
};

int main() {
  string filename;
  cout << "Enter input file name: ";
  getline(cin, filename);
  ifstream file(filename); // open file
  if (!file.is_open()) {
    cerr << "Failed to open file: " << filename << endl;
    exit(1);
  }
  // Example usage:
  Matrix mat1;
  cout << "Enter values for Matrix 1:" << endl;
  mat1.readFromStdin(file);
  cout << "Matrix 1:" << endl;
  mat1.display();

  Matrix mat2;
  cout << "Enter values for Matrix 2:" << endl;
  mat2.readFromStdin(file);
  cout << "Matrix 2:" << endl;
  mat2.display();

  file.close(); // close file

  Matrix sum = mat1 + mat2;
  cout << "Sum of matrices:" << endl;
  sum.display();

  Matrix product = mat1 * mat2;
  cout << "Product of matrices:" << endl;
  product.display();

  cout << "Sum of diagonals of Matrix 1: " << mat1.sumOfDiagonals() << endl;

  mat1.swapRows(0, 2);
  cout << "Matrix 1 after swapping rows:" << endl;
  mat1.display();

  return 0;
}
