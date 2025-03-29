import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts

import "globals.js" as Global

ApplicationWindow
{
    id: root
    visible: true
    width: Screen.width
    height: Screen.height
    title: "FinanzOrg - Benjamin Krüger"
    color: "white"

    property var createComponantDashboard
    property var createComponentTableView

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
                y: (rectSideBar.height / 3) + 100

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        
                        if (!createComponantDashboard) {
                            Global.dashboardEnabled = true
                            Global.tableViewEnabled = false
                            jsHelper.createDashboard(Global.dashboardEnabled)
                        }
                        else {
                            createComponantDashboard.destroy()
                            Global.dashboardEnabled = false
                            Global.tableViewEnabled = false
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
            Image
            {
                id: imageTable
                source: "qrc:/images/tabelle.png"
                width: 40
                height: 40
                x: (rectSideBar.width / 2) - (width / 2)
                y: (rectSideBar.height / 3)

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        
                        // if (!customTableComponend) {
                        //     Global.dashboardEnabled = false
                        //     Global.tableViewEnabled = true
                        jsHelper.createTableView(true)
                        // }
                        // else {
                        //     customTableComponend.destroy()
                        //     Global.dashboardEnabled = false
                        //     Global.tableViewEnabled = false
                        // }
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
            Image
            {
                id: imageLogOut
                source: "qrc:/images/ausloggen.png"
                width: 40
                height: 40
                x: (rectSideBar.width / 2) - (width / 2)
                y: (rectSideBar.height - (3 * height))

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
                        dashboarWidth: rectView.width,
                        dashboardHeight: rectView.height,
                        dashboardColor: '#ffffff' 
                    });
                }

                function createTableView(visible) {
                    createComponentTableView = customTableComponent.createObject(rectView, {
                        tableViewPosX: 0,
                        tableViewPosY: 0,
                        tableViewView: visible,
                        tableViewWidth: rectView.width,
                        TableViewHeight: rectView.height,
                        tableViewColor: '#000000'
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
}
