cmake_minimum_required(VERSION 3.19)
project(BaZheZhuShou LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

qt_add_executable(BaZheZhuShou
    WIN32 MACOSX_BUNDLE
    main.cpp
    LogIn.cpp
    LogIn.h
    LogIn.ui
    UserManager.h UserManager.cpp
    MainWindow.h MainWindow.cpp MainWindow.ui
    MapManager.h MapManager.cpp
    MyColor.h MyColor.cpp
    MyPoint.h MyPoint.cpp
    MyWorker.h MyWorker.cpp
    DaTingWorker.h DaTingWorker.cpp
    ZhongXinWorker.h ZhongXinWorker.cpp
    MyRect.h MyRect.cpp
    Define.h
)

target_link_libraries(BaZheZhuShou
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

include(GNUInstallDirs)

install(TARGETS BaZheZhuShou
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET BaZheZhuShou
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
