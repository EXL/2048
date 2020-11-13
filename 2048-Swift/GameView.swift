//
//  GameView.swift
//  2048-Swift
//
//  Created by EXL on 11/12/20.
//  Copyright © 2020 EXL. All rights reserved.
//

import Cocoa

//
//  Key Codes Table.
//  Additional Information:
//    https://stackoverflow.com/a/2080324
//    https://stackoverflow.com/a/59995062
//    https://gist.github.com/swillits/df648e87016772c7f7e5dbed2b345066
//
let K_Escape = Int32(0x35)
let K_R      = Int32(0x0F)
let K_W      = Int32(0x0D)
let K_A      = Int32(0x00)
let K_S      = Int32(0x01)
let K_D      = Int32(0x02)
let K_Left   = Int32(NSLeftArrowFunctionKey)
let K_Right  = Int32(NSRightArrowFunctionKey)
let K_Up     = Int32(NSUpArrowFunctionKey)
let K_Down   = Int32(NSDownArrowFunctionKey)

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
		e_init(K_Escape, K_Left, K_Right, K_Up, K_Down)
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
		let keyCode = Int32(event.keyCode)
		switch keyCode {
		case K_R:
			e_key(K_Escape)
		case K_W:
			e_key(K_Up)
		case K_A:
			e_key(K_Left)
		case K_S:
			e_key(K_Down)
		case K_D:
			e_key(K_Right)
		default:
			e_key(keyCode)
		}
		setNeedsDisplay(frame)
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
		e_key(K_Escape)
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
