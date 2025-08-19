cmake_minimum_required(VERSION 3.31)
project(toDoList)
set(CMAKE_CXX_STANDARD 20)

set(wxWidgets_ROOT_DIR "C:/libC++/wxwidgets")
set(wxWidgets_LIB_DIR "C:/libC++/wxwidgets/lib/gcc1510_x64_dll")

include(FetchContent)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(nlohmann_json)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

# Указываем все исходные файлы явно
set(SOURCES
        src/main.cpp
        src/model/Task.cpp
        src/model/TaskList.cpp
        src/view/MainFrame.cpp
        src/view/TaskPanel.cpp
        src/view/TaskDialog.cpp
        src/controller/TaskController.cpp
)

# Указываем все заголовочные файлы
set(HEADERS
        src/model/Task.h
        src/model/TaskList.h
        src/view/MainFrame.h
        src/view/TaskPanel.h
        src/view/TaskDialog.h
        src/controller/TaskController.h
)

add_executable(toDoList ${SOURCES} ${HEADERS})

# Добавляем директории с заголовочными файлами
target_include_directories(toDoList PRIVATE
        ${wxWidgets_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model
        ${CMAKE_CURRENT_SOURCE_DIR}/src/view
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controller
)

target_link_libraries(toDoList PRIVATE ${wxWidgets_LIBRARIES} nlohmann_json::nlohmann_json)
target_compile_definitions(toDoList PRIVATE UNICODE _UNICODE)