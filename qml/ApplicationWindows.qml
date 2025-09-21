import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts

import "globals.js" as Global

ApplicationWindow
{
    id: root
    visible: true
    width: Screen.width
    height: Screen.height - 100
    title: "FinanzOrg - Benjamin Krüger"
    color: "white"

    property var createComponantDashboard
    property var customTableComponend
    property var createComponentTableView
    property var createComponentDummy

    menuBar: MenuBar
    {
        Menu
        {
            title: "File"
            MenuItem { text: "Load" }
            MenuItem { text: "Save" }
            MenuItem { text: "Close"; onTriggered: Qt.quit() }
        }
        Menu
        {
            title: "Properties"
            MenuItem { text: "Layout" }
            MenuItem { text: "Claculator" }
        }
        Menu
        {
            title: "About"
            MenuItem { text: "License"}
            MenuItem { text: "Company"}
        }
    }
    RowLayout
    {
        id: layout
        anchors.fill: parent
        spacing: 3
        Rectangle
        {
            id: rectSideBar
            color: '#ffffff'
            Layout.fillWidth: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 200
            Layout.minimumHeight: parent.height

            Image
            {
                source: "qrc:/images/nutzer.png"
                width: 100
                height: 100
                x: (rectSideBar.width / 2) - (width / 2)
                y: (rectSideBar.height / 10)
            }
            Label
            {
                id: userName
                text: "Benjamin Krüger"
                scale: 2
                x: (rectSideBar.width / 2) - (width / 2)
                y: (rectSideBar.height / 10) + 110
            }
            Image
            {
                id: imageDashboard
                source: "qrc:/images/dashboard.png"
                width: 40
                height: 40
                x: (rectSideBar.width / 2) - (width / 2)
                y: (rectSideBar.height / 3)

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        
                        if (!Global.dashboardEnabled) {
                            Global.dashboardEnabled = true
                            Global.tableViewEnabled = false
                            jsHelper.createDashboard(Global.dashboardEnabled)
                        }
                    }
                    onEntered: {
                        imageDashboard.width = 45;
                        imageDashboard.height = 45;
                    }
                    onExited: {
                        imageDashboard.width = 40;
                        imageDashboard.height = 40;
                    }
                }
                Behavior on width { NumberAnimation { duration: 200 } }
                Behavior on height { NumberAnimation { duration: 200 } }
            }
            Text {
                id: dashboardImageText
                text: "Dashboard"
                anchors.top: imageDashboard.bottom // Text unter dem Bild
                anchors.horizontalCenter: imageDashboard.horizontalCenter // Text zentriert unter dem Bild
                font.pixelSize: 20
                color: "black"
                anchors.topMargin: 10 // Abstand zwischen Bild und Text
            }
            Image
            {
                id: imageTable
                source: "qrc:/images/tabelle.png"
                width: 40
                height: 40
                x: (rectSideBar.width / 2) - (width / 2)
                y: (rectSideBar.height / 3) + 100

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        
                        if (!Global.tableViewEnabled) {
                            Global.dashboardEnabled = false
                            Global.tableViewEnabled = true
                            jsHelper.createTableView(Global.tableViewEnabled)
                        }
                    }
                    onEntered: {
                        imageTable.width = 45;
                        imageTable.height = 45;
                    }
                    onExited: {
                        imageTable.width = 40;
                        imageTable.height = 40;
                    }
                }
                Behavior on width { NumberAnimation { duration: 200 } }
                Behavior on height { NumberAnimation { duration: 200 } }
            }
            Text {
                id: tableImageText
                text: "Table"
                anchors.top: imageTable.bottom // Text unter dem Bild
                anchors.horizontalCenter: imageTable.horizontalCenter // Text zentriert unter dem Bild
                font.pixelSize: 20
                color: "black"
                anchors.topMargin: 10 // Abstand zwischen Bild und Text
            }
            Image
            {
                id: imageLogOut
                source: "qrc:/images/ausloggen.png"
                width: 40
                height: 40
                x: (rectSideBar.width / 2) - (width / 2)
                y: (rectSideBar.height - (3 * height)) - 100

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: Qt.quit()
                    onEntered: {
                        imageLogOut.width = 45;
                        imageLogOut.height = 45;
                    }
                    onExited: {
                        imageLogOut.width = 40;
                        imageLogOut.height = 40;
                    }
                }
                Behavior on width { NumberAnimation { duration: 200 } }
                Behavior on height { NumberAnimation { duration: 200 } }
            }
            Text {
                id: logOutImageText
                text: "Exit"
                anchors.top: imageLogOut.bottom
                anchors.horizontalCenter: imageLogOut.horizontalCenter
                font.pixelSize: 20
                color: "black"
                anchors.topMargin: 10
            }
        }
        Rectangle
        {
            id: rectView
            color: 'white'
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: parent.height

            QtObject {
                id: jsHelper

                
                function createDashboard(visible) {
                    createComponantDashboard = customDashboardComponent.createObject(rectView, {
                        dashboardPosX: 0,
                        dashboardPosY: 0,
                        dashboardView: visible,
                        dashboardWidth: rectView.width,
                        dashboardHeight: rectView.height,
                        dashboardColor: '#FFFFFF' 
                    });
                }

                function createTableView(visible) {
                    createComponentTableView = customTableComponent.createObject(rectView, {
                        tableViewPosX: 0,
                        tableViewPosY: 0,
                        tableViewView: visible,
                        tableViewWidth: rectView.width,
                        tableViewHeight: rectView.height,
                        tableViewColor: '#000000'
                    });
                }
                function createDummyView(visible) {
                    createComponentDummy = customDummyComponent.createObject(rectView, {
                        dummyPosX: 0,
                        dummyPosY: 0,
                        dummyView: visible,
                        dummyWidth: rectView.width,
                        dummyHeight: rectView.height,
                        dummyColor: '#ffffff'
                    });
                }
            }
        }
    }
    Component
    {
        id: customDashboardComponent
        Dashboard {}
    }
    Component
    {
        id: customTableComponent
        Table {}
    }
    Component
    {
        id: customDummyComponent
        Dummy {}
    }
}
