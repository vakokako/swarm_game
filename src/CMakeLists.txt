
set(Qt_REQUIRED_VERSION 6.2.0)
set(Qt_REQUIRED_COMPONENTS Core Quick Gui Widgets Svg)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} ${Qt_REQUIRED_VERSION} COMPONENTS ${Qt_REQUIRED_COMPONENTS} REQUIRED)
set(CMAKE_AUTOMOC ON)

find_package(EnTT CONFIG REQUIRED)

add_subdirectory(HotReload)

set(${PROJECT_NAME}Libraries 
    project_options
    project_warnings
    docopt_s
    fmt::fmt
    spdlog::spdlog
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    EnTT::EnTT
    HotReloadLib
)

include(FileListing.cmake)

set(QmlCppIntegrationLibName ${PROJECT_NAME}QmlCppIntegrationLib)
add_library(${QmlCppIntegrationLibName})
qt_add_qml_module(${QmlCppIntegrationLibName}
    URI SwarmCpp
    VERSION 1.0
    SOURCES
        ${${PROJECT_NAME}_Headers}
        ${${PROJECT_NAME}_Sources}
)
target_link_libraries(${QmlCppIntegrationLibName} 
    PRIVATE ${${PROJECT_NAME}Libraries}
            ${QmlCppIntegrationLibName}plugin
)

add_executable(${PROJECT_NAME} main.cpp)

# target_sources(${PROJECT_NAME} 
#     PUBLIC FILE_SET HEADERS FILES ${${PROJECT_NAME}_Headers}
#     PRIVATE ${${PROJECT_NAME}_Sources}
# )

target_link_libraries(${PROJECT_NAME}
  PRIVATE ${${PROJECT_NAME}Libraries}
          ${QmlCppIntegrationLibName}
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(QML_CACHEGEN_FLAG NO_CACHEGEN)
endif()

qt_add_qml_module(${PROJECT_NAME}
    URI SwarmQml
    VERSION 1.0
    QML_FILES
        ${${PROJECT_NAME}_QmlSources}
    # Needed so that there is no module name prefix in qrc paths
    NO_RESOURCE_TARGET_PATH
    # Don't compile qml files to bytecode (faster compilation, enable cachegen for release)
    ${QML_CACHEGEN_FLAG}
)

