#include <cstdlib>
#include <gtest/gtest.h>

#define private public
#include "glyphs/glyph.h"
#include "glyphs/character.h"

TEST(Character_Construct, CharacterConstructor_WhenCalled_CreatesCharacterWithPositionAndSymbol) {
    Character c = Character(1, 2, 3, 4, 'A');
    ASSERT_EQ(c.GetPosition().x, 1);
    ASSERT_EQ(c.GetPosition().y, 2);
    ASSERT_EQ(c.GetWidth(), 3);
    ASSERT_EQ(c.GetHeight(), 4);
    ASSERT_EQ(c.GetChar(), 'A');
}