#ifndef GLYPH_H
#define GLYPH_H

#include <memory>

#include "geometry.h"
#include "window.h"

class Glyph{
public:
    virtual void draw(Window&) = 0;
    virtual Rectangle bounds() = 0; 

    virtual bool intersects(const Point&) = 0;

    virtual void insert(Glyph*, int) = 0;
    virtual void remove(Glyph*) = 0;
    virtual Glyph* child(int) = 0;
    virtual Glyph* parent() = 0;
protected:
    Glyph* parent;
};

class StringGlyph: public Glyph{
public:
    StringGlyph(Glyph*);

    virtual void draw(Window&) override;
    virtual Rectangle bounds() override; 

    virtual bool intersects(const Point&) override;

    virtual void insert(Glyph*, int) override;
    virtual void remove(Glyph*) override;
    virtual Glyph* child(int) override;
    virtual Glyph* parent() override;
private:
    Glyph* childs;
};

class CharacterGlyph: public Glyph{
public:
    CharacterGlyph(int);

    virtual void draw(Window&) override;
    virtual Rectangle bounds() override; 

    virtual bool intersects(const Point&) override;

    virtual void insert(Glyph*, int) override;
    virtual void remove(Glyph*) override;
    virtual Glyph* child(int) override;
    virtual Glyph* parent() override;
private:
    int symbol;
};

#endif /* GLYPH_H */
