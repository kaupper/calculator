# calculator
A simple calculator written in C++

Needed to build this project:
- JRE >= 1.6
- g++

There are 2 main build types:
- ./gradlew.bat installCalculatorDebugExecutable - builds all cpp files in src/ with debug symbols and -DDEBUG
- ./gradlew.bat installCalculatorReleaseExecutable - builds all cpp files in src/

Output directory for the executable:
./build/exe/calculator/{buildType}/calculator.exe

For more information run ./gradlew.bat tasks.