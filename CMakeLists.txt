cmake_minimum_required(VERSION 3.31) # выставляет минимальную конфигурацию cmake,
# то есть ее версию(версию cmake)
# аргументы (VERSION - обязательный аргумент дальше идёт major.minor[.patch[.tweak]]
# major - старшая версия
# "." - как я понял, так называемый разделитель
# minor - минимальная версия
# [.patch[.tweak]] - не обязательные параметры
project(toDoList) # название проект, также есть опциональные аргументы
# [VERSION major[.minor[.patch[.tweak]]]][LANGUAGES languageName ...]
# LANGUAGES languageName ... - это какие языки программирования будут использоваться в проекте
# C CXX Frotran ASM Java - всё указывается через пробел
# по умолчанию C и CXX
set(CMAKE_CXX_STANDARD 20) # (свои додумки) - какой стандарт CXX будет использоваться в проекте
set(wxWidgets_ROOT_DIR "C:/libC++/wxwidgets")
set(wxWidgets_LIB_DIR "C:/libC++/wxwidgets/lib/gcc1510_x64_dll")
set(json_c "C:/libC++/")

include(FetchContent)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3 # или последняя версия
)

FetchContent_MakeAvailable(nlohmann_json)


find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})


file(GLOB project_GLOB src/*)

add_executable(toDoList ${project_GLOB}
        src/model/Task.cpp
        src/model/Task.h
        src/model/TaskList.cpp
        src/model/TaskList.h
        src/view/MainFrame.cpp
        src/view/MainFrame.h
        src/view/TaskPanel.cpp
        src/view/TaskPanel.h
        src/view/TaskDialog.cpp
        src/view/TaskDialog.h
        src/controller/TaskController.cpp
        src/controller/TaskController.h) # это команда говорит cmake создать исполняемый файл с
#target_link_libraries(toDoList ${wxWidgets_LIBRARIES})
target_link_libraries(toDoList PRIVATE ${wxWidgets_LIBRARIES} nlohmann_json::nlohmann_json)
target_include_directories(toDoList PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_compile_definitions(toDoList PRIVATE UNICODE _UNICODE)
# исходным кодом(это будет main.cpp)
# параметры (targetName source1 [source2 ...])
# targetName - название таргета, с этим название будет создан exe
# также можно создать разными exe. Нужно только вызвать add_executable(toDoList1 main.cpp)
# с разными названиями таргетов

# чтобы создать графическое приложение нужно
# add_executable(targetName [WIN32] [MACOSX_BUNDLE] [EXCLUDE_FROM_ALL] source1 [source2 ...])
# WIN32 - говорит cmake чтобы компилируем программу с графическом интерфейсом
# MACOSX_BUNDLE - компиляция для apple платформ
# EXCLUDE_FROM_ALL - вызывается билд всех возможных таргетов(то есть при использование ALL или ALL_BUILD)
# данный таргет не будем собираться. По сути можно использовать для вспомогательных программ

# add_library(targetName [STATIC | SHARED | MODULE] [EXCLUDE_FROM_ALL] source1 [source2 ...])
# "|" - логическое "или"
# STATIC - получится статичная библиотека
# SHARED - с динамической линковкой
# MODULE - динамическая в RUNTIME(то есть когда программа уже запущена)(допустим интерфейс подключение библиотек)

# есть команда BUILD_SHARED_LIBS - когда она true библиотеки компилируются в SHARED, иначе STAIC
# set(BUILD_SHARED_LIBS YES) - выставили true
# cmake -DBUILD_SHARED_LIBS = YES /path/to/source при генерации проекта будет выставляться true
# /path/to/source - путь к cmake файлу

# target_link_libraries(targetName
#    <PRIVATE|PUBLIC|INTERFACE> item1 [item2 ...]
#        <PRIVATE|PUBLIC|INTERFACE> item1 [item2 ...]
#)

# <> - означают, что нужно выбрать что-то одно
# допустим есть две библиотеки libA и libB
# target_link_libraries(libA PRIVATE libB) то при компиляции
# target_link_libraries(toDoList PRIVATE libA) из библиотеки А ничего не будет известно в библиотекек Б
# PUBLIC - в хеддера должны буду иницилизироваться библиотка Б, когда в прайват они будут иницилизироваться в срр
# INTERFACE - инплимитация будет в только в хеддере, допустим это какая-нибудь библиотека из хеддоров

# задавание переменной
# синтаксис set(varName value... [PARENT_SCOPE])
# varName - имя переменной
# value - значение переменной
# PARENT_SCOPE - расширение переменной
# получение значение из переменной ${varName}
# message("ввод") - вывод

# переменные среды
# $ENV{название переменной среды}
# что такое переменная среды - это название переменной, когда обычно мы добавляем какую-то программу в Path

# кэшированные переменные
# set(varName value... CACHE type "docstring" [FORCE])