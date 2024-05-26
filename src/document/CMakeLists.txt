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

add_library(${target} SHARED ${sources})
target_link_libraries(${target} PUBLIC ${Boost_LIBRARIES})
target_include_directories(${target} PUBLIC ${include_dir})
