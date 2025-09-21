import QtQuick 2.15
import QtQuick.Controls 2.15
import QtCharts 2.15
import QtQuick.Layouts

Rectangle
{
    id: rootDashboard
    property alias dashboardWidth: rootDashboard.width
    property alias dashboardHeight: rootDashboard.height
    property alias dashboardColor: rootDashboard.color
    property alias dashboardView: rootDashboard.opacity
    property alias dashboardPosX: rootDashboard.x
    property alias dashboardPosY: rootDashboard.y

    color: '#FFFFFF'

    GridLayout
    {
        id: dashboard
        anchors.fill: parent
        columns: 2
        rowSpacing: 2
        columnSpacing: 2

        ChartView {
            id: chartView
            title: "Beispiel für ein Balkendiagramm"
            Layout.fillWidth: true
            Layout.fillHeight: true

            legend.visible: true
            legend.font.pointSize: 15
            theme: ChartView.ChartThemeBlueNcs
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

        ChartView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            antialiasing: true
            theme: ChartView.ChartThemeBlueNcs

            LineSeries {
                name: "Chart 2"
                XYPoint { x: 0; y: 1 }
                XYPoint { x: 1; y: 3 }
                XYPoint { x: 2; y: 2 }
            }
        }

        ChartView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            antialiasing: true
            theme: ChartView.ChartThemeBlueNcs

            PieSeries {
                name: "Beispiel Kreisdiagramm"
                PieSlice { label: "Rot"; value: 10 }
                PieSlice { label: "Blau"; value: 20 }
                PieSlice { label: "Grün"; value: 30 }
            }
        }

        ChartView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            antialiasing: true
            theme: ChartView.ChartThemeBlueNcs

            AreaSeries {
                name: "Flächendiagramm"
                upperSeries: LineSeries {
                    XYPoint { x: 0; y: 1 }
                    XYPoint { x: 1; y: 3 }
                    XYPoint { x: 2; y: 2 }
                }
            }
        }

    }
}