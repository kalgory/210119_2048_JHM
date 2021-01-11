#include <iostream>
#include <vector>


using namespace std;

int getMaxOfBoard(vector<vector<int>>& board_vec_vec) {
  int max = 0;
  for (const auto& board_vec : board_vec_vec) {
    for (const auto board : board_vec) {
      if (board > max) {
        max = board;
      }
    }
  }
  return max;
}

vector<vector<int>> moveBoard(vector<vector<int>> board_vec_vec) {
  for (int x = 0; x < board_vec_vec.size(); x++) {
    bool can_add = true;
    for (int y = 1; y < board_vec_vec.size(); y++) {
      if (board_vec_vec[y][x] == 0) continue;
      int y_temp = y;
      while (board_vec_vec[y_temp - 1][x] == 0) {
        y_temp--;
        if (y_temp == 0) break;
      }
      if (y_temp == 0) { // CASE 1: first index is Empty.
        board_vec_vec[0][x] = board_vec_vec[y][x];
        board_vec_vec[y][x] = 0;
      } else if (board_vec_vec[y_temp - 1][x] == board_vec_vec[y][x] && can_add) { // CASE 2: y_temp - 1 value is same with y index value.
        board_vec_vec[y_temp - 1][x] *= 2;
        board_vec_vec[y][x] = 0;
        can_add = false;
      } else if (y != y_temp) { // CASE 3: y_temp - 1 value is not same with y index value.
        board_vec_vec[y_temp][x] += board_vec_vec[y][x];
        board_vec_vec[y][x] = 0;
        can_add = true;
      }
    }
  }
  return board_vec_vec;
}

void rotateBoard(vector<vector<int>>& board_vec_vec) {
  vector<vector<int>> board_vec_vec_temp = board_vec_vec;
  for (int i = 0; i < board_vec_vec.size(); i++) {
    for (int j = 0; j < board_vec_vec.size(); j++) {
      board_vec_vec[i][j] = board_vec_vec_temp[board_vec_vec.size() - j - 1][i];
    }
  }
}

int solution(vector<vector<int>> board_vec_vec, int move_count) {
  if (move_count == 5) {
    return getMaxOfBoard(board_vec_vec);
  }
  int max_element = 0;
  max_element = max(solution(moveBoard(board_vec_vec), move_count + 1), max_element);
  rotateBoard(board_vec_vec);
  max_element = max(solution(moveBoard(board_vec_vec), move_count + 1), max_element);
  rotateBoard(board_vec_vec);
  max_element = max(solution(moveBoard(board_vec_vec), move_count + 1), max_element);
  rotateBoard(board_vec_vec);
  max_element = max(solution(moveBoard(board_vec_vec), move_count + 1), max_element);
  return max_element;
}

int main() {
  int board_size = 0;
  cin >> board_size;
  vector<vector<int>> board_vec_vec(board_size, vector<int>(board_size));
  for (int i = 0; i < board_size; i++) {
    for (int j = 0; j < board_size; j++) {
      cin >> board_vec_vec[i][j];
    }
  }
  cout << solution(board_vec_vec, 0) << endl;
  return 0;
}