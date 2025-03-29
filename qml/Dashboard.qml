import QtQuick 6.0
import QtQuick.Controls 6.0

Rectangle
{
    property alias dashboarWidth: dashboard.width
    property alias dashboardHeight: dashboard.height
    property alias dashboardColor: dashboard.color
    property alias dashboardView: dashboard.opacity
    property alias dashboardPosX: dashboard.x
    property alias dashboardPosY: dashboard.y

    Rectangle
    {
        id: dashboard

        Label {
            text: "Dashboard"
            font.pixelSize: 24
        }
    }
}


