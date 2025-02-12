#pragma once

#include <vector>
#include "Piece.h"
#include "Texture.h"

enum Turn { PLAYER_1, PLAYER_2 };
enum class SquareType { LIGHT_SQUARE, DARK_SQUARE, HIGHLIGHT_DARK_SQUARE };

class Board {
public:
    Board();
    ~Board();
    void initializeBoard();
    bool isInBounds(int x, int y);
    void renderBoard();
    Piece* getPieceAt(int x, int y);
    bool movePiece(int startX, int startY, int endX, int endY, Turn playerTurn);
    bool isValidMove(int startX, int startY, int endX, int endY);
    void selectPiece(int x, int y, Turn playerTurn);
    void deselectAllPieces();
    Piece* getSelectedPiece();
    bool canCapture(int x, int y, PieceColor color);
    bool checkGameOver();
    void clearBoard();
    void setCaptured(bool captur);
    bool getCaptured();

private:
    void renderSquare(double x, double y, double z, double size, SquareType sqType);

    std::vector<std::vector<Piece*>> board;
    Piece* selectedPiece = nullptr;
    Texture woodTexture;
    Texture woodTexture2;
    bool captured = false;
    int blackNumber, whiteNumber;
    int rows = 8;
    int columns = 8;
    double size = 1.0;
    double x = -3.5;
    double y = -0.5;
    double z = -3.5;
};
