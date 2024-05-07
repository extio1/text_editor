#include <cstdlib>
#include <gtest/gtest.h>

#include "document/glyphs/character.h"
#include "document/glyphs/glyph.h"
#include "document/glyphs/row.h"


//----------------------------------------Glyph---------------------------------------------------
TEST(Glyph_Constructor, GlyphConstructor_WhenCalled_CreatesGlyphWithPosition) {
    Character c = Character(1, 2, 3, 4, 'A');
    ASSERT_EQ(c.GetPosition().x, 1);
    ASSERT_EQ(c.GetPosition().y, 2);
    ASSERT_EQ(c.GetWidth(), 3);
    ASSERT_EQ(c.GetHeight(), 4);
}

TEST(Glyph_Intersects_Point1, GlyphIntersectsInternPoints_WhenCalled_ReturnTrue) {
    Character c = Character(1, 2, 2, 2, 'A');
    //corners
    ASSERT_TRUE(c.Intersects(Point(1, 2)));
    ASSERT_TRUE(c.Intersects(Point(3, 2)));
    ASSERT_TRUE(c.Intersects(Point(1, 4)));
    ASSERT_TRUE(c.Intersects(Point(3, 4)));
    //inside
    ASSERT_TRUE(c.Intersects(Point(2, 2)));
    ASSERT_TRUE(c.Intersects(Point(1, 3)));
    ASSERT_TRUE(c.Intersects(Point(2, 3)));
    ASSERT_TRUE(c.Intersects(Point(3, 3)));
    ASSERT_TRUE(c.Intersects(Point(2, 4)));
}

TEST(Glyph_Intersects_Point2, GlyphIntersectsExternPoints_WhenCalled_ReturnFalse) {
    Character c = Character(1, 2, 2, 2, 'A');
    //corners
    ASSERT_FALSE(c.Intersects(Point(0, 0)));
    ASSERT_FALSE(c.Intersects(Point(0, 1)));
    ASSERT_FALSE(c.Intersects(Point(1, 1)));
    ASSERT_FALSE(c.Intersects(Point(2, 1)));
    //inside
    ASSERT_FALSE(c.Intersects(Point(3, 1)));
    ASSERT_FALSE(c.Intersects(Point(4, 1)));
    ASSERT_FALSE(c.Intersects(Point(4, 2)));
    ASSERT_FALSE(c.Intersects(Point(4, 2)));
    ASSERT_FALSE(c.Intersects(Point(4, 4)));
    ASSERT_FALSE(c.Intersects(Point(4, 5)));
    ASSERT_FALSE(c.Intersects(Point(3, 5)));
    ASSERT_FALSE(c.Intersects(Point(2, 5)));
    ASSERT_FALSE(c.Intersects(Point(1, 5)));
    ASSERT_FALSE(c.Intersects(Point(0, 5)));
    ASSERT_FALSE(c.Intersects(Point(0, 4)));
    ASSERT_FALSE(c.Intersects(Point(0, 3)));
    ASSERT_FALSE(c.Intersects(Point(0, 2)));
}

TEST(Glyph_Intersects_Glyph1, GlyphIntersectsTheSameGlyph_WhenCalled_ReturnTrue) {
    Character c = Character(1, 2, 2, 2, 'A');
    ASSERT_TRUE(c.Intersects(std::make_shared<Character>(c)));
}

TEST(Glyph_Intersects_Glyph2, GlyphIntersectsSmallerGlyph_WhenCalled_ReturnTrue) {
    Character c = Character(1, 2, 3, 3, 'A');
    Character c2 = Character(2, 3, 1, 1, 'B');
    ASSERT_TRUE(c.Intersects(std::make_shared<Character>(c2)));
}

TEST(Glyph_Intersects_Glyph3, GlyphIntersectsBiggerGlyph_WhenCalled_ReturnTrue) {
    Character c = Character(1, 2, 3, 3, 'A');
    Character c2 = Character(0, 0, 10, 10, 'B');
    ASSERT_TRUE(c.Intersects(std::make_shared<Character>(c2)));
}

TEST(Glyph_Intersects_Glyph4, GlyphIntersectsGlyphAround_WhenCalled_ReturnFalse) {
    Character c = Character(1, 2, 3, 3, 'A');
    Character c2 = Character(0, 0, 1, 1, 'B');
    ASSERT_FALSE(c.Intersects(std::make_shared<Character>(c2)));
}

