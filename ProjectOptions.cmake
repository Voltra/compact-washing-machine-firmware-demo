include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


include(CheckCXXSourceCompiles)


macro(compact_washing_machine_firmware_demo_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)

    message(STATUS "Sanity checking UndefinedBehaviorSanitizer, it should be supported on this platform")
    set(TEST_PROGRAM "int main() { return 0; }")

    # Check if UndefinedBehaviorSanitizer works at link time
    set(CMAKE_REQUIRED_FLAGS "-fsanitize=undefined")
    set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=undefined")
    check_cxx_source_compiles("${TEST_PROGRAM}" HAS_UBSAN_LINK_SUPPORT)

    if(HAS_UBSAN_LINK_SUPPORT)
      message(STATUS "UndefinedBehaviorSanitizer is supported at both compile and link time.")
      set(SUPPORTS_UBSAN ON)
    else()
      message(WARNING "UndefinedBehaviorSanitizer is NOT supported at link time.")
      set(SUPPORTS_UBSAN OFF)
    endif()
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    if (NOT WIN32)
      message(STATUS "Sanity checking AddressSanitizer, it should be supported on this platform")
      set(TEST_PROGRAM "int main() { return 0; }")

      # Check if AddressSanitizer works at link time
      set(CMAKE_REQUIRED_FLAGS "-fsanitize=address")
      set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
      check_cxx_source_compiles("${TEST_PROGRAM}" HAS_ASAN_LINK_SUPPORT)

      if(HAS_ASAN_LINK_SUPPORT)
        message(STATUS "AddressSanitizer is supported at both compile and link time.")
        set(SUPPORTS_ASAN ON)
      else()
        message(WARNING "AddressSanitizer is NOT supported at link time.")
        set(SUPPORTS_ASAN OFF)
      endif()
    else()
      set(SUPPORTS_ASAN ON)
    endif()
  endif()
endmacro()

