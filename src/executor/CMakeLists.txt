set(target executor) 

set(sources 
    "executor.cpp"
    "command/insert_character.cpp"
    "command/remove_character.cpp"
    "command/save_document.cpp"
    "command/load_document.cpp"
)

add_library(${target} SHARED ${sources})
target_link_libraries(${target} PRIVATE ${Boost_LIBRARIES})
target_include_directories(${target} PUBLIC ${include_dir})
