import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0

Window {
	property int w: 340
	property int h: 400
	property int tileSize: 64
	property int tileMargin: 16

	width: w; height: h
	minimumWidth: w; minimumHeight: h
	visible: true
	title: qsTr("2048-QtQuick")

	ColumnLayout {
		anchors.fill: parent

		GridLayout {
			Layout.alignment: Qt.AlignCenter
			columns: 4 // FROM C
			columnSpacing: tileMargin; rowSpacing: tileMargin

			Repeater {
				model: 16 // FROM_C

				Rectangle {
					width: tileSize; height: tileSize
					radius: 10
					color: "red"

					Text {
						anchors.centerIn: parent
						text: qsTr("text")
						color: "blue"
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
}
