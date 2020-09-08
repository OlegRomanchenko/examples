import QtQuick 2.14
import QtQuick.Window 2.14
import TableModel 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Phone Book")

    TableView {
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        model: TableModel {}

        delegate: Rectangle {
            implicitWidth: 200
            implicitHeight: 50
            border.width: 1

            Text {
                text: display
                anchors.centerIn: parent
            }
        }
    }
}
