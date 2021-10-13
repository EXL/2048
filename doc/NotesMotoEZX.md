Porting 2048 Game to EZX Platform
=================================

To create correct Makefiles, the configuration file of the `tmake` utility needs to be patched. See [2048-EZX/ReadMe.md](../2048-EZX/ReadMe.md) document for patching and general building information. The 2048-EZX project contains a ready-to-build and fixed Makefile already, so the patching step can be skipped.

## Task List

1. [x] Add some information about `tmake` and `progen` utilites.
2. [x] Add memory stats.
3. [x] Improve title bar widget: show game score via changing `QLabel` text.
4. [x] Disable touch clicks sound option.
5. [x] Create touch event controls.
6. [x] Implement basic game functionality.
7. [x] Add Telnet environment & run recipe.
8. [x] Test building on clean EZX SDK.
9. [x] Add PKG-package files.
10. [x] Create ReadMe.md files, screens, photos, etc.
11. [x] Create PKG-package building script.
12. [x] Add executable file/package information.
13. [ ] TODO: Adapt code for Motorola E680 or Motorola E680i.