macro(compact_washing_machine_firmware_demo_setup_options)
  option(compact_washing_machine_firmware_demo_ENABLE_HARDENING "Enable hardening" ON)
  option(compact_washing_machine_firmware_demo_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    compact_washing_machine_firmware_demo_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    compact_washing_machine_firmware_demo_ENABLE_HARDENING
    OFF)

  compact_washing_machine_firmware_demo_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR compact_washing_machine_firmware_demo_PACKAGING_MAINTAINER_MODE)
    option(compact_washing_machine_firmware_demo_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(compact_washing_machine_firmware_demo_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_PCH "Enable precompiled headers" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(compact_washing_machine_firmware_demo_ENABLE_IPO "Enable IPO/LTO" ON)
    option(compact_washing_machine_firmware_demo_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(compact_washing_machine_firmware_demo_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(compact_washing_machine_firmware_demo_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(compact_washing_machine_firmware_demo_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(compact_washing_machine_firmware_demo_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(compact_washing_machine_firmware_demo_ENABLE_PCH "Enable precompiled headers" OFF)
    option(compact_washing_machine_firmware_demo_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      compact_washing_machine_firmware_demo_ENABLE_IPO
      compact_washing_machine_firmware_demo_WARNINGS_AS_ERRORS
      compact_washing_machine_firmware_demo_ENABLE_USER_LINKER
      compact_washing_machine_firmware_demo_ENABLE_SANITIZER_ADDRESS
      compact_washing_machine_firmware_demo_ENABLE_SANITIZER_LEAK
      compact_washing_machine_firmware_demo_ENABLE_SANITIZER_UNDEFINED
      compact_washing_machine_firmware_demo_ENABLE_SANITIZER_THREAD
      compact_washing_machine_firmware_demo_ENABLE_SANITIZER_MEMORY
      compact_washing_machine_firmware_demo_ENABLE_UNITY_BUILD
      compact_washing_machine_firmware_demo_ENABLE_CLANG_TIDY
      compact_washing_machine_firmware_demo_ENABLE_CPPCHECK
      compact_washing_machine_firmware_demo_ENABLE_COVERAGE
      compact_washing_machine_firmware_demo_ENABLE_PCH
      compact_washing_machine_firmware_demo_ENABLE_CACHE)
  endif()

  compact_washing_machine_firmware_demo_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (compact_washing_machine_firmware_demo_ENABLE_SANITIZER_ADDRESS OR compact_washing_machine_firmware_demo_ENABLE_SANITIZER_THREAD OR compact_washing_machine_firmware_demo_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(compact_washing_machine_firmware_demo_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(compact_washing_machine_firmware_demo_global_options)
  if(compact_washing_machine_firmware_demo_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    compact_washing_machine_firmware_demo_enable_ipo()
  endif()

  compact_washing_machine_firmware_demo_supports_sanitizers()

  if(compact_washing_machine_firmware_demo_ENABLE_HARDENING AND compact_washing_machine_firmware_demo_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR compact_washing_machine_firmware_demo_ENABLE_SANITIZER_UNDEFINED
       OR compact_washing_machine_firmware_demo_ENABLE_SANITIZER_ADDRESS
       OR compact_washing_machine_firmware_demo_ENABLE_SANITIZER_THREAD
       OR compact_washing_machine_firmware_demo_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${compact_washing_machine_firmware_demo_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${compact_washing_machine_firmware_demo_ENABLE_SANITIZER_UNDEFINED}")
    compact_washing_machine_firmware_demo_enable_hardening(compact_washing_machine_firmware_demo_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(compact_washing_machine_firmware_demo_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(compact_washing_machine_firmware_demo_warnings INTERFACE)
  add_library(compact_washing_machine_firmware_demo_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  compact_washing_machine_firmware_demo_set_project_warnings(
    compact_washing_machine_firmware_demo_warnings
    ${compact_washing_machine_firmware_demo_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(compact_washing_machine_firmware_demo_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    compact_washing_machine_firmware_demo_configure_linker(compact_washing_machine_firmware_demo_options)
  endif()

  include(cmake/Sanitizers.cmake)
  compact_washing_machine_firmware_demo_enable_sanitizers(
    compact_washing_machine_firmware_demo_options
    ${compact_washing_machine_firmware_demo_ENABLE_SANITIZER_ADDRESS}
    ${compact_washing_machine_firmware_demo_ENABLE_SANITIZER_LEAK}
    ${compact_washing_machine_firmware_demo_ENABLE_SANITIZER_UNDEFINED}
    ${compact_washing_machine_firmware_demo_ENABLE_SANITIZER_THREAD}
    ${compact_washing_machine_firmware_demo_ENABLE_SANITIZER_MEMORY})

  set_target_properties(compact_washing_machine_firmware_demo_options PROPERTIES UNITY_BUILD ${compact_washing_machine_firmware_demo_ENABLE_UNITY_BUILD})

  if(compact_washing_machine_firmware_demo_ENABLE_PCH)
    target_precompile_headers(
      compact_washing_machine_firmware_demo_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(compact_washing_machine_firmware_demo_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    compact_washing_machine_firmware_demo_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(compact_washing_machine_firmware_demo_ENABLE_CLANG_TIDY)
    compact_washing_machine_firmware_demo_enable_clang_tidy(compact_washing_machine_firmware_demo_options ${compact_washing_machine_firmware_demo_WARNINGS_AS_ERRORS})
  endif()

  if(compact_washing_machine_firmware_demo_ENABLE_CPPCHECK)
    compact_washing_machine_firmware_demo_enable_cppcheck(${compact_washing_machine_firmware_demo_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(compact_washing_machine_firmware_demo_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    compact_washing_machine_firmware_demo_enable_coverage(compact_washing_machine_firmware_demo_options)
  endif()

  if(compact_washing_machine_firmware_demo_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(compact_washing_machine_firmware_demo_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(compact_washing_machine_firmware_demo_ENABLE_HARDENING AND NOT compact_washing_machine_firmware_demo_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR compact_washing_machine_firmware_demo_ENABLE_SANITIZER_UNDEFINED
       OR compact_washing_machine_firmware_demo_ENABLE_SANITIZER_ADDRESS
       OR compact_washing_machine_firmware_demo_ENABLE_SANITIZER_THREAD
       OR compact_washing_machine_firmware_demo_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    compact_washing_machine_firmware_demo_enable_hardening(compact_washing_machine_firmware_demo_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
