cmake_minimum_required(VERSION 3.10)

#Set up project
project(fake-paint VERSION 1.0)

#Set executable
set(SOURCES
    src/button.cpp
    src/canvas.cpp
    src/main.cpp
    src/tool_strategy/fill_bucket_tool_strategy.cpp
    src/tool_strategy/line_tool_strategy.cpp
    src/tool_strategy/paint_brush_strategy.cpp
    src/tool_strategy/pencil_tool_strategy.cpp
    src/tool_strategy/spray_can_strategy.cpp
    src/tool_strategy/square_tool_strategy.cpp
    src/tool_strategy/eraser_tool_strategy.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

#Set C++17
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

#Set flags
if(MSVC)
  	target_compile_options(${PROJECT_NAME} PRIVATE 
    	/W4 /WX)
else()
  	target_compile_options(${PROJECT_NAME} PRIVATE 
		-Wall -Wextra -pedantic -Werror)		#Warning flags
endif()

#Set module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

#Find libraries
find_package(Threads)
find_package(SFML REQUIRED audio network graphics window system)

#Finally
target_link_libraries(${PROJECT_NAME} 
    Threads::Threads 
    ${SFML_LIBRARIES} 
    ${SFML_DEPENDENCIES}
)
