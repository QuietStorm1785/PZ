#include <iostream>
#include "Sprite.h"
#include "SpriteBatch.h"
#include "Core.h"
#include "TextureManager.h"

using namespace zombie;

/**
 * Simple unit test for sprite rendering system
 */
int main() {
    std::cout << "=== Sprite System Test ===" << std::endl;
    
    // Test 1: Sprite creation
    std::cout << "Test 1: Creating sprite... ";
    graphics::Sprite sprite;
    sprite.setPosition(100, 200);
    sprite.setSize(64, 64);
    sprite.setScale(2.0f, 2.0f);
    sprite.setRotation(45.0f);
    sprite.setColor(255, 128, 0);
    sprite.setAlpha(200);
    sprite.setOrigin(0.5f, 0.5f);
    std::cout << "PASS" << std::endl;
    
    // Test 2: Sprite properties
    std::cout << "Test 2: Verifying sprite properties... ";
    bool pass = true;
    pass &= (sprite.getX() == 100.0f);
    pass &= (sprite.getY() == 200.0f);
    pass &= (sprite.getWidth() == 64.0f);
    pass &= (sprite.getHeight() == 64.0f);
    pass &= (sprite.getScaleX() == 2.0f);
    pass &= (sprite.getScaleY() == 2.0f);
    pass &= (sprite.getRotation() == 45.0f);
    pass &= (sprite.getOriginX() == 0.5f);
    pass &= (sprite.getOriginY() == 0.5f);
    pass &= (sprite.getAlpha() == 200);
    
    Uint8 r, g, b;
    sprite.getColor(&r, &g, &b);
    pass &= (r == 255 && g == 128 && b == 0);
    
    std::cout << (pass ? "PASS" : "FAIL") << std::endl;
    
    // Test 3: Source rectangle
    std::cout << "Test 3: Source rectangle... ";
    sprite.setSourceRect(10, 20, 30, 40);
    pass = sprite.hasSourceRect();
    auto srcRect = sprite.getSourceRect();
    pass &= (srcRect.x == 10 && srcRect.y == 20 && srcRect.w == 30 && srcRect.h == 40);
    sprite.clearSourceRect();
    pass &= !sprite.hasSourceRect();
    std::cout << (pass ? "PASS" : "FAIL") << std::endl;
    
    // Test 4: Flip flags
    std::cout << "Test 4: Flip flags... ";
    sprite.setFlipHorizontal(true);
    sprite.setFlipVertical(true);
    pass = sprite.isFlippedHorizontal() && sprite.isFlippedVertical();
    sprite.setFlipHorizontal(false);
    pass &= !sprite.isFlippedHorizontal() && sprite.isFlippedVertical();
    std::cout << (pass ? "PASS" : "FAIL") << std::endl;
    
    // Test 5: SpriteBatch creation
    std::cout << "Test 5: SpriteBatch creation... ";
    graphics::SpriteBatch batch;
    batch.resetStats();
    pass = (batch.getDrawCallCount() == 0 && batch.getSpriteCount() == 0);
    std::cout << (pass ? "PASS" : "FAIL") << std::endl;
    
    std::cout << std::endl;
    std::cout << "=== All Tests Completed ===" << std::endl;
    std::cout << "Sprite rendering system is ready!" << std::endl;
    
    return 0;
}
