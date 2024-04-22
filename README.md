# AirCompare
To run this project, clone this repo, and use your preferred compiler. This project uses Cmake to build the SFML seamlessly across computers.

Help with Cmake with different compilers:
    - [VS Code](https://code.visualstudio.com) via the [CMake extension](https://code.visualstudio.com/docs/cpp/cmake-linux)
    - [Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)
    - [CLion](https://www.jetbrains.com/clion/features/cmake-support.html)
    - [Qt Creator](https://doc.qt.io/qtcreator/creator-project-cmake.html)

Once the project is set up in your compiler, follow these steps:
In the src/assets/fonts folder, copy both the Roboto-Bold and Roboto-Regular font, and paste them into your bin folder. This should be located in the cmake-build-debug folder (in Visual Studio 2019, it will be in the out/build/x64-Debug folder).
Go back to the src/assets folder, and extract the CSV from airbnb_listings_usa. Copy the airbnb_listings_usa.csv file, and paste it into the same location you pasted the fonts.

Compile and run the project, and enjoy AirCompare!