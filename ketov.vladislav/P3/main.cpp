#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

const int invalid_argument = 1;
const int invalid_data = 2;
const int max_rows = 100;
const int max_cols = 100;

int main(int argc, char *argv[])
{
  if (argc != 4) {
    std::cerr << "Not enough arguments\n";
    return invalid_argument;
  }

  const char *const s = argv[1];
  for (size_t i = 0; s[i] != '\0'; ++i) {
    if (s[i] < '0' || s[i] > '9') {
      std::cerr << "First parameter is not a number\n";
      return invalid_argument;
    }
  }

  if ((std::stoi(argv[1]) != 1) && (std::stoi(argv[1]) != 2)) {
    std::cerr << "First parametr is out of range\n";
    return invalid_argument;
  }

  std::ifstream file_in(argv[2]);
  if (!file_in) {
    std::cerr << "Can not open file\n";
    return invalid_data;
  }

  std::ofstream file_out(argv[3]);
  if (!file_out) {
    std::cerr << "Can not open file\n";
    return invalid_data;
  }

  int rows = 0;
  int cols = 0;

  if (std::stoi(argv[1]) == 1) {
    if (!(file_in >> rows >> cols)) {
      std::cerr << "Not correct data\n";
      return invalid_data;
    }

    if (rows > max_rows || cols > max_cols) {
      std::cerr << "Too large size";
      return invalid_data;
    }

    int arr[max_rows][max_cols] = {};

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(file_in >> arr[i][j])) {
          std::cerr << "Not correct data\n";
          return invalid_data;
        }
      }
    }

    int add_value = 1;
    const int all_count = rows * cols;
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;
    while (add_value <= all_count) {
      for (int i = left; i <= right && add_value <= all_count; i++) {
        arr[bottom][i] += add_value;
        add_value++;
      }
      bottom--;

      for (int i = bottom; i >= top && add_value <= all_count; i--) {
        arr[i][right] += add_value;
        add_value++;
      }
      right--;

      for (int i = right; i >= left && add_value <= all_count; i--) {
        arr[top][i] += add_value;
        add_value++;
      }
      top++;

      for (int i = top; i <= bottom && add_value <= all_count; i++) {
        arr[i][left] += add_value;
        add_value++;
      }
      left++;
    }

    file_out << rows << " " << cols << " ";
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        file_out << arr[i][j] << " ";
      }
    }
  }

  if (std::stoi(argv[1]) == 2) {
    if (!(file_in >> rows >> cols)) {
      std::cerr << "Not correct data\n";
      return invalid_data;
    }

    int **const arr = new int *[rows];

    try {
      for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols]{};
      }
    } catch (...) {
      for (int i = 0; i < rows; i++) {
        delete[] arr[i];
      }
      delete[] arr;
      std::cerr << "no memory";
      return invalid_argument;
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(file_in >> arr[i][j])) {
          std::cerr << "Not correct data\n";
          for (int k = 0; k < rows; k++) {
            delete[] arr[k];
          }
          delete[] arr;
          return invalid_data;
        }
      }
    }

    int add_value = 1;
    const int all_count = rows * cols;
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;
    while (add_value <= all_count) {
      for (int i = left; i <= right && add_value <= all_count; i++) {
        arr[bottom][i] += add_value;
        add_value++;
      }
      bottom--;

      for (int i = bottom; i >= top && add_value <= all_count; i--) {
        arr[i][right] += add_value;
        add_value++;
      }
      right--;

      for (int i = right; i >= left && add_value <= all_count; i--) {
        arr[top][i] += add_value;
        add_value++;
      }
      top++;

      for (int i = top; i <= bottom && add_value <= all_count; i++) {
        arr[i][left] += add_value;
        add_value++;
      }
      left++;
    }

    file_out << rows << " " << cols << " ";
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        file_out << arr[i][j] << " ";
      }
    }

    for (int i = 0; i < rows; i++) {
      delete[] arr[i];
    }
    delete[] arr;
  }

  file_in.close();
  file_out.close();
  return 0;
}
