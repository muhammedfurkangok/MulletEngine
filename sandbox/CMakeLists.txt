file(GLOB SANDBOX_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(sandbox ${SANDBOX_SRC})
target_link_libraries(sandbox PRIVATE engine)

add_custom_command(TARGET sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:sandbox>/assets)
