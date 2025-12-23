cmake_minimum_required(VERSION 3.10)
project(QtApplicationDemo LANGUAGES CXX)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc, uic, and rcc automatically when needed
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Widgets X11Extras)
set(REQUIRED_LIBS_QUALIFIED Qt5::Widgets Qt5::X11Extras xcb)

# Find the required Qt 5 packages and components
# QtWidgets is needed for QApplication and GUI elements
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

# Add the executable target
add_executable(QtApplicationDemo main.cpp)

# Link the executable with the necessary Qt 5 libraries
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
