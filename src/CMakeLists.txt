# 命名变量
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)


# file(GLOB SRC_SDL
#         "${SOURCE_DIR}/sdl/*.cpp")
# add_library(SDL SHARED ${SRC_SDL})

file(GLOB SRC_UTILS
        "${SOURCE_DIR}/utils/*.cpp")
add_library(UTILS SHARED ${SRC_UTILS})
