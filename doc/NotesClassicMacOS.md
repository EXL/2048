Classic Mac OS Notes
====================

## Mac OS System 6 Notes

I took for development under classic [Mac OS System 6](https://en.wikipedia.org/wiki/System_6) the [Symantec THINK C 5.0.2](https://en.wikipedia.org/wiki/THINK_C) IDE and [Apple ResEdit 2.1.1](https://en.wikipedia.org/wiki/ResEdit) which is already included to the THINK C distribution kit. THINK C expands a traditional [C language](https://en.wikipedia.org/wiki/C_(programming_language)) syntax with basic [object-oriented programming (OOP)](https://en.wikipedia.org/wiki/Object-oriented_programming) concepts such as single inheritance, object and classes, these extensions make programming more familar and convenient. Standard Apple technologies such as [Macintosh Toolbox](https://en.wikipedia.org/wiki/Macintosh_Toolbox) and [QuickDraw](https://en.wikipedia.org/wiki/QuickDraw) can be used with THINK C alongside with [ANSI C](https://en.wikipedia.org/wiki/ANSI_C) language standard library.

### TODO List

1. [x] Check `NumberToStr()` function and `Str15` type for small Pascal strings.
2. [x] Check `THINK_C` compilator macro define on Symantec THINK C 5.0.2 IDE.
3. [x] Disable scrollbars and growing icon for application window.
4. [x] Find constant values for control keys.
5. [x] Find a way to call submenu from the main menu.
6. [x] Change the (c) sign to good one (hint: ©).
7. [x] Add link to the Macintosh Toolbox with THINK C tutorial.
8. [x] Find a way to set application icon.
9. [x] Implement offscreen drawing and mention the author of the functions.
10. [x] Make game score visible on the final.
11. [x] Set proper `x` and `y` coords for window and dialog.
12. [x] Bump date in about dialog.
13. [x] Refactor all code with [OOP](https://en.wikipedia.org/wiki/Object-oriented_programming)-style.
14. [x] Set first frame also as offscreen drawing.
15. [x] Check `Random()` function and use it instead `rand()` from huge ANSI C language library. This will allow to use ANSI-small library and reduce the size of executable file.
16. [x] Add notes about `mac2unix` and `unix2mac` utilites.
17. [ ] Create floppy disk image with source code of classic Mac OS projects.
18. [x] Add notes about Macintosh Toolbox and QuickDraw technologies.
19. [x] Bring C-casts to the one style in game engine.
20. [x] Check argument of `SysBeep()` function.
21. [x] Fix bug with wrong desk acc drawing on the application window, like "Calculator" applet.

### References and Books List

1. [Macintosh C Programming By Example, 1991](https://vintageapple.org/macprogramming/pdf/Macintosh_C_Programming_By_Example_1991.pdf)
2. [More Macintosh Toolbox, 1993](http://mirror.informatimago.com/next/developer.apple.com/documentation/mac/pdf/MoreMacintoshToolbox.pdf)
3. [Programming QuickDraw, 1992](https://vintageapple.org/macprogramming/pdf/Programming_QuickDraw_1992.pdf)
4. [THINK C Version 5 User Manual, 1991](http://mirror.macintosharchive.org/max1zzz.co.uk/+Mac%20OS%20Classic/Programming/THINK%20Pascal/Think_C_Version_5_User_Manual_1991.pdf)
5. [THINK C Version 5 Standard Libraries Reference, 1991](http://mirror.macintosharchive.org/max1zzz.co.uk/+Mac%20OS%20Classic/Programming/THINK%20Pascal/Think_C_Version_5_Standard_Libraries_Reference_1991.pdf)
6. [THINK C Version 5 Object-oriented Programming Manual](http://mirror.macintosharchive.org/max1zzz.co.uk/+Mac%20OS%20Classic/Programming/THINK%20Pascal/Think_C_Version_5_Object-Oriented_Programming_Manual_1991.pdf)
7. [ResEdit Reference For ResEdit 2.1](https://developer.apple.com/library/archive/documentation/mac/pdf/ResEditReference.pdf)

You can find literature, documentation, and source code on the following sites:

1. [Vintage Apple](https://vintageapple.org/)
2. [Informatimago Mirror](http://mirror.informatimago.com/next/developer.apple.com/documentation/)
3. [Macintosh Archive](http://mirror.macintosharchive.org/max1zzz.co.uk/+Mac%20OS%20Classic/)
4. [Infomac Mirro](http://ftp.knoppix.nl/infomac/)
5. [Apple Documentation Archive](https://developer.apple.com/library/archive/navigation/)
