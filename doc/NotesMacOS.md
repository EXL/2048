Mac OS Notes
============

## Mac OS X 10.6.8 "Snow Leopard" problems

### Problem with `NSFont *` instance variables.

#### Affected environment:

* Mac OS X "Snow Leopard" at least 10.6.8 version.
* Xcode 3 and 4 major versions.

#### Minimal reproducible example:

```objc
// MyView.h

@interface MyView : NSView {
	NSFont *largeFont;
}
```

```objc
// MyView.m

@implementation MyView

- (void)awakeFromNib {
	largeFont = [NSFont systemFontOfSize:28.0f];
}

- (void)drawRect:(NSRect)rect {
	if (largeFont)
		NSLog(@"%p:%@", largeFont, largeFont);
}

@end
```

#### Description:

The first rendering frame - everything is fine, information about the font is displayed in the log. The second redraw frame causes the application to crash. It seems that the `largeFont` pointer is being invalidated somewhere. The pointer in this case isn't reset to `nil` and `EXC_BAD_ACCESS` error occurs directly in `NSLog()` function.

```
(gdb) bt
#0  0x00007fff8580dd05 in -[NSFont description] ()
#1  0x00007fff81eaa492 in _NSDescriptionWithLocaleFunc ()
#2  0x00007fff89c88ded in _CFStringAppendFormatAndArgumentsAux ()
#3  0x00007fff89c8826d in _CFStringCreateWithFormatAndArgumentsAux ()
#4  0x00007fff89d079bf in _CFLogvEx ()
#5  0x00007fff81f0bd70 in NSLogv ()
#6  0x00007fff81f0bd08 in NSLog ()
#7  0x00000001000017e8 in -[GameView drawRect:] (self=0x100173880, _cmd=0x7fff85ba3560) at /Users/exl/Desktop/TestShit/TestShit/GameView.m:20
...
```

The backtrace shows that the fall occurs on the `- [NSFont description]` method inside the Cocoa (AppKit) framework.

#### Additional research:

Modification the draw-method as follows shows that `largeFont` pointer changes its address after first rendered frame.

```objc
- (void)drawRect:(NSRect)rect {
	NSFont *largeFont = [NSFont systemFontOfSize:28.0f];
	NSLog(@"%p:%@", largeFont, largeFont);
}
```

Mac OS X 10.6.8 output:

```
0x100166a30:"LucidaGrande 28.00 pt. P [] (0x100166a30) fobj=0x100166cc0, spc=8.86"
0x100144210:"LucidaGrande 28.00 pt. P [] (0x100144210) fobj=0x10016ae20, spc=8.86"
0x100144210:"LucidaGrande 28.00 pt. P [] (0x100144210) fobj=0x10016afe0, spc=8.86"
0x100144210:"LucidaGrande 28.00 pt. P [] (0x100144210) fobj=0x10015bcd0, spc=8.86"
0x100144210:"LucidaGrande 28.00 pt. P [] (0x100144210) fobj=0x10018f380, spc=8.86"
...
```

macOS X 10.13.6 output:

```
0x604000245880:".SFNSDisplay 28.00 pt. P [] (0x604000245880) fobj=0x1028269e0, spc=6.10"
0x604000245880:".SFNSDisplay 28.00 pt. P [] (0x604000245880) fobj=0x10052ef30, spc=6.10"
0x604000245880:".SFNSDisplay 28.00 pt. P [] (0x604000245880) fobj=0x100605770, spc=6.10"
0x604000245880:".SFNSDisplay 28.00 pt. P [] (0x604000245880) fobj=0x10282fa00, spc=6.10"
0x604000245880:".SFNSDisplay 28.00 pt. P [] (0x604000245880) fobj=0x10282fa00, spc=6.10"
...
```

Modern and some older versions of Mac OS are not affected by the issue.

#### Fix:

Don't use instance variables for `NSFont` objects.

```objc
#define largeFont [NSFont systemFontOfSize:28.0f]
```

The problem can be solved by local calls or defines. See 97b57132b8df8c66841e96452f02cdf9cecfbc9e commit for more information.
