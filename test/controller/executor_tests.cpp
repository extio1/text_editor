#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define private public

#include "document/document.h"

#include "executor/executor.h"
#include "executor/command/insert_character.h"

// Where to put mock class??? (http://google.github.io/googletest/gmock_for_dummies.html#where-to-put-it)
class DocumentMock : public IDocument {
public:
    MOCK_METHOD(void, Insert, (Glyph::GlyphPtr& glyph), (override));
    MOCK_METHOD(void, Remove, (Glyph::GlyphPtr& glyph), (override));
    MOCK_METHOD(void, SelectGlyphs, (GlyphContainer::GlyphList& glyphs), (override));
    MOCK_METHOD(void, PasteGlyphs, (int x, int y), (override));
    MOCK_METHOD(void, CutGlyphs, (GlyphContainer::GlyphList& glyphs), (override));
};


TEST(Executor_Construct, WhenCalled_WithProperArguments_Correct) {
    for (std::size_t i = 0; i < 100; ++i){
        auto executor = Executor(i);
        ASSERT_EQ(executor.command_history.buffer.size(), i);
    }

    auto executor = Executor(42);
    ASSERT_EQ(executor.n_executed, 0);
    ASSERT_EQ(executor.n_unexecuted, 0);
}

TEST(Executor_Construct, WhenCalled_WithNegativeArguments_ThrowException) {
    for (int i = -100; i < 0; ++i){
        EXPECT_THROW({Executor e(i);}, std::length_error);
    }
}

using ::testing::NotNull;
using ::testing::AtLeast;
using ::testing::Eq;
TEST(InsertCommand, WhenCalled_DoUndoRedo_Correct){
    auto e = Executor(3);
    DocumentMock d_mock;

    auto c1 = std::make_shared<InsertCharacter>(d_mock, 0, 0, 10, 20, 'A');
    auto c2 = std::make_shared<InsertCharacter>(d_mock, 10, 0, 10, 20, 'B');
    auto c3 = std::make_shared<InsertCharacter>(d_mock, 20, 0, 10, 20, 'C');
    auto c4 = std::make_shared<InsertCharacter>(d_mock, 30, 0, 10, 20, 'D');

    EXPECT_CALL(d_mock, Insert(Eq(c1->character))).Times(1);
    e.Do(std::move(c1));

    EXPECT_CALL(d_mock, Insert(Eq(c2->character))).Times(1);
    e.Do(std::move(c2));

    EXPECT_CALL(d_mock, Insert(Eq(c3->character))).Times(1);
    e.Do(std::move(c3));

    EXPECT_CALL(d_mock, Insert(Eq(c4->character))).Times(1);
    e.Do(std::move(c4));

//    EXPECT_CALL(d_mock, Remove(Eq(c4->character))).Times(1);
//    e.Undo();

}
