#ifndef TEXT_EDITOR_BUTTON
#define TEXT_EDITOR_BUTTON

#include <string>
#include "glyph.h"

class Button: public Glyph
{
public:
    explicit Button(const int x, const int y, const int width, const int height, const std::string& name);
    void Draw() override;
    void Add(GlyphPtr) override {}
    void Insert(GlyphPtr, int) {}
    bool IsPressed() const;

private:
    std::string name;
    bool isPressed = false;
};

#endif  // TEXT_EDITOR_BUTTON