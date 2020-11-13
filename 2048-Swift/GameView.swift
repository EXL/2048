//
//  GameView.swift
//  2048-Swift
//
//  Created by EXL on 11/12/20.
//  Copyright © 2020 EXL. All rights reserved.
//

import Cocoa

let TILE_SIZE: Int32   = 64
let TILE_MARGIN: Int32 = 16

let smallFont = NSFont.boldSystemFont(ofSize: 18.0 as CGFloat)
let middleFont = NSFont.boldSystemFont(ofSize: 22.0 as CGFloat)
let normalFont = NSFont.systemFont(ofSize: 18.0 as CGFloat)
let largeFont = NSFont.boldSystemFont(ofSize: 28.0 as CGFloat)

@inline(__always) func R(rgb: UInt32) -> CGFloat { return CGFloat((rgb >> 16) & 0xFF) / 255.0 as CGFloat }
@inline(__always) func G(rgb: UInt32) -> CGFloat { return CGFloat((rgb >> 8) & 0xFF) / 255.0 as CGFloat }
@inline(__always) func B(rgb: UInt32) -> CGFloat { return CGFloat((rgb >> 0) & 0xFF) / 255.0 as CGFloat }

@inline(__always) func offsetCoords(coord: Int32, size: Int32, offset: Int32) -> Int32 {
	let start = (size / 2) - (((TILE_SIZE * LINE_SIZE) + (TILE_MARGIN * (LINE_SIZE - 1))) / 2)
	return coord * (TILE_MARGIN + TILE_SIZE) + start - offset
}

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

	override func draw(_ dirtyRect: NSRect) {
		(showBackground) ? getColor(aRgb: COLOR_BOARD, aAlpha: 1.0 as CGFloat).set() : NSColor.clear.set()
		bounds.fill(using: NSCompositingOperation.sourceOver)
		for y_index in 0..<LINE_SIZE {
			for x_index in 0..<LINE_SIZE {
				drawTile(value: p_board![Int(x_index + y_index * LINE_SIZE)], x: x_index, y: y_index)
			}
		}
		drawFinal()
	}

	func drawTile(value: Int32, x: Int32, y: Int32) {
		let xOffset = offsetCoords(coord: x, size: Int32(bounds.size.width), offset: 0)
		let yOffset = offsetCoords(coord: y, size: Int32(bounds.size.height), offset: TILE_MARGIN * 2)
		let tile = NSMakeRect(CGFloat(xOffset), CGFloat(yOffset), CGFloat(TILE_SIZE), CGFloat(TILE_SIZE))
		getColor(aRgb: e_background(value), aAlpha: 1.0 as CGFloat).set()
		(roundedTiles) ?
			NSBezierPath(roundedRect: tile, xRadius: 8.0 as CGFloat, yRadius: 8.0 as CGFloat).fill() :
			tile.fill()
		if (value > 0) {
			let strFont = (value < 100) ? largeFont : (value < 1000) ? middleFont : smallFont
			let strValue = String(value)
			let strAttributes = [
				NSAttributedStringKey.font: strFont,
				NSAttributedStringKey.foregroundColor: getColor(aRgb: e_foreground(value), aAlpha: 1.0 as CGFloat)
			]
			let strSize = strValue.size(withAttributes: strAttributes)
			let strPoint = NSMakePoint(
				CGFloat(xOffset + (TILE_SIZE - Int32(strSize.width)) / 2),
				CGFloat(yOffset + (TILE_SIZE - Int32(strSize.height)) / 2)
			)
			strValue.draw(at: strPoint, withAttributes: strAttributes)
		}
	}

	func drawFinal() {
		let bWin = (e_win as NSNumber).boolValue
		let bLose = (e_lose as NSNumber).boolValue
		let strScore = String(format: "GMScoreFMT".localized, e_score)
		let strEscape = "GMEscape".localized
		let strAttributes = [
			NSAttributedStringKey.font: normalFont,
			NSAttributedStringKey.foregroundColor: getColor(aRgb: COLOR_TEXT, aAlpha: 1.0 as CGFloat)
		]
		if (bWin || bLose) {
			let strCenter = (bWin) ? "GMYouWon".localized : "GMGameOver".localized
			let strAttributes = [
				NSAttributedStringKey.font: largeFont,
				NSAttributedStringKey.foregroundColor: getColor(aRgb: COLOR_FINAL, aAlpha: 1.0 as CGFloat)
			]
			getColor(aRgb: COLOR_OVERLAY, aAlpha: 0.5 as CGFloat).set()
			bounds.fill(using: NSCompositingOperation.sourceOver)
			let strSize = strCenter.size(withAttributes: strAttributes)
			let strCenterPoint = NSMakePoint(
				CGFloat(Int32(bounds.size.width) / 2 - Int32(strSize.width) / 2),
				CGFloat(Int32(bounds.size.height) / 2 - Int32(strSize.height) / 2)
			)
			strCenter.draw(at: strCenterPoint, withAttributes: strAttributes)
		}
		let strSize = strScore.size(withAttributes: strAttributes)
		let strEscapePoint = NSMakePoint(
			CGFloat(TILE_MARGIN),
			CGFloat(Int32(bounds.size.height - strSize.height) - 10)
		)
		let strScorePoint = NSMakePoint(
			CGFloat(Int32(bounds.size.width - strSize.width) - TILE_MARGIN),
			CGFloat(Int32(bounds.size.height - strSize.height) - 10)
		)
		strEscape.draw(at: strEscapePoint, withAttributes: strAttributes)
		strScore.draw(at: strScorePoint, withAttributes: strAttributes)
	}

	func initGameView() {
		e_init(K_Escape, K_Left, K_Right, K_Up, K_Down)
		if let bRectType = UserDefaults.standard.object(forKey: "roundedTiles") as? Bool {
			setRoundedTiles(value: bRectType)
		}
		if let bShowBackground = UserDefaults.standard.object(forKey: "showBackground") as? Bool {
			setShowBackground(value: bShowBackground)
		}
	}

	func getColor(aRgb: UInt32, aAlpha: CGFloat) -> NSColor {
		return NSColor(calibratedRed: R(rgb: aRgb), green: G(rgb: aRgb), blue: B(rgb: aRgb), alpha: aAlpha)
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
		setNeedsDisplay(bounds)
	}

	override var isFlipped: Bool {
		get {
			return true
		}
	}

	func setRoundedTiles(value: Bool) {
		roundedTiles = value
		UserDefaults.standard.set(roundedTiles, forKey: "roundedTiles")
		UserDefaults.standard.synchronize()
	}

	func setShowBackground(value: Bool) {
		showBackground = value
		UserDefaults.standard.set(showBackground, forKey: "showBackground")
		UserDefaults.standard.synchronize()
	}

	func updateMenus() {
		menuItemTiles.state = roundedTiles ? .on : .off
		menuItemBackground.state = showBackground ? .on : .off
	}

	@IBAction func menuReset(_ sender: NSMenuItem) {
		e_key(K_Escape)
		setNeedsDisplay(bounds)
	}

	@IBAction func menuTiles(_ sender: NSMenuItem) {
		setRoundedTiles(value: !roundedTiles)
		updateMenus()
		setNeedsDisplay(bounds)
	}

	@IBAction func menuBackground(_ sender: NSMenuItem) {
		setShowBackground(value: !showBackground)
		updateMenus()
		setNeedsDisplay(bounds)
	}

	@IBAction func menuSave(_ sender: NSMenuItem) {
		let strState = GameController.saveState()
		(!strState.isEmpty) ?
			showAlertSheet(title: "GMSaveOk".localized, information: strState) :
			showAlertSheet(title: "GMSaveError".localized, information: "GMSaveErrorDesc".localized)
	}

	@IBAction func menuLoad(_ sender: NSMenuItem) {
		let strState = GameController.loadState()
		(!strState.isEmpty) ?
			showAlertSheet(title: "GMLoadOk".localized, information: strState) :
			showAlertSheet(title: "GMLoadError".localized, information: "GMLoadErrorDesc".localized)
		setNeedsDisplay(bounds)
	}

	func showAlertSheet(title: String, information: String) {
		let alertSheet = NSAlert()
		alertSheet.messageText = title
		alertSheet.informativeText = information
		alertSheet.beginSheetModal(for: window!, completionHandler: nil)
	}
}
