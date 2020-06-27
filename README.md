# Chess

### Classic chess game for two players
### The C++ project with SFML library of Microsoft Visual Studio.
#### What to do to run the project:
1) Clone the repository to you OS directory (for example 'C:\projects\chess').
2) [Download SFML library](https://www.sfml-dev.org/download.php) (32-bit) unzip and merge into one directory. For example 'C:\SFML'
3) MSVS project must have the following configurations - Project -> chess Properties (Configuration: All Configuration; Platform: win 32) -> Configuration Properties ->:
- a) C/C++ -> General -> Additional Include Directories - <Edit...> directory with includes of SFML, for examle: C:\SFML\include
- b) Linker -> General -> Additional Library Directories - <Edit...> directory with libraries of SFML, for examle: C:\SFML\lib
- c) Linker -> Input -> Additional Dependencies - <Edit...> include following libraries:  
    sfml-graphics.lib;  
    sfml-window.lib;  
    sfml-system.lib;  
    sfml-audio.lib;  
- d) Switch Configuration: to Debug, then add "-d" in each of these dll (Additional Dependencies):  
    sfml-graphics-d.lib;  
    sfml-window-d.lib;  
    sfml-system-d.lib;  
    sfml-audio-d.lib;  
- e) Run the project in "Debug x86" press "ok" and "Release x86" press "ok"
- f) Copy openal32.dll and all *-d.dll files from 'C:\SFML\bin' to project Debug direcectory (C:\projects\Debug), then copy openal32.dll and all *.dll (without '-d') files from 'C:\SFML\bin' to project Release direcectory (C:\projects\Release)

### All game rules are implemented: 
    en passant  
    сastling  
    stalemate  
    check  
    checkmate
The whole game is controlled by the left mouse button.
The game has a hint button that will help during the move highlighting the correct moves.

### Sample
![](https://github.com/vgladush/resources/blob/master/img/chess.gif)
