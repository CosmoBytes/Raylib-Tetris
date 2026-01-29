Set-Location $PSScriptRoot

# refresh the build directory
Remove-Item build -Recurse -Force
mkdir build
Set-Location build

# configure cmake with ninja and clang
cmake -G Ninja `
    -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake `
    -DCMAKE_CXX_COMPILER=clang++ `
    -DCMAKE_BUILD_TYPE=Debug `
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON `
    ..

# build the executable file
ninja

Set-Location ..