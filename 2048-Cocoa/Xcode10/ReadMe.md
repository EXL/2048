2048-Cocoa
==========

## Build & Deploy

```bash
xcodebuild -scheme 2048-Cocoa archive -archivePath 2048-Cocoa
xcodebuild -exportArchive -archivePath 2048-Cocoa.xcarchive -exportPath build -exportOptionsPlist 2048-Cocoa.xcarchive/Info.plist
```
