#include "Piece.h"

Piece::Piece(int x, int y, PieceType type, PieceColor color)
    : position(x, y), type(type), color(color), selected(false), 
    animation(false), destPosition(position), xyzPosition(glm::vec3((float)x-3.5f, 0.0f, (float)y-3.5f)) {}

void Piece::renderPiece() {
    glPushMatrix();

    // Przesuniêcie pionka na odpowiedni¹ pozycjê na planszy
    glTranslatef((GLfloat)xyzPosition.x, (GLfloat)xyzPosition.y, (GLfloat)xyzPosition.z);
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f);

    // Ustawienie koloru pionka
    setMaterial();

    // Renderowanie podstawowego pionka jako cylinder
    renderCylinder(0.4f, 0.2f, 128);

    if (type == PieceType::KING) {
        setMaterialColor(1.0f, 0.84f, 0.0f);
    }

    renderKingCrown();

    glPopMatrix();
}

void Piece::move(int newX, int newY) {
    position = glm::vec2(newX, newY);
}

void Piece::promoteToKing() {
    type = PieceType::KING;
}

PieceType Piece::getType() const {
    return type;
}

PieceColor Piece::getColor() const {
    return color;
}

void Piece::setMaterial() {
    if (selected && !animation) {
        setMaterialColor(0.5f, 0.5f, 0.9f);
    }
    else {
        switch (color) {
        case PieceColor::BLACK:
            setMaterialColor(0.1f, 0.1f, 0.1f); // Ustawienie koloru materia³u na czarny
            break;
        case PieceColor::WHITE:
            setMaterialColor(0.9f, 0.9f, 0.9f); // Ustawienie koloru materia³u na bia³y
            break;
        }
    }
}

void Piece::setMaterialColor(float r, float g, float b) {
    GLfloat mat_ambient[] = { r * 0.2f, g * 0.2f, b * 0.2f, 1.0f };
    GLfloat mat_diffuse[] = { r, g, b, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void Piece::renderCylinder(float radius, float height, int slices) {
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, radius, radius, height, slices, 1);
    gluDisk(quad, 0, radius, slices, 1);
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(quad, 0, radius, slices, 1);
    glTranslatef(0.0f, 0.0f, -height);
    gluDeleteQuadric(quad);
}

void Piece::renderKingCrown() {
    // Renderowanie dodatkowego elementu reprezentuj¹cego koronê
    // To mo¿e byæ prosta reprezentacja np. ma³y sto¿ek lub inny kszta³t
    /*glPushMatrix();
    glTranslatef((GLfloat)xyzPosition.x, 0.2f, (GLfloat)xyzPosition.z);
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
    setMaterialColor(1.0f, 0.84f, 0.0f);
    glutSolidTorus(0.05f, 0.3f, 32, 32);
    glPopMatrix();*/

    glTranslatef(0.0f, 0.0f, 0.2f);
    glutSolidTorus(0.05f, 0.3f, 32, 128);
    glTranslatef(0.0f, 0.0f, -0.2f);
}

void Piece::setSelected(bool selected) {
    this->selected = selected;
}

bool Piece::isSelected() const {
    return selected;
}

glm::vec2 Piece::getPosition() {
    return position;
}

bool Piece::getAnimation() {
    return animation;
}

void Piece::setAnimation(bool enable) {
    animation = enable;
}

glm::vec2 Piece::getDestPosition() {
    return destPosition;
}

void Piece::setDestPosition(glm::vec2 position) {
    destPosition = position;
}

glm::vec3 Piece::getXyzPosition() {
    return xyzPosition;
}
void Piece::setXyzPosition(glm::vec3 position) {
    xyzPosition = position;
}