Classic Mac OS Notes
====================

## Mac OS 9 Notes

// TODO: CodeWarrior Pro 8 on Mac OS 9
// TODO: ProjectBuilder on OS X 10.0

### Task List

1. [x] Install MCW IDE and find some Carbon code example.
2. [x] Rename directory from 2048-Toolbox to 2048-Carbon.
3. [x] Add Carbon skeleton project for MCW IDE on Mac OS 9.
4. [x] Find ResEdit or its analog and create all resources.
5. [x] Implement basic game drawing.
6. [ ] Add Classic Mac OS binaries size information.
7. [x] Polish "2048-Carbon.rsrc" resource file.
8. [x] Implement Offscreen drawing with Carbon.
9. [x] Check executable file on Mac OS X.
10. [x] Create "Project Builder" project for Mac OS X Carbon version.
11. [x] Fix crash on Mac OS X.
12. [x] Get and read two Carbon API examples on Mac OS X: simple and NIB-based.
13. [x] Fix menus on Mac OS X.
14. [x] It is possible to set icon for Mac OS X Carbon API application compiled on Mac OS 9? Yes.
15. [x] Work on about dialog: moveable, background, etc.
16. [x] Drop sudo Sheep Shaver.
17. [x] Add information about [MoreIsBetter](http://mirror.informatimago.com/next/developer.apple.com/samplecode/MoreIsBetter/index.html) example.
18. [ ] Check on Intel-based Mac OS.
19. [ ] Add ReadMe.md files to the "Supporting Files" group in projects.

## Mac OS 8 Notes

I choose for Mac OS 8.1 development [Metrowerks CodeWarrior IDE 3.2](https://en.wikipedia.org/wiki/CodeWarrior), [Metrowerks Constructor 2.4.5](https://en.wikipedia.org/wiki/PowerPlant), and [Apple ResEdit 2.1.3](https://en.wikipedia.org/wiki/ResEdit) programs which are included to the [CodeWarrior Pro 4](https://macintoshgarden.org/apps/codewarrior-pro-4) distribution CD. The compilers provided with this package can compile [С](https://en.wikipedia.org/wiki/C_(programming_language)) and [C++](https://en.wikipedia.org/wiki/C%2B%2B) code for [Motorola 68000](https://en.wikipedia.org/wiki/Motorola_68000) and [PowerPC](https://en.wikipedia.org/wiki/PowerPC) architectures. Standard Apple technologies such as [Macintosh Toolbox](https://en.wikipedia.org/wiki/Macintosh_Toolbox), [QuickDraw](https://en.wikipedia.org/wiki/QuickDraw), and [QuickDraw GX](https://en.wikipedia.org/wiki/QuickDraw_GX) can be used with Metrowerks CodeWarrior IDE alongside with C and C++ standard libraries.

The CodeWarrior Pro 4 package includes object-oriented [Metrowerks PowerPlant](https://en.wikipedia.org/wiki/PowerPlant) application framework, which is similar to the Think Class Library (TCL) from the Symantec THINK C integrated development environment. I think a lot of good things in the Metrowerks CodeWarrior IDE come from the Symantec THINK C world.

The [Macintosh Programmer's Workshop](https://en.wikipedia.org/wiki/Macintosh_Programmer%27s_Workshop) (MPW) is a software development environment for the Classic Mac OS operating system, written by Apple, which was later superseded by the Metrowerks CodeWarrior IDE. MPW provided a collection of compilers and tools inside command line "MPW Shell" environment which was similar to UNIX-shells in desing but with a "worksheet" interface, allowing the user to select and run arbitrary sections of a shell script or to redo commands with no retyping. Metrowerks added to the Apple MPW own compilers, various auxiliary scripts, and some utilities. A set of "CodeWarrior MPW" tools is included in the **CodeWarrior Pro 4** distribution and requires preliminary manual configuration describes in [2048-Carbon/2048-MCW/ReadMe.md](../2048-Carbon/2048-MCW/ReadMe.md) document.

### Tasks List

1. [x] Find option to enable `bool` keyword for C++.
2. [x] Create project skeleton.
3. [x] Find some offscreen drawing examples.
4. [x] What is QuickDraw GX? Try to implement it.
5. [x] Create GUI skeleton: MenuBar, Menus, Windows, Resources, About dialog, etc.
6. [x] Implement basic offscreen drawing.
7. [x] Update engine source code.
8. [x] Finish general game drawing.
9. [x] Check it on Mac OS System 6, Mac OS System 7 and Mac OS 9.
10. [x] Add about dialog with a window title bar.
11. [x] Setup environment for building QuickDraw examples.
12. [x] Create QuickDraw + QuickDrawGX switch example.
13. [x] Add links to the "ftp.apple.com" archive and QuickDraw GX books.
14. [x] Add alerts instead of beeps.
15. [x] Implement skeleton QuickDraw + QuickDraw GX drawing.
16. [x] Implement QuickDraw GX general game drawing.
17. [x] Optimize QuickDraw GX shapes drawing and release/free/dispose these shapes.
18. [x] Draw some QuickDraw GX logo on game board background.
19. [x] Find a way to some transparents drawing.
20. [x] Check standard dialogs.
21. [x] Check executables on various Mac OS versions and PowerPC architecture.
22. [x] Add some documentation files, screens and instructions.
23. [x] Enable weak linkage of QuickDrawGXLib for PowerPC build.
24. [x] Check Metrowerks CodeWarrior and Apple MPWs environments.
25. [ ] Create floppy image disk with executable, sources, and project files.
26. [x] Add CodeWarrior MPW instructions and screenshots.
27. [x] Add `LF` => `CR` conversion list of files.
28. [x] Check various memory consumption.
29. [ ] Include ReadMe.md files to the source directories.
30. [x] Transfer problems of Motorola 68000 executable files. Use archives or floppy disk images.
31. [x] Check game on the Mac OS System 6 with color display. It's works! There is crash on the "About 2048-MCW..." dialog though.
32. [ ] Connection with Carbon.

## A/UX Notes

TODO: Desc AUX
TODO: Desc AUX Dev Tools inbox
TODO: Use BasiliskII for move files (README)

### Task List

1. [x] Port and run X11 version, 2048-Xlib application.
2. [x] Port and run Toolbox version, 2048-AUX application.
3. [ ] Add compiler info and version to document.
4. [ ] Create "old" directory for ported engine, patch file?
5. [ ] Note about 256 MB RAM on Shoebill command.
6. [x] Compile and test Macintosh Toolbox for A/UX code sample.
7. [ ] Add links to ReadMe.md files.
8. [x] #ifdef AUX #endif AUX (don't need that).
9. [x] Check code style on K&R function declarations.
10. [x] Add some information about `DeRez` utility.
11. [ ] Add some information about `fcnvt` utility.
12. [x] Port and run X11 version, 2048-Xaw application.
13. [x] Add short offscreen drawing function.
14. [x] Implement general drawing.
15. [x] Enable offscreen drawing by default and fix bugs.
16. [x] Fix bug with colors in offscreen.
17. [x] Drop background/foreground routines in other versions.
18. [ ] Fix UNIX file rights.
19. [ ] Add some note about setting file associations by ResEdit program.

## Mac OS System 6 Notes

I took for development under classic [Mac OS System 6](https://en.wikipedia.org/wiki/System_6) the [Symantec THINK C 5.0.2](https://en.wikipedia.org/wiki/THINK_C) IDE and [Apple ResEdit 2.1.1](https://en.wikipedia.org/wiki/ResEdit) program which is already included to the THINK C distribution kit. THINK C expands a traditional [C language](https://en.wikipedia.org/wiki/C_(programming_language)) syntax with basic [object-oriented programming (OOP)](https://en.wikipedia.org/wiki/Object-oriented_programming) concepts such as single inheritance, object and classes, these extensions make programming more familar and convenient. Standard Apple technologies such as [Macintosh Toolbox](https://en.wikipedia.org/wiki/Macintosh_Toolbox) and [QuickDraw](https://en.wikipedia.org/wiki/QuickDraw) can be used with THINK C alongside with [ANSI C](https://en.wikipedia.org/wiki/ANSI_C) language standard library.

The THINK C offered the programmer a powerful object-oriented Think Class Library (TCL) framework, which was used extensively for Macintosh application development.

### Tasks List

1. [x] Check `NumberToStr()` function and `Str15` type for small Pascal strings.
2. [x] Check `THINK_C` compiler macro define on Symantec THINK C 5.0.2 IDE.
3. [x] Disable scrollbars and growing icon for application window.
4. [x] Find constant values for control keys.
5. [x] Find a way to call submenu from the main menu.
6. [x] Change the (c) sign to the good one (hint: ©).
7. [x] Add link to the "Macintosh Toolbox with THINK C" tutorial.
8. [x] Find a way to set application icon.
9. [x] Implement offscreen drawing and mention the author of these functions.
10. [x] Make game score visible on the final.
11. [x] Set proper `x` and `y` coords for window and dialog.
12. [x] Bump date in about dialog.
13. [x] Refactor all code with [OOP](https://en.wikipedia.org/wiki/Object-oriented_programming)-style.
14. [x] Set first frame also as offscreen drawing.
15. [x] Check `Random()` function and use it instead of `rand()` from huge ANSI C language library. This will allow to use ANSI-small library and reduce the size of executable file.
16. [x] Add notes about `mac2unix` and `unix2mac` utilites.
17. [ ] Create floppy disk image with source code of classic Mac OS projects.
18. [x] Add notes about Macintosh Toolbox and QuickDraw technologies.
19. [x] Bring C-casts to the one style in game engine.
20. [x] Check argument of `SysBeep()` function.
21. [x] Fix bug with wrong Desk Accessories (DA) drawing above the application window, like "Calculator" applet.
22. [x] Set date seed for `Random()` function.
23. [x] Set private section for some classes methods and polish code.
24. [x] Add "..." to the "About 2048-ThinkC" menu item.
25. [x] Update engine source code.
26. [x] Fix random initialization.
27. [x] Fix font setting for offscreen drawing.
28. [x] Update engine sources.
29. [x] Check game on the Mac OS System 6 with color display.

## References and Books List

1. [Macintosh C Programming By Example, 1991](https://vintageapple.org/macprogramming/pdf/Macintosh_C_Programming_By_Example_1991.pdf)
2. [More Macintosh Toolbox, 1993](http://mirror.informatimago.com/next/developer.apple.com/documentation/mac/pdf/MoreMacintoshToolbox.pdf)
3. [Programming QuickDraw, 1992](https://vintageapple.org/macprogramming/pdf/Programming_QuickDraw_1992.pdf)
4. [THINK C Version 5 User Manual, 1991](http://mirror.macintosharchive.org/max1zzz.co.uk/+Mac%20OS%20Classic/Programming/THINK%20Pascal/Think_C_Version_5_User_Manual_1991.pdf)
5. [THINK C Version 5 Standard Libraries Reference, 1991](http://mirror.macintosharchive.org/max1zzz.co.uk/+Mac%20OS%20Classic/Programming/THINK%20Pascal/Think_C_Version_5_Standard_Libraries_Reference_1991.pdf)
6. [THINK C Version 5 Object-oriented Programming Manual, 1991](http://mirror.macintosharchive.org/max1zzz.co.uk/+Mac%20OS%20Classic/Programming/THINK%20Pascal/Think_C_Version_5_Object-Oriented_Programming_Manual_1991.pdf)
7. [ResEdit Reference For ResEdit 2.1, 1995](https://developer.apple.com/library/archive/documentation/mac/pdf/ResEditReference.pdf)
8. [Metrowerks Code Warrior Programming, 1995](https://vintageapple.org/macprogramming/pdf/Metrowerks_Code_Worrior_Programming_1995.pdf)
9. [QuickDraw GX Graphics, 1994](https://vintageapple.org/inside_r/pdf/QD_GX_Graphics_1994.pdf)
10. [Building and Managing Programs in MPW, 1996](https://sites.google.com/site/macintoshprogrammersworkshop/files)
11. [Carbon Porting Guide, 2002](http://mirror.informatimago.com/next/developer.apple.com/documentation/Carbon/Conceptual/carbon_porting_guide/carbonporting.pdf) | [Web version](https://developer.apple.com/library/archive/documentation/Carbon/Conceptual/carbon_porting_guide/cpg_intro_struct/cpg_intro_struct.html#//apple_ref/doc/uid/TP30000991)
12. [Handling Carbon Events, 2003](http://mirror.informatimago.com/next/developer.apple.com/documentation/Carbon/Conceptual/Carbon_Event_Manager/CarbonEvents.pdf)
13. [Handling Carbon Windows and Controls, 2002](http://mirror.informatimago.com/next/developer.apple.com/documentation/Carbon/Conceptual/HandlingWindowsControls/windowscontrols.pdf)
14. [Quartz 2D Programming Guide](http://mirror.informatimago.com/next/developer.apple.com/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/drawingwithquartz2d.pdf)

You can find literature, documentation, and source code on the following sites:

1. [Vintage Apple](https://vintageapple.org/)
2. [Informatimago Mirror](http://mirror.informatimago.com/next/developer.apple.com/documentation/)
3. [Macintosh Archive](http://mirror.macintosharchive.org/max1zzz.co.uk/+Mac%20OS%20Classic/)
4. [Infomac Mirror](http://ftp.knoppix.nl/infomac/)
5. [Apple Documentation Archive](https://developer.apple.com/library/archive/navigation/)
6. [Apple FTP Archive](https://macintoshgarden.org/apps/ftpapplecom-archive)
