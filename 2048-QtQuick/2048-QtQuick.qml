import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0

Window {
	property int w: 340
	property int h: 400
	property int tileSize: 64
	property int tileMargin: 16
	property int lineWidth: gameEngine.lineSize()

	width: w; height: h
	minimumWidth: w; minimumHeight: h
	visible: true
	title: qsTr("2048-QtQuick")
	color: gameEngine.boardColor()

	ColumnLayout {
		anchors.fill: parent

		GridView {
			id: grid
			Layout.alignment: Qt.AlignCenter
			width: tileSize * lineWidth + tileMargin * lineWidth; height: tileSize * lineWidth + tileMargin * lineWidth
			cellWidth: tileSize + tileMargin; cellHeight: tileSize + tileMargin
			model: gameBoard

			delegate: Item {
				width: grid.cellWidth; height: grid.cellHeight

				Rectangle {
					anchors.fill: parent; anchors.margins: tileMargin / 2
					radius: 10
					color: gameEngine.backgroundColor(modelData)

					Text {
						anchors.centerIn: parent
						text: modelData > 0 ? modelData : ""
						color: gameEngine.foregroundColor(modelData)
						font.bold: true; font.pointSize: modelData < 100 ? 24 : modelData < 1000 ? 18 : 14
					}
				}
			}
		}

		RowLayout {
			Layout.margins: 10

			Text {
				text: qsTr("ESC to Restart!")
				font.pointSize: 16
				color: gameEngine.textColor()
			}

			Item { Layout.fillWidth: true }

			Text {
				text: qsTr("Score: ") + gameScore
				font.pointSize: 16
				color: gameEngine.textColor()
			}
		}
	}

	Item {
		anchors.fill: parent
		visible: gameWin || gameLose

		Rectangle {
			anchors.fill: parent
			color: gameEngine.overlayColor(); opacity: 0.5
		}

		Text {
			anchors.centerIn: parent
			text: gameWin ? qsTr("You won!") : qsTr("Game Over!")
			color: gameEngine.finalColor()
			font.bold: true; font.pointSize: 24
		}
	}

	Item {
		focus: true
		Keys.onPressed:	gameEngine.keyEvent(event.key)
	}
}
