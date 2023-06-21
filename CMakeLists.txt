cmake_minimum_required(VERSION 3.26)

project(drawshot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(X11 REQUIRED)


qt_standard_project_setup()

qt_add_executable(appdrawshot)

find_package(Qt6 REQUIRED COMPONENTS Quick)
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIB_DIR})
target_link_libraries(appdrawshot PRIVATE Qt6::Quick)
target_link_libraries(appdrawshot PRIVATE ${X11_LIBRARIES})

target_sources(appdrawshot
    PRIVATE
        main.cpp
        screencapture.h screencapture.cpp
        selectimageprovider.h
        share.h share.cpp
        arearecord.h    arearecord.cpp

    PUBLIC
        resource.qrc

)

qt_add_qml_module(appdrawshot
    URI drawshot
    VERSION 1.0

    #    SOURCES

    QML_FILES
        Main.qml
        Actions.qml
        Content.qml
        LeftContent.qml
        RightContent.qml
        LeftTools.qml
        BottomTools.qml
        Dialogs.qml
        Functions.js
        SelectWindow.qml

)

target_compile_features(appdrawshot PRIVATE cxx_std_20)

set_target_properties(appdrawshot PROPERTIES
    AUTORCC TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appdrawshot
    PRIVATE
        Qt6::Quick
        Qt6::Widgets
        ${X11_LIBRARIES}
        )


install(TARGETS appdrawshot
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


target_link_libraries(appdrawshot PRIVATE Qt6::Widgets)
target_link_libraries(appdrawshot PRIVATE Qt6::Core)



















































#qt_add_executable(drawshot)  //Creates and finalizes an application target of a platform-specific type.
#This command performs the following tasks:
#    1. Create a CMake target of the appropriate type for the target platform.
#    2. Link the target to the Qt::Core library.
#    3. Handle finalization of the CMake target.



# qt_standard_project_setup()     #set(CMAKE_AUTOUIC ON)  set(CMAKE_AUTOMOC ON)

# @if %{HasTranslation}
# find_package(Qt6 REQUIRED COMPONENTS Core Quick LinguistTools)
# @else
# find_package(Qt6 REQUIRED COMPONENTS Core Quick)
# @endif

# target_sources(appdrawshot
#     PRIVATE
#         main.cpp
#         qml.qrc
#     @if %{HasTranslation}
#         %{TsFileName}
#     @endif
#         
#     PUBLIC
#         
# )

# qt_import_qml_plugins(drawshot)
