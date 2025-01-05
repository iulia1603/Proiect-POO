# target definitions

if(GITHUB_ACTIONS)
    message("NOTE: GITHUB_ACTIONS defined")
    target_compile_definitions(${MAIN_EXECUTABLE_NAME} PRIVATE GITHUB_ACTIONS)
    target_compile_definitions(${MAIN_PROJECT_NAME}_lib PRIVATE GITHUB_ACTIONS)
endif()

###############################################################################

if(PROJECT_WARNINGS_AS_ERRORS)
    set_property(TARGET ${MAIN_EXECUTABLE_NAME} PROPERTY COMPILE_WARNING_AS_ERROR ON)
    set_property(TARGET ${MAIN_PROJECT_NAME}_lib PROPERTY COMPILE_WARNING_AS_ERROR ON)
endif()

# custom compiler flags
message("Compiler: ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
if(MSVC)
    target_compile_options(${MAIN_EXECUTABLE_NAME} PRIVATE /W4 /permissive- /wd4244 /wd4267 /wd4996 /external:anglebrackets /external:W0 /utf-8 /MP)
    target_compile_options(${MAIN_PROJECT_NAME}_lib PRIVATE /W4 /permissive- /wd4244 /wd4267 /wd4996 /external:anglebrackets /external:W0 /utf-8 /MP)
else()
    target_compile_options(${MAIN_EXECUTABLE_NAME} PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(${MAIN_PROJECT_NAME}_lib PRIVATE -Wall -Wextra -pedantic)
endif()

###############################################################################

# sanitizers
include(${CMAKE_HELPER_DIR}/CustomStdlibAndSanitizers.cmake)

set_custom_stdlib_and_sanitizers(${MAIN_EXECUTABLE_NAME} true)
set_custom_stdlib_and_sanitizers(${MAIN_PROJECT_NAME}_lib true)
