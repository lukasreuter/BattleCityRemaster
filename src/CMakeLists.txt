find_package(Magnum REQUIRED
    GL
    Sdl2Application
    SceneGraph)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

set(CMAKE_CXX_STANDARD 17)

file(GLOB CPP_FILES *.cpp *.cc) 
file(GLOB H_FILES *.h) 
file(GLOB_RECURSE ENTT entt/src/entt/*.h entt/src/entt/*.hpp)

add_executable(BattleCity2018 main.cpp
${CPP_FILES}
${H_FILES}
)

include_directories(entt/src/entt)
target_include_directories(BattleCity2018 PRIVATE ${ENTT})
target_link_libraries(BattleCity2018 PRIVATE
    Magnum::Application
    Magnum::GL
    Magnum::Magnum
    Magnum::SceneGraph)
