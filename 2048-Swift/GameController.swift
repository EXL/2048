//
//  GameController.swift
//  2048-Swift
//
//  Created by EXL on 11/10/20.
//  Copyright © 2020 EXL. All rights reserved.
//

import Cocoa

@NSApplicationMain
class GameController: NSObject, NSApplicationDelegate {
	@IBOutlet weak var gameView: GameView!

	// TODO: Save static func.
	// TODO: Load static func.

	func applicationDidFinishLaunching(_ notification: Notification) {
		gameView.window?.makeKeyAndOrderFront(self)
		gameView.window?.makeFirstResponder(gameView)
		gameView.updateMenus()
	}

	func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool {
		return true
	}
}
