//
//  GameView.swift
//  2048-Swift
//
//  Created by EXL on 11/12/20.
//  Copyright © 2020 EXL. All rights reserved.
//

import Cocoa

class GameView: NSView {
	@IBOutlet weak var menuItemTiles: NSMenuItem!
	@IBOutlet weak var menuItemBackground: NSMenuItem!

	var roundedTiles: Bool = true
	var showBackground: Bool = true

	required init?(coder aDecoder: NSCoder) {
		super.init(coder: aDecoder)
		initGameView()
	}

	override init(frame aFrame: NSRect) {
		super.init(frame: aFrame)
		initGameView()
	}

	func initGameView() {
		NSLog("Test!")
		// TODO: e_init
		let rectType: Bool = UserDefaults.standard.bool(forKey: "roundedTiles")
		let showBackground: Bool = UserDefaults.standard.bool(forKey: "showBackground")
		if (rectType) {
			setRoundedTiles(value: rectType)
		}
		if (showBackground) {
			setShowBackground(value: showBackground)
		}
	}

	override func keyDown(with event: NSEvent) {
		// TODO: e_key
		NSLog(event.charactersIgnoringModifiers!)
	}

	override var isFlipped: Bool {
		get {
			return true
		}
	}

	func setRoundedTiles(value: Bool) {
		roundedTiles = value
		UserDefaults.standard.set(value, forKey: "roundedTiles")
	}

	func setShowBackground(value: Bool) {
		showBackground = value
		UserDefaults.standard.set(value, forKey: "showBackground")
	}

	func updateMenus() {
		menuItemTiles.state = roundedTiles ? .on : .off
		menuItemBackground.state = showBackground ? .on : .off
	}

	@IBAction func menuReset(_ sender: NSMenuItem) {
		NSLog("Reset")
		// TODO: e_key
		setNeedsDisplay(frame)
	}

	@IBAction func menuTiles(_ sender: NSMenuItem) {
		setRoundedTiles(value: !roundedTiles)
		updateMenus()
		setNeedsDisplay(frame)
	}

	@IBAction func menuBackground(_ sender: NSMenuItem) {
		setShowBackground(value: !showBackground)
		updateMenus()
		setNeedsDisplay(frame)
	}

	@IBAction func menuSave(_ sender: NSMenuItem) {
		NSLog("Save!")
		// TODO: e_save
	}

	@IBAction func menuLoad(_ sender: NSMenuItem) {
		NSLog("Load!")
		// TODO: e_load
	}
}
