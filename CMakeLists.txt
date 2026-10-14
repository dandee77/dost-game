cmake_minimum_required(VERSION 3.11) 
project(SpaceAblaze)

option(GAME_DEBUG "Enable debug keys and overlay" OFF)
option(GAME_COLLISION_TESTS "Build collision regression tests and rendered benchmark" OFF)
option(GAME_EQUIPMENT_TESTS "Build player equipment integration tests" OFF)
set(GAME_COLLISION_REFERENCE "" CACHE FILEPATH "Optional original Game.cpp for benchmark comparison")


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) 
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) 
  endif()
endif()


file(GLOB_RECURSE SOURCES "src/*.cpp")

if (NOT SOURCES)
  message(FATAL_ERROR "No source files found in the src/ directory.")
endif()


add_executable(${PROJECT_NAME} ${SOURCES})

if (GAME_DEBUG)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GAME_DEBUG)
endif()

# hide console window on Windows
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

target_link_libraries(${PROJECT_NAME} raylib)

#? copy assets to build directory after building
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMENT "Copying assets to build directory"
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /wd4244)
    # Keep the windowed executable while using the existing standard main().
    set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY LINK_FLAGS " /ENTRY:mainCRTStartup")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()


if (PLATFORM STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html") 
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()


if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

if (GAME_COLLISION_TESTS)
    enable_testing()
    add_executable(SpatialGridTests tests/SpatialGridTests.cpp src/SpatialGrid.cpp)
    target_include_directories(SpatialGridTests PRIVATE src)
    target_link_libraries(SpatialGridTests raylib)
    add_test(NAME SpatialGridParity COMMAND SpatialGridTests)

    set(COLLISION_SOURCES ${SOURCES})
    list(FILTER COLLISION_SOURCES EXCLUDE REGEX "/main\\.cpp$")
    if (GAME_COLLISION_REFERENCE)
        list(FILTER COLLISION_SOURCES EXCLUDE REGEX "/Game\\.cpp$")
        list(APPEND COLLISION_SOURCES "${GAME_COLLISION_REFERENCE}")
    endif()
    add_executable(CollisionBenchmark tests/CollisionBenchmark.cpp tests/NormalAccess.cpp ${COLLISION_SOURCES})
    target_include_directories(CollisionBenchmark PRIVATE src)
    target_link_libraries(CollisionBenchmark raylib)
    add_executable(CollisionRegression tests/CollisionRegression.cpp tests/NormalAccess.cpp ${COLLISION_SOURCES})
    target_include_directories(CollisionRegression PRIVATE src)
    target_link_libraries(CollisionRegression raylib)
    if (GAME_DEBUG)
        target_compile_definitions(CollisionBenchmark PRIVATE GAME_DEBUG)
        target_compile_definitions(CollisionRegression PRIVATE GAME_DEBUG)
    endif()
    foreach(COLLISION_TARGET SpatialGridTests CollisionBenchmark CollisionRegression)
        if (MSVC)
            target_compile_options(${COLLISION_TARGET} PRIVATE /W3 /wd4244)
        else()
            target_compile_options(${COLLISION_TARGET} PRIVATE -Wall -Wextra)
        endif()
    endforeach()
endif()

if (GAME_EQUIPMENT_TESTS)
    enable_testing()
    set(EQUIPMENT_SOURCES ${SOURCES})
    list(FILTER EQUIPMENT_SOURCES EXCLUDE REGEX "/main\\.cpp$")
    add_executable(PlayerEquipmentTests tests/PlayerEquipmentTests.cpp tests/EquipmentAccess.cpp tests/NormalAccess.cpp ${EQUIPMENT_SOURCES})
    target_include_directories(PlayerEquipmentTests PRIVATE src)
    target_link_libraries(PlayerEquipmentTests raylib)
    if (GAME_DEBUG)
        target_compile_definitions(PlayerEquipmentTests PRIVATE GAME_DEBUG)
    endif()
    if (MSVC)
        target_compile_options(PlayerEquipmentTests PRIVATE /W3 /wd4244)
    else()
        target_compile_options(PlayerEquipmentTests PRIVATE -Wall -Wextra)
    endif()
    add_test(NAME PlayerEquipment COMMAND PlayerEquipmentTests "${CMAKE_CURRENT_BINARY_DIR}")
    set_tests_properties(PlayerEquipment PROPERTIES WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()
