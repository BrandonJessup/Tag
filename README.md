# Building
1. Install [Qt Creator](https://doc.qt.io/qt-6/get-and-install-qt.html).
2. Either download the ZIP for this project or run `git clone https://github.com/BrandonJessup/Tag.git` wherever you want it to be.
3. Open the `Tag.pro` file with Qt Creator.
4. You should now be able to just build and run Tag through the Run button (the green triangle on the bottom left of Qt Creator).

# Deploying
1. With the Tag project open in Qt Creator, run a release build.
2. You can then navigate to the release folder, in my case: `[projectfolder]/build/Desktop_Qt_6_7_2_MinGW_64_bit-Release/release/`.
3. From here, take the `.exe` file and copy it to whatever folder you want to deploy to.
4. Run the Qt MinGW terminal (should be installed alongside Qt in your start menu).
5. In the terminal, navigate to the folder you moved the `.exe` to.
6. Run the command `windeployqt6 tag`, and the Qt dependencies should automatically added into this folder.
7. Try to run `Tag.exe` now, and a few dependencies should still be missing. These can be found in the install location of Qt on your system, for my version of Qt, they are in `[Qt install location]/6.7.2/mingw_64/bin`. Just copy whatever `.dll`s the error messages say you are missing into the same folder as your `Tag.exe`.

# Future plans

## Bug Fixes
- When an item is dragged into the program, the filters get reset in the list window, but the tags in the search box do not get cleared.
    - Search tags should be cleared whenever an item is dragged into the program.

## Modifications
- Dragging an item into the window when that item already exists in the program should highlight the existing item.
    - Currently the bottom file will be selected.
- Make search card and font more readable in dark mode, and just better support for dark/light mode in general. (Maybe dark mode could be forced to make this easier?)

## Features
- Search dropdown has third option: filename
    - Results shown will have all or part of their filename matching the value entered into the search box.
    - Entering a second filename search into the tag box will remove the first.
        - Otherwise this would be too annoying to change the searched tag each time, and it's not like searching would ever really require more than one chunk of a filename anyway.
    - No autocomplete.
    - Search card should have a unique color in the search box.
