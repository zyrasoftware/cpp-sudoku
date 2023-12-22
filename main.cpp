#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Sudoku {
public:
    Sudoku() {
        initializeBoard();
    }

    void playGame() {
        while (!isSudokuSolved()) {
            displayBoard();
            int row, col, num;
            getUserMove(row, col, num);

            if (isValidMove(row, col, num)) {
                placeNumber(row, col, num);
            }
            else {
                std::cout << "Geçersiz hamle. Lütfen tekrar deneyin." << std::endl;
            }
        }

        std::cout << "Tebrikler! Sudoku tamamlandı." << std::endl;
    }

private:
    std::vector<std::vector<int>> board;

    void initializeBoard() {
        board = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
        generateSudoku();
    }

    void generateSudoku() {
        // Sudoku üretebilecek bir algoritma kullanabilirsiniz.
        // Bu örnekte, basit bir şekilde rastgele sayılar yerleştirilmiştir.
        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < 20; ++i) {
            int row = rand() % 9;
            int col = rand() % 9;
            int num = rand() % 9 + 1;
            board[row][col] = num;
        }
    }

    void displayBoard() const {
        std::cout << "-------------------------" << std::endl;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                std::cout << board[i][j] << " ";
                if ((j + 1) % 3 == 0 && j < 8) {
                    std::cout << "| ";
                }
            }
            std::cout << std::endl;
            if ((i + 1) % 3 == 0 && i < 8) {
                std::cout << "-------------------------" << std::endl;
            }
        }
    }

    void getUserMove(int& row, int& col, int& num) const {
        std::cout << "Satır, sütun ve sayıyı girin (örneğin, 3 5 7): ";
        std::cin >> row >> col >> num;
    }

    bool isValidMove(int row, int col, int num) const {
        return board[row][col] == 0 && isNumValidInRow(row, num) && isNumValidInCol(col, num) &&
            isNumValidInBox(row - row % 3, col - col % 3, num);
    }

    bool isNumValidInRow(int row, int num) const {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == num) {
                return false;
            }
        }
        return true;
    }

    bool isNumValidInCol(int col, int num) const {
        for (int row = 0; row < 9; ++row) {
            if (board[row][col] == num) {
                return false;
            }
        }
        return true;
    }

    bool isNumValidInBox(int startRow, int startCol, int num) const {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (board[startRow + row][startCol + col] == num) {
                    return false;
                }
            }
        }
        return true;
    }

    void placeNumber(int row, int col, int num) {
        board[row][col] = num;
    }

    bool isSudokuSolved() const {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    setlocale(LC_ALL, "Turkish");
    Sudoku sudokuGame;
    sudokuGame.playGame();

    return 0;
}
