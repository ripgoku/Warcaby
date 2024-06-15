#include "Board.h"
#include <iostream>

Board::Board() {
    initializeBoard();
}

Board::~Board() {
    clearBoard();
}

void Board::initializeBoard() {
    blackNumber = whiteNumber = 12;
    board.resize(8, std::vector<Piece*>(8, nullptr));

    for (int y = 0; y < 3; ++y) {
        for (int x = ((y+1) % 2); x < 8; x += 2) {
            board[y][x] = new Piece(x, y, PieceType::MAN, PieceColor::BLACK);
        }
    }

    for (int y = 5; y < 8; ++y) {
        for (int x = ((y + 1) % 2); x < 8; x += 2) {
            board[y][x] = new Piece(x, y, PieceType::MAN, PieceColor::WHITE);
        }
    }
}

void Board::renderBoard() {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    woodTexture.loadTexture("Textures/wood.jpg");
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.5f, -1.1f, 4.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(4.5f, -1.1f, 4.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(4.5f, -0.2f, 4.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.5f, -0.2f, 4.5f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.5f, -1.1f, -4.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-4.5f, -1.1f, 4.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-4.5f, -0.2f, 4.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.5f, -0.2f, -4.5f);
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f(4.5f, -1.1f, -4.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-4.5f, -1.1f, -4.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-4.5f, -0.2f, -4.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(4.5f, -0.2f, -4.5f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(4.5f, -1.1f, 4.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(4.5f, -1.1f, -4.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(4.5f, -0.2f, -4.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(4.5f, -0.2f, 4.5f);
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    woodTexture2.loadTexture("Textures/wood2.jpg");
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.5f, -0.2f, -4.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(4.5f, -0.2f, -4.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(4.5f, -0.2f, 4.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.5f, -0.2f, 4.5f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.5f, -1.1f, -4.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(4.5f, -1.1f, -4.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(4.5f, -1.1f, 4.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.5f, -1.1f, 4.5f);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    double currentX = x;
    double currentZ = z;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            SquareType sqType = ((i + j) % 2 == 0) ? SquareType::LIGHT_SQUARE : SquareType::DARK_SQUARE;
            if (getSelectedPiece() != nullptr && !getSelectedPiece()->getAnimation() && isValidMove(getSelectedPiece()->getPosition().x, getSelectedPiece()->getPosition().y, j, i))
                sqType = SquareType::HIGHLIGHT_DARK_SQUARE;
            
            renderSquare(currentX, y, currentZ, size, sqType);

            if (board[i][j]) {
                board[i][j]->renderPiece();
            }
            currentX += size;
        }
        currentX = x;
        currentZ += size;
    }
}

Piece* Board::getPieceAt(int x, int y) {
    if (isInBounds(x, y)) {
        return board[y][x];
    }
    return nullptr;
}

bool Board::movePiece(int startX, int startY, int endX, int endY, Turn turn) {
    if (isInBounds(startX, startY) && isInBounds(endX, endY)) {
        if (isValidMove(startX, startY, endX, endY)) {
            Piece* piece = getPieceAt(startX, startY);
            if (piece != nullptr && ((turn == PLAYER_1 && piece->getColor() == PieceColor::WHITE) ||
                (turn == PLAYER_2 && piece->getColor() == PieceColor::BLACK))) {
                board[startY][startX]->move(endX, endY);
                board[endY][endX] = piece;
                board[startY][startX] = nullptr;
                if (abs(endX - startX) == 2 && abs(endY - startY) == 2) {
                    int midX = (startX + endX) / 2;
                    int midY = (startY + endY) / 2;

                    if (board[midY][midX]->getColor() == PieceColor::WHITE)
                        whiteNumber -= 1;
                    else if (board[midY][midX]->getColor() == PieceColor::BLACK)
                        blackNumber -= 1;

                    delete board[midY][midX]; 
                    board[midY][midX] = nullptr;
                    this->captured = true;
                }
                if ((endY == 0 && piece->getColor() == PieceColor::WHITE) ||
                    (endY == 7 && piece->getColor() == PieceColor::BLACK))
                    piece->promoteToKing();
                return true;
            }
        }
    }
    return false;
}

bool Board::isValidMove(int startX, int startY, int endX, int endY) {
    if (!isInBounds(startX, startY) || !isInBounds(endX, endY)) {
        return false;
    }

    int deltaX = endX - startX;
    int deltaY = endY - startY;

    Piece* piece = board[startY][startX];
    if (piece == nullptr || !piece->isSelected()) {
        return false;
    }

    if (board[endY][endX] != nullptr) {
        return false; 
    }

    PieceType pieceType = piece->getType();
    PieceColor color = piece->getColor();

    if (pieceType != PieceType::KING) {
        if (color == PieceColor::WHITE) {
            if (deltaY > 0) {
                return false;
            }
        }
        else if (color == PieceColor::BLACK) {
            if (deltaY < 0) {
                return false;
            }
        }
    }

    bool mandatoryCapture = false;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Piece* currentPiece = board[y][x];
            if (currentPiece != nullptr && currentPiece->getColor() == color) {
                if (canCapture(x, y, color)) {
                    mandatoryCapture = true;
                    break;
                }
            }
        }
        if (mandatoryCapture) break;
    }

    if (abs(deltaX) == 2 && abs(deltaY) == 2 && canCapture(startX, startY, board[startY][startX]->getColor())) {
        int midX = (startX + endX) / 2;
        int midY = (startY + endY) / 2;
        Piece* middlePiece = board[midY][midX];

        if (middlePiece == nullptr || middlePiece->getColor() == piece->getColor()) {
            return false; 
        }

        return true;
    }

    if (mandatoryCapture) {
        return false;
    }

    if (abs(deltaX) == 1 && abs(deltaY) == 1) {
        return true; 
    }

    return false; 
}

bool Board::canCapture(int x, int y, PieceColor color) {
    Piece* piece = board[y][x];
    if (!piece) return false;

    std::vector<std::pair<int, int>> directions;
    if (piece->getType() == PieceType::KING) {
        directions = { {2, 2}, {2, -2}, {-2, 2}, {-2, -2} };
    }
    else {
        directions = (color == PieceColor::WHITE) ? std::vector<std::pair<int, int>>{{2, -2}, { -2, -2 }}
        : std::vector<std::pair<int, int>>{ {2, 2}, {-2, 2} };
    }

    for (const auto& dir : directions) {
        int targetX = x + dir.first;
        int targetY = y + dir.second;
        int midX = (targetX + x) / 2;
        int midY = (targetY + y) / 2;

        if (isInBounds(targetX, targetY) && isInBounds(midX, midY)) {
            Piece* targetPiece = board[targetY][targetX];
            Piece* middlePiece = board[midY][midX];

            if (targetPiece == nullptr && middlePiece != nullptr && middlePiece->getColor() != color) {
                return true;
            }
        }
    }
    return false;
}

void Board::selectPiece(int x, int y, Turn playerTurn) {
    if (isInBounds(x, y) && board[y][x] != nullptr) {
        if((playerTurn == PLAYER_1 && board[y][x]->getColor() == PieceColor::WHITE) || 
            (playerTurn == PLAYER_2 && board[y][x]->getColor() == PieceColor::BLACK))
        {
            deselectAllPieces();
            board[y][x]->setSelected(true);
            this->selectedPiece = getPieceAt(x, y);
        }
    }
}

void Board::deselectAllPieces() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] != nullptr) {
                board[i][j]->setSelected(false);
            }
        }
    }
    selectedPiece = nullptr;
}

