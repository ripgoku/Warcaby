#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <iostream>

enum class PieceType { MAN, KING };
enum class PieceColor { BLACK, WHITE };

class Piece {
public:
    Piece(int x, int y, PieceType type, PieceColor color);
    void renderPiece();
    void move(int newX, int newY);
    void promoteToKing();
    PieceType getType() const;
    PieceColor getColor() const;
    void setSelected(bool selected);
    bool isSelected() const;
    glm::vec2 getPosition();
    bool getAnimation();
    void setAnimation(bool enable);
    glm::vec2 getDestPosition();
    void setDestPosition(glm::vec2 position);
    glm::vec3 getXyzPosition();
    void setXyzPosition(glm::vec3 position);

private:
    glm::vec2 position;
    PieceType type;
    PieceColor color;
    bool selected;
    bool animation;
    glm::vec2 destPosition;
    glm::vec3 xyzPosition;

    void renderCylinder(float radius, float height, int slices);
    void renderKingCrown();
    void setMaterialColor(float r, float g, float b);
    void setMaterial();
};