TEST(Glyph_Intersects_Glyph5, GlyphIntersectsGlyphByCorner_WhenCalled_ReturnTrue) {
    Character c = Character(1, 2, 3, 3, 'A');
    Character c2 = Character(3, 4, 1, 1, 'B');
    ASSERT_TRUE(c.Intersects(std::make_shared<Character>(c2)));
}

TEST(Glyph_Intersects_Glyph6, ZeroSizeGlyphIntersetsHimself_WhenCalled_ReturnTrue) {
    Character c = Character(1, 2, 0, 0, 'A');
    ASSERT_TRUE(c.Intersects(std::make_shared<Character>(c)));
}

TEST(Glyph_MoveGlyph1, GlyphMoveGlyph_WhenCalled_ChangesPositionOfGlyphDueArguments) {
    Character c = Character(1, 2, 3, 4, 'A');
    c.MoveGlyph(1, 2);
    ASSERT_EQ(c.GetPosition().x, 2);
    ASSERT_EQ(c.GetPosition().y, 4);
}

TEST(Glyph_MoveGlyph2, GlyphMoveGlyphZero_WhenCalled_NotChangesPositionOfGlyph) {
    Character c = Character(1, 2, 3, 4, 'A');
    c.MoveGlyph(0, 0);
    ASSERT_EQ(c.GetPosition().x, 1);
    ASSERT_EQ(c.GetPosition().y, 2);
}

TEST(Glyph_MoveGlyph3, GlyphMoveGlyphNegative_WhenCalled_ChangesPositionOfGlyph) {
    Character c = Character(1, 2, 3, 4, 'A');
    c.MoveGlyph(-1, -1);
    ASSERT_EQ(c.GetPosition().x, 0);
    ASSERT_EQ(c.GetPosition().y, 1);
}

TEST(Glyph_MoveGlyph4, GlyphMoveGlyphNegative_WhenCalled_AssertFailed) {
    Character c = Character(1, 2, 3, 4, 'A');
    ASSERT_DEATH(c.MoveGlyph(-2, -3), "Cannot move glyph due to these coordinates");
}

TEST(Glyph_SetPosition1, GlyphSetPosition_WhenCalled_ChangesPositionOfGlyph) {
    Character c = Character(1, 2, 3, 4, 'A');

    c.SetPosition({6, 7});
    ASSERT_EQ(c.GetPosition().x, 6);
    ASSERT_EQ(c.GetPosition().y, 7);
}

TEST(Glyph_SetPosition2, GlyphSetPosition_WhenCalled_ChangesPositionOfGlyph) {
    Character c = Character(1, 2, 3, 4, 'A');

    c.SetPosition(6, 7);
    ASSERT_EQ(c.GetPosition().x, 6);
    ASSERT_EQ(c.GetPosition().y, 7);
}

TEST(Glyph_SetWidth1, GlyphSetWidth_WhenCalled_ChangesWidthOfGlyph) {
    Character c = Character(1, 2, 3, 4, 'A');

    c.SetWidth(5);
    ASSERT_EQ(c.GetPosition().x, 1);
    ASSERT_EQ(c.GetPosition().y, 2);
    ASSERT_EQ(c.GetWidth(), 5);
    ASSERT_EQ(c.GetHeight(), 4);
}

TEST(Glyph_SetWidth2, GlyphSetWidth_WhenCalled_AssertFailed) {
    Character c = Character(1, 2, 3, 4, 'A');

    ASSERT_DEATH(c.SetWidth(-1), "Invalid width of glyph");
}

TEST(Glyph_SetHeight, GlyphSetHeight_WhenCalled_ChangesHeightOfGlyph) {
    Character c = Character(1, 2, 3, 4, 'A');

    c.SetHeight(5);
    ASSERT_EQ(c.GetPosition().x, 1);
    ASSERT_EQ(c.GetPosition().y, 2);
    ASSERT_EQ(c.GetWidth(), 3);
    ASSERT_EQ(c.GetHeight(), 5);
}

