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

	static func saveState() -> String {
		let formatter = DateFormatter()
		formatter.dateStyle = .long
		formatter.timeStyle = .long
		let strState = String(format: "GMStateFMT".localized, formatter.string(from: Date()))
		UserDefaults.standard.set(strState, forKey: "saveDate")
		for i in 0..<BOARD_SIZE {
			UserDefaults.standard.set(p_board![Int(i)], forKey: String(format: "saveBoard_%d", i))
		}
		UserDefaults.standard.set(e_score, forKey: "saveScore")
		UserDefaults.standard.set((e_win as NSNumber).boolValue, forKey: "saveWin")
		UserDefaults.standard.set((e_lose as NSNumber).boolValue, forKey: "saveLose")
		return (UserDefaults.standard.synchronize()) ? strState : ""
	}

	// TODO: Load static func.
	static func loadState() -> String {
		let formatter = DateFormatter()
		formatter.dateStyle = .long
		formatter.timeStyle = .long
		let strState = String(format: "GMStateFMT".localized, formatter.string(from: Date()))
		return strState
	}

	func applicationDidFinishLaunching(_ notification: Notification) {
		gameView.window?.makeKeyAndOrderFront(self)
		gameView.window?.makeFirstResponder(gameView)
		gameView.updateMenus()
	}

	func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool {
		return true
	}
}
