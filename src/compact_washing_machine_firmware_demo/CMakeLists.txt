include(GenerateExportHeader)

add_library(compact_washing_machine_firmware_demo compact_washing_machine_firmware_demo.cpp)


add_library(compact_washing_machine_firmware_demo::compact_washing_machine_firmware_demo ALIAS compact_washing_machine_firmware_demo)

target_link_libraries(compact_washing_machine_firmware_demo PRIVATE compact_washing_machine_firmware_demo_options compact_washing_machine_firmware_demo_warnings)

target_link_system_libraries(
        compact_washing_machine_firmware_demo
        PRIVATE
        magic_enum::magic_enum
        mpark_patterns
)

target_include_directories(compact_washing_machine_firmware_demo ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(compact_washing_machine_firmware_demo PUBLIC cxx_std_20)

set_target_properties(
        compact_washing_machine_firmware_demo
        PROPERTIES VERSION ${PROJECT_VERSION}
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(compact_washing_machine_firmware_demo EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/compact_washing_machine_firmware_demo/compact_washing_machine_firmware_demo_export.hpp)

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(compact_washing_machine_firmware_demo PUBLIC COMPACT_WASHING_MACHINE_FIRMWARE_DEMO_STATIC_DEFINE)
endif ()


add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE
        compact_washing_machine_firmware_demo::compact_washing_machine_firmware_demo)
target_link_system_libraries(
        demo
        PRIVATE
        magic_enum::magic_enum
        mpark_patterns
        fmt::fmt
)
