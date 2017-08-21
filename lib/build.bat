cmake CMakeLists.txt -G"Visual Studio 15 2017 Win64" -DINSTALL_NAME="x64-Debug" -H. -Bbuild\\x64-Debug
cmake --build .\\build\\x64-Debug --config Debug

cmake CMakeLists.txt -G"Visual Studio 15 2017 Win64" -DINSTALL_NAME="x64-RelWithDebInfo" -H. -Bbuild\\x64-RelWithDebInfo
cmake --build .\\build\\x64-RelWithDebInfo --config RelWithDebInfo

cmake CMakeLists.txt -G"Visual Studio 15 2017 Win64" -DINSTALL_NAME="x64-Release" -H. -Bbuild\\x64-Release
cmake --build .\\build\\x64-Release --config Release
