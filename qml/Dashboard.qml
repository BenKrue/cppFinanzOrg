import QtQuick 2.15
import QtQuick.Controls 2.15
import QtCharts 2.15

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
            color: '#ffffff'
            font.pixelSize: 24
            anchors.centerIn: parent
        }
        ChartView {
            //anchors.fill: parent
            title: "Beispiel für ein Balkendiagramm"
            width: 400
            height: 700
            legend.visible: true
            legend.font.pointSize: 15
            theme: ChartView.ChartThemeDark
            legend.alignment: Qt.AlignRight
            antialiasing: true

            HorizontalStackedBarSeries {
                id: ioBarchart
                objectName: "ioBarchart"
                axisY: BarCategoryAxis { categories: ["Ketegorien", "Ausgaben"] }
                BarSet { label: "Kredite"; values: [2500, 0] }
                BarSet { label: "Nebenkosten"; values: [550, 0] }
                BarSet { label: "Freizeit"; values: [700, 0] }
                BarSet { label: "Total"; values: [0, 1500] }
            }
        }
    }
}



