set(target document) 

set(sources 
    "document.cpp"
    "glyphs/button.cpp"
    "glyphs/character.cpp"
    "glyphs/column.cpp"
    "glyphs/glyph_container.cpp"
    "glyphs/glyph.cpp"
    "glyphs/monoglyph.cpp"
    "glyphs/page.cpp"
    "glyphs/row.cpp"
)

add_library(document SHARED ${sources})
target_include_directories(document PUBLIC ${include_dir})
