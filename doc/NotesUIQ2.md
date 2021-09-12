Porting 2048 Game to UIQ2 Platform
==================================

Vanilla Symbian UIQ2 SDK is tested and works on Windows 2000 SP4 with installed Visual C++ 6.0 SP6 IDE.

## WSD (Writeable Static Data)

Symbian OS is designed to be able to run on read-only storage devices. Therefore, DLLs located in ROM cannot contain code that writes to the its data segment. Shared libraries in Symbian UIQ2 platform do not support WSD and mutable global variables so this is reason of a [branch of a "2048" engine](../src/wsd/) that doesn't use WSD. Additional information links:

1. [Apps:Symbian Platform Support for Writeable Static Data in DLLs](https://www.akawolf.org/wiki/index.php/Apps:Symbian_Platform_Support_for_Writeable_Static_Data_in_DLLs)
2. [No Writable Static Data in DLLs](https://www.25yearsofprogramming.com/c/no-writable-static-data-in-dlls.html)
3. [Workarounds to avoid writable static data](https://www.25yearsofprogramming.com/developer/workarounds-to-avoid-writable-static-data.html)
4. [Symbian OS guide => Essential idioms => Static data](https://docs.huihoo.com/symbian/s60-3rd-edition-cpp-developers-library-v1.1/GUID-35228542-8C95-4849-A73F-2B4F082F0C44/html/SDL_93/doc_source/guide/EssentialIdioms/StaticData.html)

## Symbian UIQ2 Emulator/Simulator

Sometimes compiled applications don't appear in the main menu of the Symbian UIQ emulator/simulator. In this case, restarting the emulator to release `epoc -urel` and returning back to debug `epoc -udeb` helps to avoid problem.

## C Standard Library

There is a small nuance in using C-language standard library on Symbian platform. When application finishes need to call the `CloseSTDLIB()` function declared in `sys/reent.h` include file. Otherwise, there may be problems with a periodic crash of the application on exit and memory leaks:

1. [Программирование под Symbian OS: начало](https://rsdn.org/article/pda/symbian.xml)
2. [GUI App: Porting an Engine for Use in a Symbian Application](https://docs.huihoo.com/symbian/nokia-symbian3-developers-library-v0.8/GUID-BB39DE14-B314-59CB-A8EC-BBD2A5C1BCD9.html)

## Documentation

The documentation files that come with the Symbian UIQ2 SDK along with code examples are very useful for learning APIs and various techniques for creating Symbian UIQ2 applications.

* `C:\Symbian\UIQ_21\Documentation\uiq21.chm`
* `C:\Symbian\UIQ_21\Starters Guide\Starter's Guide.chm`

## Task List

1. [x] Create installable SIS-packages (armi, arm4, thumb) for Symbian UIQ 2.0 (2.1) and test them on Motorola FOMA M1000.
2. [x] Create UIQ2-application skeleton.
3. [x] Create proper application icons.
4. [x] Create all documentation files and notes.
5. [x] Insert SIM-card and set correct time & date when need to take screenshots and photos.
6. [x] Add non-WSD (Writeable Static Data) version of engine.
7. [x] Create menus and implement them.
8. [x] Implement basic drawing.
9. [x] Use Double Buffering for drawing game context.
10. [x] Set proper font drawing.
11. [x] Create about dialog with icon.
12. [x] Add photo with Motorola A1000.
13. [x] Add photo with Motorola A925.
14. [ ] TODO: Try to sign SIS-package and run it on Motorola A920.

## Motorola FOMA M1000 key codes table

| key        | code   |
|------------|--------|
| Joy Up     | 0xF846 |
| Joy Down   | 0xF847 |
| Joy Left   | 0xF848 |
| Joy Right  | 0xF849 |
| Joy Center | 0xF84A |
| Game A     | 0xF85C |
| Game B     | 0xF85D |

## Dead Links to Motorola SDKs and other files

1. [SDK_A1000_beta.zip](http://www.motocoder.com/motorola/download.jsp?FILENAME=downloads/files/SDK_A1000_beta.zip)
2. [A1000_SDK_Users_Guide.pdf](http://www.motocoder.com/motorola/download.jsp?FILENAME=downloads/pdf/A1000_SDK_Users_Guide.pdf)
3. [M1000SDK_v1_0.zip](http://www.motocoder.com/motorola/download.jsp?FILENAME=downloads/files/M1000SDK_v1_0.zip)
4. [M1000_SDK_Users_Guide.pdf](http://www.motocoder.com/motorola/download.jsp?FILENAME=downloads/pdf/M1000_SDK_Users_Guide.pdf)
5. [A925SDK.zip](http://www.motocoder.com/motorola/download.jsp?FILENAME=downloads/files/A925SDK.zip)
