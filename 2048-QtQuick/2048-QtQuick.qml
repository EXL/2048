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

	ColumnLayout {
		anchors.fill: parent

		GridView {
			id: grid
			Layout.alignment: Qt.AlignCenter
			width: tileSize * lineWidth + tileMargin * lineWidth; height: tileSize * lineWidth + tileMargin * lineWidth
			cellWidth: tileSize + tileMargin; cellHeight: tileSize + tileMargin
			model: gameBoard

			delegate: Item {
				width: grid.cellWidth
				height: grid.cellHeight
				Rectangle {
					anchors.fill: parent
					anchors.margins: tileMargin / 2
					radius: 10
					color: gameEngine.rectColor(modelData)

					Text {
						anchors.centerIn: parent
						text: (modelData > 0) ? modelData : ""
						color: gameEngine.textColor(modelData)
						font.bold: true
						font.pointSize: 12
					}
				}
			}
		}

		RowLayout {
			Rectangle {
				width: tileSize; height: tileSize
				color: "red"
			}
			Item {
				Layout.fillWidth: true
			}
			Rectangle {
				width: tileSize; height: tileSize
				color: "blue"
			}
		}
	}

	Item {
		focus: true
		Keys.onPressed: {
			gameEngine.keyEvent(event.key)
			gameEngine.updateGameBoard()
		}
	}
}