bool Board::isInBounds(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

void Board::renderSquare(double x, double y, double z, double side, SquareType sqType) {
    glPushMatrix();
    glTranslated(x, y, z);

    GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat mat_diffuse[4] = {0,0,0,0};
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };



    switch (sqType) {
    case SquareType::LIGHT_SQUARE:
        mat_diffuse[0] = 1.0f; mat_diffuse[1] = 0.956f; mat_diffuse[2] = 0.749f; mat_diffuse[3] = 1.0f;
        break;
    case SquareType::DARK_SQUARE:
        mat_diffuse[0] = 0.361f; mat_diffuse[1] = 0.090f; mat_diffuse[2] = 0.008f; mat_diffuse[3] = 1.0f;
        break;
    case SquareType::HIGHLIGHT_DARK_SQUARE:
        mat_diffuse[0] = 0.5f; mat_diffuse[1] = 0.5f; mat_diffuse[2] = 0.9f; mat_diffuse[3] = 1.0f;
        break;
    default:
        mat_diffuse[0] = 0.5f; mat_diffuse[1] = 0.5f; mat_diffuse[2] = 0.5f; mat_diffuse[3] = 1.0f;
        break;
    }

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidCube(side);
    glPopMatrix();
}

Piece* Board::getSelectedPiece() {
    return selectedPiece;
}

bool Board::checkGameOver() {
    if (blackNumber == 0)
        return true;
    else if (whiteNumber == 0)
        return true;
    else
        return false;
}

void Board::clearBoard() {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            if (board[x][y] != nullptr) {
                delete board[x][y];
                board[x][y] = nullptr;
            }
        }
    }
}

void Board::setCaptured(bool captur) {
    this->captured = captur;
}

bool Board::getCaptured() {
    return this->captured;
}