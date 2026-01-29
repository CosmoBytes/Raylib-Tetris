add_library(Core)

target_sources(Core
    PRIVATE
        Renderer/Window.cpp
        Renderer/blockMotion.cpp
        Renderer/blockType.cpp
        Renderer/colors.cpp
        Renderer/grid.cpp
        Renderer/position.cpp        
    PUBLIC
        Renderer/Window.hpp
        Renderer/blockMotion.hpp
        Renderer/blockType.hpp
        Renderer/colors.hpp
        Renderer/grid.hpp
        Renderer/position.hpp 
)

target_include_directories(Core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Core
    PUBLIC raylib
)

set(ASSETS
    Fonts
    Images
    Sounds
)

foreach(ASSET_DIR ${ASSETS})
    add_custom_target(copy_${ASSET_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/${ASSET_DIR}
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ASSET_DIR}
    )
endforeach()

add_dependencies(Core
    copy_Fonts
    copy_Images
    copy_Sounds
)