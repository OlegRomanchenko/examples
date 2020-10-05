import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import TableModelPhoneBook 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Phone Book")

        TableView {
            id: tableView
            anchors.top: horizontalHeader.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            columnSpacing: 1
            rowSpacing: 1

            ScrollBar.horizontal: ScrollBar { id: hbar; active: vbar.active }
            ScrollBar.vertical: ScrollBar { id: vbar; active: hbar.active }

            model: TableModelPhoneBook { id: tableModelPhoneBook }

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

        HorizontalHeaderView {
            id: horizontalHeader
            syncView: tableView
            anchors.top: parent.top
        }
}
