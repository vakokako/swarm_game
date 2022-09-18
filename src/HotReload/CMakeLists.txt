set(HotReloadLibName HotReloadLib)

add_library(${HotReloadLibName})

qt_add_qml_module(${HotReloadLibName}
    URI HotReload
    VERSION 1.0
    RESOURCE_PREFIX /qml
    # PLUGIN_TARGET ${HotReloadLibName}
    SOURCES
        HotReload.hpp
        HotReload.cpp
    QML_FILES
        HotReload.qml
    RESOURCES
        icons/exit_active.svg
        icons/exit_idle.svg
        icons/exit_pressed.svg
        icons/refresh_active.svg
        icons/refresh_idle.svg
        icons/refresh_pressed.svg
    # Needed so that there is no module name prefix in qrc paths
    # NO_RESOURCE_TARGET_PATH
    # Don't compile qml files to bytecode (faster compilation, enable cachegen for release)
    # ${QML_CACHEGEN_FLAG}
)

target_link_libraries(${HotReloadLibName}
  PRIVATE project_options
          project_warnings
          fmt::fmt
          spdlog::spdlog
          Qt${QT_VERSION_MAJOR}::Quick
          Qt${QT_VERSION_MAJOR}::Svg
          Qt${QT_VERSION_MAJOR}::Core
          ${HotReloadLibName}plugin
)
