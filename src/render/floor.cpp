#include "render/floor.h"

void Floor::DrawTextureTiled(Texture2D texture, Rectangle source, Rectangle dest, 
    Vector2 origin, float rotation, Vector2 scale, Color tint)
{
    for (float y = dest.y; y < dest.y + dest.height; y += source.height * scale.y) {
        for (float x = dest.x; x < dest.x + dest.width; x += source.width * scale.x) {
            Rectangle dstRec = { x, y, source.width * scale.x, source.height * scale.y };
            DrawTexturePro(texture, source, dstRec, origin, rotation, tint);
        }
    }
}

Floor::Floor(const char* texturePath, float width, float height) {
    texture = LoadTexture(texturePath);
    sourceRec = { 0, 0, (float)texture.width, (float)texture.height };
    destRec = { 0, 0, width, height };
    origin = { 0, 0 };
    scale = { 1.0f, 1.0f };
}

Floor::~Floor() {
    UnloadTexture(texture);
}

void Floor::draw() {
   DrawTextureTiled(texture, sourceRec, destRec, origin, 0.0f, scale, WHITE);
}
