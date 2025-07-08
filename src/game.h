#pragma once
#include <array>


// Window Properties
float const WindowX = 800.0f;
float const WindowY = 800.0f;


void Event();
void Update();
void Draw();
void InitWindowCustom();

class CODS {
    std::array<float, 2> coord; // coord[0]: x, coord[1]: y
public:
    CODS();
    CODS(float xVal, float yVal);

    void setX(float xVal);
    void setY(float yVal);
    void set(float xVal, float yVal);

    float getX() const;
    float getY() const;

    // Access as matrix
    float& operator()(int idx) { return coord[idx]; }
    float operator()(int idx) const { return coord[idx]; }
};