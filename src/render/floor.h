#pragma once
#include "raylib.h"

class Floor {
private:
    Texture2D texture;
    Rectangle sourceRec;
    Rectangle destRec;
    Vector2 origin;
    Vector2 scale;
    void DrawTextureTiled(Texture2D texture, Rectangle source, Rectangle dest, 
        Vector2 origin, float rotation, Vector2 scale, Color tint);
public:
    // Constructor
    Floor(const char* texturePath, float width, float height);

    // Destructor
    ~Floor();

    // Drawing function
    void draw();
};