TEST(Glyph_SetHeight2, GlyphSetHeight_WhenCalled_AssertFailed) {
    Character c = Character(1, 2, 3, 4, 'A');

    ASSERT_DEATH(c.SetHeight(-1), "Invalid height of glyph");
}

TEST(Glyph_SetParams1, GlyphSetParams_WhenCalled_ChangesParamsOfGlyph) {
    Character c = Character(1, 2, 3, 4, 'A');

    c.SetGlyphParams(5, 6, 7, 8);
    ASSERT_EQ(c.GetPosition().x, 5);
    ASSERT_EQ(c.GetPosition().y, 6);
    ASSERT_EQ(c.GetWidth(), 7);
    ASSERT_EQ(c.GetHeight(), 8);
}

TEST(Glyph_SetParams2, GlyphSetParams_WhenCalled_AssertFailed) {
    Character c = Character(1, 2, 3, 4, 'A');

    ASSERT_DEATH(c.SetGlyphParams(-5, 6, 7, 8), "Invalid params of glyph");
}

TEST(Glyph_GetBorders, GlyphGetBorders_WhenCalled_ReturnsBottomAndRightBordersOfGlyph) {
    Character c = Character(1, 2, 3, 4, 'A');

    ASSERT_EQ(c.GetBottomBorder(), 6);
    ASSERT_EQ(c.GetRightBorder(), 4);
}

//---------------------------------------Character------------------------------------------------------

TEST(Character_Constructor, CharacterConstructor_WhenCalled_CreatesCharacter) {
    Character c = Character(1, 2, 3, 4, 'A');

    ASSERT_EQ(c.GetPosition().x, 1);
    ASSERT_EQ(c.GetPosition().y, 2);
    ASSERT_EQ(c.GetWidth(), 3);
    ASSERT_EQ(c.GetHeight(), 4);
    ASSERT_EQ(c.GetChar(), 'A');
}

TEST(Character_GetChar, CharacterGetChar_WhenCalled_ReturnsSymbol) {
    Character c = Character(1, 2, 3, 4, 'A');

    ASSERT_EQ(c.GetChar(), 'A');
}

TEST(Character_SetChar, CharacterSetChar_WhenCalled_ChangesSymbol) {
    Character c = Character(1, 2, 3, 4, 'A');

    c.SetChar('F');
    ASSERT_EQ(c.GetChar(), 'F');
}

//-------------------------------------GlyphContainer-------------------------------------------------

TEST(GlyphContainer_Constructor, GlyphContainerConstructor_WhenCalled_CreatesGlyphContainer) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);

    ASSERT_EQ(rowPtr->GetPosition().x, 1);
    ASSERT_EQ(rowPtr->GetPosition().y, 2);
    ASSERT_EQ(rowPtr->GetWidth(), 3);
    ASSERT_EQ(rowPtr->GetHeight(), 4);
}

TEST(GlyphContainer_GetGlyphIndex1, GlyphContainerGetGlyphIndex_WhenCalled_ReturnsIndexOfGlyph) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    rowPtr->Add(cPtr);

    ASSERT_EQ(rowPtr->GetGlyphIndex(cPtr), 0);
}

TEST(GlyphContainer_GetGlyphIndex2, GlyphContainerGetGlyphIndex_WhenCalled_ReturnsIndexOfGlyph) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    rowPtr->Add(cPtr);
    ASSERT_EQ(rowPtr->GetGlyphIndex(cPtr), 0);

    Character c2 = Character(1, 2, 3, 4, 'B');
    Glyph::GlyphPtr c2Ptr = std::make_shared<Character>(c2);
    rowPtr->Add(c2Ptr);
    ASSERT_EQ(rowPtr->GetGlyphIndex(cPtr), 0);
    ASSERT_EQ(rowPtr->GetGlyphIndex(c2Ptr), 1);
}

TEST(GlyphContainer_GetGlyphIndex3, GlyphContainerGetGlyphIndex_WhenCalled_AssertFailed) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);

    ASSERT_DEATH(rowPtr->GetGlyphIndex(cPtr), "GlyphContainer doesn't contain this glyph");
}

TEST(GlyphContainer_GetGlyphByIndex1, GlyphContainerGetGlyphByIndex_WhenCalled_ReturnsGlyphPtr) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    rowPtr->Add(cPtr);

    ASSERT_EQ(rowPtr->GetGlyphByIndex(0), cPtr);
}

