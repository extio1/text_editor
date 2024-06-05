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
    MOCK_METHOD(void, InsertChar, (char symbol), (override));
    MOCK_METHOD(char, RemoveChar, (), (override));
    MOCK_METHOD(void, DrawDocument, (), (override));
    MOCK_METHOD(void, MoveCursorLeft, (), (override));
    MOCK_METHOD(void, MoveCursorRight, (), (override));
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

    auto c1 = std::make_shared<InsertCharacter>(d_mock, 'A');
    auto c2 = std::make_shared<InsertCharacter>(d_mock, 'B');
    auto c3 = std::make_shared<InsertCharacter>(d_mock, 'C');
    auto c4 = std::make_shared<InsertCharacter>(d_mock, 'D');

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c1->character))).Times(1);
    e.Do(std::move(c1));
    // c1

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c2->character))).Times(1);
    e.Do(std::move(c2));
    // c1 - c2

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c3->character))).Times(1);
    e.Do(std::move(c3));
    // c1 - c2 - c3

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c4->character))).Times(1);
    e.Do(std::move(c4));
    // c4 - c2 - c3

    EXPECT_CALL(*d_mock.get(), RemoveChar()).Times(1);
    e.Undo();
    // .c4 - c2 - c3

    EXPECT_CALL(*d_mock.get(), RemoveChar()).Times(1);
    e.Undo();
    // .c4 - .c2 - c3

    EXPECT_CALL(*d_mock.get(), InsertChar(_)).Times(1);
    e.Redo();
    // .c4 - c2 - c3

    EXPECT_CALL(*d_mock.get(), InsertChar(_)).Times(1);
    e.Redo();
    // c4 - c2 - c3

    EXPECT_CALL(*d_mock.get(), InsertChar(_)).Times(0);
    e.Redo();
    // c4 - c2 - c3
}

TEST(ExecutorDoUndoRedo, WhenCalled_WraparoundUndo_Correct){
    auto e = Executor(3);
    auto d_mock = std::make_shared<DocumentMock>();

    auto c1 = std::make_shared<InsertCharacter>(d_mock, 'A');
    auto c2 = std::make_shared<InsertCharacter>(d_mock, 'B');
    auto c3 = std::make_shared<InsertCharacter>(d_mock, 'C');
    auto c4 = std::make_shared<InsertCharacter>(d_mock, 'D');

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c1->character))).Times(1);
    e.Do(std::move(c1));
    // c1

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c2->character))).Times(1);
    e.Do(std::move(c2));
    // c1 - c2

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c3->character))).Times(1);
    e.Do(std::move(c3));
    // c1 - c2 - c3

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c4->character))).Times(1);
    e.Do(std::move(c4));
    // c4 - c2 - c3

    EXPECT_CALL(*d_mock.get(), RemoveChar()).Times(1);
    e.Undo();
    // c4 - c2 - .c3

    EXPECT_CALL(*d_mock.get(), RemoveChar()).Times(1);
    e.Undo();
    // c4 - .c2 - .c3

    EXPECT_CALL(*d_mock.get(), RemoveChar()).Times(1);
    e.Undo();
    // .c4 - .c2 - .c3

    EXPECT_CALL(*d_mock.get(), RemoveChar()).Times(0);
    e.Undo();
    // .c4 - .c2 - .c3
}

TEST(ExecutorDoUndoRedo, WhenCalled_DoDoDoUndoUndoDoRedo_RedoDoNothing){
    auto e = Executor(3);
    auto d_mock = std::make_shared<DocumentMock>();

    auto c1 = std::make_shared<InsertCharacter>(d_mock, 'A');
    auto c2 = std::make_shared<InsertCharacter>(d_mock, 'B');
    auto c3 = std::make_shared<InsertCharacter>(d_mock, 'C');
    auto c4 = std::make_shared<InsertCharacter>(d_mock, 'D');

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c1->character))).Times(1);
    e.Do(std::move(c1));
    // c1

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c2->character))).Times(1);
    e.Do(std::move(c2));
    // c1 - c2

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c3->character))).Times(1);
    e.Do(std::move(c3));
    // c1 - c2 - c3

    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c4->character))).Times(1);
    e.Do(std::move(c4));
    // c4 - c2 - c3

    EXPECT_CALL(*d_mock.get(), RemoveChar()).Times(1);
    e.Undo();
    // .c4 - c2 - c3

    EXPECT_CALL(*d_mock.get(), RemoveChar()).Times(1);
    e.Undo();
    // .c4 - c2 - .c3

    auto c5 = std::make_shared<InsertCharacter>(d_mock, 'F');
    EXPECT_CALL(*d_mock.get(), InsertChar(Eq(c5->character))).Times(1);
    e.Do(std::move(c5));
    // .c4 - c2 - c5

    // after new command inserted future history is not valid anymore
    // future before Redo is c4 - this mustn't be executed
    EXPECT_CALL(*d_mock.get(), InsertChar(_)).Times(0);
    e.Redo();
    // .c4 - c2 - c5
}