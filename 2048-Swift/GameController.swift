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
		UserDefaults.standard.set(e_win, forKey: "saveWin")
		UserDefaults.standard.set(e_lose, forKey: "saveLose")
		return (UserDefaults.standard.synchronize()) ? strState : ""
	}

	static func loadState() -> String {
		if let strState = UserDefaults.standard.object(forKey: "saveDate") as? String {
			for i in 0..<BOARD_SIZE {
				if let value = UserDefaults.standard.object(forKey: String(format: "saveBoard_%d", i)) as? Int32 {
					p_board![Int(i)] = value
				}
			}
			if let score = UserDefaults.standard.object(forKey: "saveScore") as? Int32 {
				e_score = score
			}
			if let win = UserDefaults.standard.object(forKey: "saveWin") as? Int32 {
				e_win = win
			}
			if let lose = UserDefaults.standard.object(forKey: "saveLose") as? Int32 {
				e_lose = lose
			}
			return strState
		}
		return ""
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