TEST(GlyphContainer_GetGlyphByIndex2, GlyphContainerGetGlyphByIndex_WhenCalled_ReturnsNullPtr) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    rowPtr->Add(cPtr);

    ASSERT_EQ(rowPtr->GetGlyphByIndex(1), nullptr);
}

TEST(GlyphContainer_GetGlyphByIndex3, GlyphContainerGetGlyphByIndex_WhenCalled_ReturnsNullPtr) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    rowPtr->Add(cPtr);

    ASSERT_DEATH(rowPtr->GetGlyphByIndex(-1), "Invalid index of glyph");
}

TEST(GlyphContainer_Find1, GlyphContainerFind_WhenCalled_ReturnsGlyphPtr) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    rowPtr->Add(cPtr);

    Character c2 = Character(5, 6, 7, 8, 'B');
    Glyph::GlyphPtr c2Ptr = std::make_shared<Character>(c2);
    rowPtr->Add(c2Ptr);

    ASSERT_EQ(rowPtr->Find(Point(1, 2)), cPtr);
}

TEST(GlyphContainer_Find2, GlyphContainerFind_WhenCalled_ReturnsGlyphPtr) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    rowPtr->Add(cPtr);

    Character c2 = Character(5, 6, 7, 8, 'B');
    Glyph::GlyphPtr c2Ptr = std::make_shared<Character>(c2);
    rowPtr->Add(c2Ptr);

    ASSERT_EQ(rowPtr->Find(Point(0, 0)), nullptr);
}

TEST(GlyphContainer_Find3, GlyphContainerFind_WhenCalled_ReturnsFirstGlyphPtr) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    rowPtr->Add(cPtr);

    Character c2 = Character(1, 2, 3, 4, 'B');
    Glyph::GlyphPtr c2Ptr = std::make_shared<Character>(c2);
    rowPtr->Add(c2Ptr);

    ASSERT_EQ(rowPtr->Find(Point(1, 2)), cPtr);
}

TEST(GlyphContainer_Add1, GlyphContainerAdd_WhenCalled_AddsGlyph) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    rowPtr->Add(cPtr);

    ASSERT_EQ(rowPtr->GetGlyphIndex(cPtr), 0);
}

TEST(GlyphContainer_Insert1, GlyphContainerInsert_WhenCalled_InsertsGlyphByPosition) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    rowPtr->Insert(cPtr, 0);

    ASSERT_EQ(rowPtr->GetGlyphIndex(cPtr), 0);
}

TEST(GlyphContainer_Insert2, GlyphContainerInsert_WhenCalled_InsertsGlyphByPosition) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    rowPtr->Insert(cPtr, 3);

    ASSERT_EQ(rowPtr->GetGlyphIndex(cPtr), 0);
}

TEST(GlyphContainer_Insert3, GlyphContainerInsert_WhenCalled_InsertsGlyphByPosition) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c1 = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr c1Ptr = std::make_shared<Character>(c1);
    Character c2 = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr c2Ptr = std::make_shared<Character>(c2);
    Character c3 = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr c3Ptr = std::make_shared<Character>(c3);
    rowPtr->Insert(c1Ptr, 0);
    rowPtr->Insert(c2Ptr, 1);
    rowPtr->Insert(c3Ptr, 1);

    ASSERT_EQ(rowPtr->GetGlyphIndex(c1Ptr), 0);
    ASSERT_EQ(rowPtr->GetGlyphIndex(c2Ptr), 2);
    ASSERT_EQ(rowPtr->GetGlyphIndex(c3Ptr), 1);
}

TEST(GlyphContainer_Insert4, GlyphContainerInsert_WhenCalled_AssertFailed) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);

    ASSERT_DEATH(rowPtr->Insert(cPtr, -1), "Invalid position for inserting glyph");
}

