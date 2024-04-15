#ifndef TEXT_EDITOR_WINDOW
#define TEXT_EDITOR_WINDOW

#include <memory>
#include "composition.h"
#include "glyph.h"

/**
 * A class representing a window to display a text editor.
 */
class Window: public Composition {
public:
    explicit Window(const GlyphParams&);
    Window(const GlyphParams&, Window*);
    ~Window() override;

protected:
};

#endif  // TEXT_EDITOR_WINDOW