set(target executor) 

set(sources 
    "executor.cpp"
    "command/insert_symbol.cpp"
)

add_library(executor SHARED ${sources})
target_include_directories(executor PUBLIC ${include_dir})