TEST(GlyphContainer_MoveGlyph1, GlyphContainerMoveGlyph_WhenCalled_MoveAllGlyphsInComponents) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c1 = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr c1Ptr = std::make_shared<Character>(c1);
    Character c2 = Character(5, 6, 7, 8, 'B');
    Glyph::GlyphPtr c2Ptr = std::make_shared<Character>(c2);
    rowPtr->Insert(c1Ptr, 0);
    rowPtr->Insert(c2Ptr, 1);

    rowPtr->MoveGlyph(1, 2);

    Glyph::GlyphPtr c1PtrNew = rowPtr->GetGlyphByIndex(0);
    Glyph::GlyphPtr c2PtrNew = rowPtr->GetGlyphByIndex(1);

    ASSERT_EQ(c1PtrNew->GetPosition().x, 2);
    ASSERT_EQ(c1PtrNew->GetPosition().y, 4);
    ASSERT_EQ(c1PtrNew->GetWidth(), 3);
    ASSERT_EQ(c1PtrNew->GetHeight(), 4);

    ASSERT_EQ(c2PtrNew->GetPosition().x, 6);
    ASSERT_EQ(c2PtrNew->GetPosition().y, 8);
    ASSERT_EQ(c2PtrNew->GetWidth(), 7);
    ASSERT_EQ(c2PtrNew->GetHeight(), 8);
}

TEST(GlyphContainer_MoveGlyph2, GlyphContainerMoveGlyph_WhenCalled_AssertFailed) {
    Row r = Row(1, 2, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);

    ASSERT_DEATH(rowPtr->MoveGlyph(-2, 1), "Cannot move glyph due to these coordinates");
}

TEST(GlyphContainer_MoveGlyph3, GlyphContainerMoveGlyph_WhenCalled_MoveAllGlyphsInComponents) {
    Row r = Row(5, 5, 3, 4);
    std::shared_ptr<GlyphContainer> rowPtr = std::make_shared<Row>(r);
    Character c1 = Character(1, 2, 3, 4, 'A');
    Glyph::GlyphPtr c1Ptr = std::make_shared<Character>(c1);
    Character c2 = Character(5, 6, 7, 8, 'B');
    Glyph::GlyphPtr c2Ptr = std::make_shared<Character>(c2);
    rowPtr->Insert(c1Ptr, 0);
    rowPtr->Insert(c2Ptr, 1);

    ASSERT_DEATH(rowPtr->MoveGlyph(-2, 1), "Cannot move glyph due to these coordinates");
}

// -----------------------------Row------------------------------------------------------

TEST(Row_Constructor, RowConstructor_WhenCalled_CreatesEmptyRow) {
    Row r = Row(1, 2, 3, 4);
    
    ASSERT_EQ(r.GetPosition().x, 1);
    ASSERT_EQ(r.GetPosition().y, 2);
    ASSERT_EQ(r.GetWidth(), 3);
    ASSERT_EQ(r.GetHeight(), 4);
    ASSERT_EQ(r.GetGlyphByIndex(0), nullptr);
    ASSERT_EQ(r.GetUsedSpace(), 0);
    ASSERT_EQ(r.GetFreeSpace(), 3);
}

