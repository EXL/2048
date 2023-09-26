Application {
	Depends { name: "sdk" }
	files: [ "2048-AHI.c", "../../src/2048.c" ]

	cpp.defines: [ "EP1", "USE_MME" ]
	cpp.optimization: "O2"
	cpp.includePaths: [ "../../src", "../../image/icon/precompiled", "../../image/gfx"]
	cpp.staticLibraries: ["Lib"]
}
