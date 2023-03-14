cmake_minimum_required (VERSION 3.19.0)

project (StringFinder)

OPTION(WITH_MAIN "Enable main executable build" OFF)

set(SOURCES
    #headers
    include/string_finder/console.hpp
    include/string_finder/file.hpp
    include/string_finder/filequeue.hpp
    include/string_finder/filesystem.hpp
    include/string_finder/searcher.hpp

    #sources
    src/console.cpp
    src/file.cpp
    src/filequeue.cpp
    src/filesystem.cpp
    src/searcher.cpp
)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    # warning level 4
    add_compile_options(/W4 /WX)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -pthread)
endif()

add_library (${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
	PRIVATE
		"include"
		"src"
	SYSTEM INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if (WITH_MAIN)
    add_subdirectory(main)
endif ()