TEST(Row_Insert1, RowInsertGlyph_WhenCalled_InsertsGlyphInEmptyRowByPosition) {
    Row r = Row(1, 2, 5, 1);
    
    Character c = Character(1, 2, 1, 1, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    
    ASSERT_TRUE(r.Insert(cPtr).size() == 0);

    ASSERT_EQ(r.GetPosition().x, 1);
    ASSERT_EQ(r.GetPosition().y, 2);
    ASSERT_EQ(r.GetWidth(), 5);
    ASSERT_EQ(r.GetHeight(), 1);
    ASSERT_EQ(r.GetGlyphByIndex(0), cPtr);
    ASSERT_EQ(r.GetGlyphIndex(cPtr), 0);
    ASSERT_EQ(r.GetUsedSpace(), 1);
    ASSERT_EQ(r.GetFreeSpace(), 4);
    ASSERT_FALSE(r.IsEmpty());
    ASSERT_FALSE(r.IsFull());
}

TEST(Row_Insert2, RowInsertGlyphWithTheSameSize_WhenCalled_BecomeFull) {
    Row r = Row(1, 2, 5, 1);
    
    Character c = Character(1, 2, 5, 1, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    
    ASSERT_TRUE(r.Insert(cPtr).size() == 0);

    ASSERT_EQ(r.GetPosition().x, 1);
    ASSERT_EQ(r.GetPosition().y, 2);
    ASSERT_EQ(r.GetWidth(), 5);
    ASSERT_EQ(r.GetHeight(), 1);
    ASSERT_EQ(r.GetGlyphByIndex(0), cPtr);
    ASSERT_EQ(r.GetGlyphIndex(cPtr), 0);
    ASSERT_EQ(r.GetUsedSpace(), 5);
    ASSERT_EQ(r.GetFreeSpace(), 0);
    ASSERT_FALSE(r.IsEmpty());
    ASSERT_TRUE(r.IsFull());
}

TEST(Row_Insert2, RowInsertBigGlyph_WhenCalled_CannotInsertBigGlyph) {
    Row r = Row(1, 2, 5, 1);
    
    Character c = Character(1, 2, 6, 1, 'A');
    Glyph::GlyphPtr cPtr = std::make_shared<Character>(c);
    std::list<Glyph::GlyphPtr> list = r.Insert(cPtr);

    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list.front(), cPtr);

    ASSERT_EQ(r.GetPosition().x, 1);
    ASSERT_EQ(r.GetPosition().y, 2);
    ASSERT_EQ(r.GetWidth(), 5);
    ASSERT_EQ(r.GetHeight(), 1);
    ASSERT_EQ(r.GetGlyphByIndex(0), nullptr);
    ASSERT_DEATH(r.GetGlyphIndex(cPtr), "GlyphContainer doesn't contain this glyph");
    ASSERT_EQ(r.GetUsedSpace(), 0);
    ASSERT_EQ(r.GetFreeSpace(), 5);
    ASSERT_TRUE(r.IsEmpty());
    ASSERT_FALSE(r.IsFull());
}

// TEST(Row_Remove1, RowRemove_WhenCalled_RemovesGlyphFromRow) {
//     Character c1 = Character(1, 2, 3, 4, 'A');
//     Glyph::GlyphPtr c1Ptr = std::make_shared<Character>(c1);
//     Character c2 = Character(5, 6, 7, 8, 'B');
//     Glyph::GlyphPtr c2Ptr = std::make_shared<Character>(c2);
//     GlyphContainer::GlyphList list;
//     list.push_back(c1Ptr);
//     list.push_back(c2Ptr);

//     Row r = Row(1, 2, 3, 4, std::move(list));
//     r.Remove(c1Ptr);
    
//     ASSERT_EQ(r.GetPosition().x, 1);
//     ASSERT_EQ(r.GetPosition().y, 2);
//     ASSERT_EQ(r.GetWidth(), 3);
//     ASSERT_EQ(r.GetHeight(), 4);
//     ASSERT_EQ(r.GetGlyphIndex(c2Ptr), 0);
//     ASSERT_DEATH(r.GetGlyphIndex(c1Ptr), "GlyphContainer doesn't contain this glyph");
//     ASSERT_EQ(r.GetGlyphByIndex(0), c2Ptr);
//     ASSERT_EQ(r.GetGlyphByIndex(1), nullptr);
// }

// TEST(Row_Remove2, RowRemoveNullPtr_WhenCalled_RemoveNothing) {
//     Character c1 = Character(1, 2, 3, 4, 'A');
//     Glyph::GlyphPtr c1Ptr = std::make_shared<Character>(c1);
//     Character c2 = Character(5, 6, 7, 8, 'B');
//     Glyph::GlyphPtr c2Ptr = std::make_shared<Character>(c2);
//     GlyphContainer::GlyphList list;
//     list.push_back(c1Ptr);
//     list.push_back(c2Ptr);

//     Row r = Row(1, 2, 3, 4, std::move(list));
//     r.Remove(nullptr);
    
//     ASSERT_EQ(r.GetPosition().x, 1);
//     ASSERT_EQ(r.GetPosition().y, 2);
//     ASSERT_EQ(r.GetWidth(), 3);
//     ASSERT_EQ(r.GetHeight(), 4);
//     ASSERT_EQ(r.GetGlyphIndex(c1Ptr), 0);
//     ASSERT_EQ(r.GetGlyphIndex(c2Ptr), 1);
//     ASSERT_EQ(r.GetGlyphByIndex(0), c1Ptr);
//     ASSERT_EQ(r.GetGlyphByIndex(1), c2Ptr);
// }