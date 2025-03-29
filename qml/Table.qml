import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle
{
    property alias tableViewWidth: tableView.width
    property alias tableViewHeight: tableView.height
    property alias tableViewColor: tableView.color
    property alias tableViewView: tableView.opacity
    property alias tableViewPosX: tableView.x
    property alias tableViewPosY: tableView.y

    color: '#ffffff'

    ColumnLayout
    {
        spacing: 2

        Rectangle
        {
            id: tableView
            Layout.preferredWidth: tableView.width
            Layout.preferredHeight: 70
            Layout.alignment: Qt.AlignCenter
            
            Label {
                text: "TableView"
                color: '#ffffff'
                font.pixelSize: 24
                anchors.centerIn: parent
            }
        }
        Rectangle
        {
            id: rectTable
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: tableView.width
            Layout.preferredHeight: 800
            color: tableView.color

            HorizontalHeaderView {
                id: horizontalHeader
                anchors.left: tableViewId.left
                anchors.top: parent.top
                syncView: tableViewId
                clip: true
            }

            VerticalHeaderView {
                id: verticalHeader
                anchors.top: tableViewId.top
                anchors.left: parent.left
                syncView: tableViewId
                clip: true
            }

            TableView {
                id: tableViewId
                anchors.left: verticalHeader.right
                anchors.top: horizontalHeader.bottom
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                clip: true

                columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds

                model: tableModel
                
                delegate: Rectangle {
                    implicitWidth: 250
                    implicitHeight: 30
                    color: '#ffffff'
                    
                    property bool editing: false
                    TextField {
                        id: editField
                        anchors.fill: parent
                        visible: editing
                        text: model.display
                        focus: editing
                        onEditingFinished: {
                            tableModel.updateCell(model.row, model.column, text)
                            editing = false
                        }
                    }
                    Text {
                        anchors.centerIn: parent
                        text: model.display
                        visible: !editing
                    }
                    MouseArea {
                        anchors.fill: parent
                        onDoubleClicked: editing = true
                    }
                }
            }
        }
    }
}