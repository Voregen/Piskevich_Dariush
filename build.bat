md _build
cd _build
set CMAKE_PREFIX_PATH="C:/Qt/5.9.9/msvc2015_64"
set QT_QMAKE_EXECUTABLE="C:/Qt/5.9.9/msvc2015_64/bin/qmake.exe"

cmake .. -DCMAKE_PREFIX_PATH=%CMAKE_PREFIX_PATH%
cmake --build .
