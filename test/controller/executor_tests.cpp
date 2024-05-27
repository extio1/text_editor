#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define private public

#include "document/document.h"

#include "executor/executor.h"
#include "executor/command/insert_character.h"

class DocumentMock : public IDocument {
public:
    MOCK_METHOD(void, Insert, (Glyph::GlyphPtr& glyph), (override));
    MOCK_METHOD(void, Remove, (Glyph::GlyphPtr& glyph), (override));
    MOCK_METHOD(void, SelectGlyphs, (const Point& start, const Point& end), (override));
    MOCK_METHOD(Glyph::GlyphList, PasteGlyphs, (const Point& to_point), (override));
    MOCK_METHOD(void, CutGlyphs, (const Point& start, const Point& end), (override));
};


TEST(Executor_Construct, WhenCalled_WithProperArguments_Correct) {
    for (std::size_t i = 0; i < 100; ++i){
        auto executor = Executor(i);
        ASSERT_EQ(executor.command_history.buffer.size(), i);
    }

    auto executor = Executor(42);
}

TEST(Executor_Construct, WhenCalled_WithNegativeArguments_ThrowException) {
    for (int i = -100; i < 0; ++i){
        EXPECT_THROW({Executor e(i);}, std::length_error);
    }
}

using ::testing::NotNull;
using ::testing::AtLeast;
using ::testing::Eq;
using ::testing::_;
TEST(ExecutorDoUndoRedo, WhenCalled_DoUndoRedo_Correct){
    auto e = Executor(3);
    auto d_mock = std::make_shared<DocumentMock>();

    auto c1 = std::make_shared<InsertCharacter>(d_mock, 0, 0, 10, 20, 'A');
    auto c2 = std::make_shared<InsertCharacter>(d_mock, 10, 0, 10, 20, 'B');
    auto c3 = std::make_shared<InsertCharacter>(d_mock, 20, 0, 10, 20, 'C');
    auto c4 = std::make_shared<InsertCharacter>(d_mock, 30, 0, 10, 20, 'D');

    EXPECT_CALL(*d_mock.get(), Insert(Eq(c1->character))).Times(1);
    e.Do(std::move(c1));
    // c1

    EXPECT_CALL(*d_mock.get(), Insert(Eq(c2->character))).Times(1);
    e.Do(std::move(c2));
    // c1 - c2

    EXPECT_CALL(*d_mock.get(), Insert(Eq(c3->character))).Times(1);
    e.Do(std::move(c3));
    // c1 - c2 - c3

    EXPECT_CALL(*d_mock.get(), Insert(Eq(c4->character))).Times(1);
    e.Do(std::move(c4));
    // c2 - c3 - c4

    EXPECT_CALL(*d_mock.get(), Remove(_)).Times(1);
    e.Undo();
    // c2 - c3

    EXPECT_CALL(*d_mock.get(), Insert(_)).Times(1);
    e.Redo();
    // c2 - c3 - c4
}

TEST(ExecutorDoUndoRedo, WhenCalled_WraparoundUndoRedo_Correct){
    auto e = Executor(3);
    auto d_mock = std::make_shared<DocumentMock>();

    auto c1 = std::make_shared<InsertCharacter>(d_mock, 0, 0, 10, 20, 'A');
    auto c2 = std::make_shared<InsertCharacter>(d_mock, 10, 0, 10, 20, 'B');
    auto c3 = std::make_shared<InsertCharacter>(d_mock, 20, 0, 10, 20, 'C');
    auto c4 = std::make_shared<InsertCharacter>(d_mock, 30, 0, 10, 20, 'D');

    EXPECT_CALL(*d_mock.get(), Insert(Eq(c1->character))).Times(1);
    e.Do(std::move(c1));
    // c1

    EXPECT_CALL(*d_mock.get(), Insert(Eq(c2->character))).Times(1);
    e.Do(std::move(c2));
    // c1 - c2

    EXPECT_CALL(*d_mock.get(), Insert(Eq(c3->character))).Times(1);
    e.Do(std::move(c3));
    // c1 - c2 - c3

    EXPECT_CALL(*d_mock.get(), Insert(Eq(c4->character))).Times(1);
    e.Do(std::move(c4));
    // c2 - c3 - c4

    EXPECT_CALL(*d_mock.get(), Remove(_)).Times(1);
    e.Undo();
    // c2 - c3

    EXPECT_CALL(*d_mock.get(), Remove(_)).Times(1);
    e.Undo();
    // c2

    EXPECT_CALL(*d_mock.get(), Remove(_)).Times(1);
    e.Undo();
    //

    EXPECT_CALL(*d_mock.get(), Remove(_)).Times(0);
    e.Undo();
    //

    
}