add_executable(hello
    main.cpp
    appLayer.cpp
)

target_link_libraries(hello
    PRIVATE Core
)

target_include_directories(hello
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
