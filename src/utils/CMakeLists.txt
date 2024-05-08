set(target point) 

set(sources 
    "point.cpp"
)

add_library(point SHARED ${sources})
target_include_directories(point PUBLIC ${include_dir})