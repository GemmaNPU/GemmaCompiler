cmake_minimum_required(VERSION 3.20)
project(gemmas)

set( TARGET ${PROJECT_NAME} )
set( TARGETWASM ${PROJECTNAME}wasm )
set( TARGETTEST ${PROJECT_NAME}test )
set( CMAKE_CXX_STANDARD 23)
set( CMAKE_CXX_STANDARD_REQUIRED ON)

set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include" )
set( TEST_PATH "${PROJECT_SOURCE_DIR}/tests" )

include(FetchContent)
FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse.git
  )
  FetchContent_MakeAvailable(argparse)

#  generated using  `find . -type f -printf "%T@ %p\n" | sort -nr | cut -d\  -f2-`
set( HPPS "${INCLUDE_PATH}/assembler/formatters/human_hex_formatter.hpp"
          "${INCLUDE_PATH}/assembler/formatters/instruction_formatter.hpp"
          "${INCLUDE_PATH}/assembler/instructions/definitions.hpp"
          "${INCLUDE_PATH}/assembler/instructions/halt.hpp"
          "${INCLUDE_PATH}/assembler/instructions/instructions_set.hpp"
          "${INCLUDE_PATH}/assembler/instructions/nop.hpp"
          "${INCLUDE_PATH}/assembler/assembler.hpp"
          "${INCLUDE_PATH}/assembler/errors.hpp"
          "${INCLUDE_PATH}/assembler/scanner.hpp"
           )
file( GLOB_RECURSE TEST_CPPS "${TEST_PATH}/*.cpp" )

if (DEFINED EMSCRIPTEN)
  add_executable( ${TARGETWASM} ${SOURCE_PATH}/wasm.cpp ${INCLUDE_PATH}/wasm.hpp)
  target_include_directories( ${TARGETWASM} PUBLIC ${INCLUDE_PATH} )
  set_target_properties( ${TARGETWASM} PROPERTIES COMPILE_FLAGS "-Os")
  set_target_properties( ${TARGETWASM} PROPERTIES LINK_FLAGS    "-Os --no-entry -s EXPORTED_RUNTIME_METHODS='[\"cwrap\", \"allocate\", \"intArrayFromString\"]'")
else()
  add_executable( ${TARGET} src/main.cpp)
  add_executable( ${TARGETTEST} ${TEST_CPPS} )
  target_compile_features(${TARGET} PUBLIC cxx_std_23)
  target_link_libraries( ${TARGET} argparse  )
  target_include_directories( ${TARGET} PUBLIC ${INCLUDE_PATH} )
  target_compile_options( ${TARGET} PRIVATE -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion -Wunused-parameter -Wno-long-long -pedantic  -W -Wcast-qual -Wwrite-strings -Werror )
  install( 
    TARGETS ${TARGET} 
    RUNTIME DESTINATION 
    )
        
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  enable_testing()

  include_directories( ${INCLUDE_PATH} )

  target_link_libraries(
    ${TARGETTEST}
    GTest::gtest_main
    ${TARGETLIB}
  )

  include(GoogleTest)
  gtest_discover_tests(${TARGETTEST})

  find_package(Doxygen)
  if (DOXYGEN_FOUND)
      # set input and output files
      set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
      set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
      
      # request to configure the file
      configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
      message("Doxygen build started")

      # note the option ALL which allows to build the docs together with the application
      add_custom_target( doc_doxygen ALL
          COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Generating API documentation with Doxygen"
          VERBATIM )
          endif()
endif()