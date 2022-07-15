# wildflower
![Header](https://user-images.githubusercontent.com/108103048/179121215-cfc911f7-6fd5-4667-8d82-09f15a89cbce.png)

**GOOD FOR ALLERGIES, NICE ON TOAST**

Wildflower is a DLL file designed to tamper with memory files. The DLL has to be injected into the Counter Strike: Global Offensive process in order to use the program, this can be done with any process management tool or injector.

Inspiration from this tool was taken from Rollraw and their CS:GO cheat template/base. Code used has been referenced in the appendix, for more information their repository can be found below:
[Rollraw's repository](https://github.com/rollraw/qo0-base/)


## About
![About Header](https://user-images.githubusercontent.com/108103048/179121309-da75dc09-667f-422a-8e41-90e41e502166.png)


Currently the project is bare with no features on the tool itself however, all the code is available for creating a performing program.

### Usage
When opening, a menu will appear which is the primary control for the programs features. This menu can be toggled on/off using the 'insert' key. The 'end' key can be used to end the operation while open.

A picture of the application in progress is shown below. When injecting a debug release of the DLL a console will attach to the process to log events in real time for developer use.

![Menu Header](https://user-images.githubusercontent.com/108103048/179123885-b0417471-c252-4efa-bd5f-6f40141a1755.png)
### Caution
Use this program at your own risk on servers other than your own. To avoid issues launch the game with the '-insecure' configuration.

### License
This project is covered under the MIT license. Use of the code or files found in this project can be used as long as the license is included with the material taken.
[MIT License](https://choosealicense.com/licenses/mit/)

## Appendix
![Appendix Header](https://user-images.githubusercontent.com/108103048/179125465-7646f039-519a-48d4-af82-a2b89aa4cf30.png)

### Dependencies
This program would not work without the use of these vital libraries. The repositories used can be found listed below:

**ImGui**
ImGui is a graphical user interface library that is used for rendering the cheats menu and, on screen effects using the process's window.
[ImGui Library](https://github.com/ocornut/imgui/)

**Minhook**
Minhook is a program hooking library and is the back bone of the tool itself. The library is being used to create functions that can alter game modules.
[Minhook Library](https://github.com/TsudaKageyu/minhook/)

### References
Code adapted from other projects can be found here in APA style of reference. The code is also internally referenced using comments.

**Memory.cpp**
Rollraw. (2022).  qo0-base: internal cs:go cheat base/template.
--- Retrieved from GitHub: https://github.com/rollraw/qo0-base/