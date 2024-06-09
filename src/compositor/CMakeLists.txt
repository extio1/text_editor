set(target compositor) 

set(sources 
    "compositor.cpp"
    "simple_compositor/simple_compositor.cpp"
)

add_library(compositor SHARED ${sources})
target_include_directories(compositor PUBLIC ${include_dir})