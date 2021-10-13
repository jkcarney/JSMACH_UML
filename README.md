# 2021fa-420-JSMACH

### Dependencies:

- Python3
- CMake (version 3.17.0 minimum)
- VCPKG 

### Instructions:

1. Clone repo to desired local folder
2. Run these commands: 

    `sudo pip3 install cmake`

3. Navigate to the project root (Should have a CMakeLists.txt file in it)
4. Install vcpkg for your OS:

   - `git clone https://github.com/microsoft/vcpkg` - clones vcpkg (make sure you're in project root!)
   - Next you'll install the packages the project depends on:
   
   - WINDOWS:

        ```.\vcpkg\bootstrap-vcpkg.bat```

        ```.\vcpkg\vcpkg install catch2:x64-windows nlohmann-json:x64-windows```

   - MAC:

        ```./vcpkg/bootstrap-vcpkg.sh```

        ```./vcpkg/vcpkg install catch2:x64-osx nlohmann-json:x64-osx```

    - LINUX:

        ```./vcpkg/bootstrap-vcpkg.sh```

        ```./vcpkg/vcpkg install catch2:x64-linux nlohmann-json:x64-linux```

5. `mkdir build`
6. `cd build`
5. `cmake ..` - creates Makefile, SLN file, etc depending on your compiler
6. If cmake compiled with Visual Studio, then you should have a .sln file that you can compile using either Visual Studio or using the Visual Studio Developer Command Prompt with 

    ```cl /EHsc main.cpp```

8. If cmake compiled with GCC (probably on Mac or Linux) you should have a Makefile that can be used to compile with 

    ```make```

9. An executable should be available.
    
    ```./jsmach_uml```
