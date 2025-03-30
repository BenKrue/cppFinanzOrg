import QtQuick 2.15
import QtQuick.Controls 2.15
import QtCharts 2.15
import QtQuick.Layouts

Rectangle
{
    property alias dashboardWidth: dashboard.width
    property alias dashboardHeight: dashboard.height
    property alias dashboardColor: dashboard.color
    property alias dashboardView: dashboard.opacity
    property alias dashboardPosX: dashboard.x
    property alias dashboardPosY: dashboard.y

    ColumnLayout
    {
        spacing: 3

        Rectangle
        {
            id: dashboard
            Layout.preferredWidth: dashboard.width
            Layout.preferredHeight: 70
            Layout.alignment: Qt.AlignCenter

            Label {
                text: "Dashboard"
                color: '#000000'
                font.pixelSize: 24
                anchors.centerIn: parent
            }
        }
        Rectangle
        {
            id: rectChartView
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: dashboard.width
            Layout.preferredHeight: 610
            color: dashboard.color

            ChartView
            {
                id : mChart
                width: dashboard.width
                height: 600
                title: "Einnahmen und Ausgaben nach Kategorie"

                Component.onCompleted: {
                    var mHorSeries = mChart.createSeries(ChartView.SeriesTypeHorizontalBar)
                    var categoryAxisY = Qt.createQmlObject('import QtCharts 2.2; BarCategoryAxis {}', mChart);
                    mHorSeries.axisY = categoryAxisY

                    categoryAxisY.categories = [""]
                    setAxisY(categoryAxisY, mHorSeries);

                    mChart.axisX(mHorSeries).min= -2000 //Math.min.apply(null, mBarSet.values)
                    mChart.axisX(mHorSeries).max= 3500 //Math.max.apply(null, mBarSet.values)

                    for (var i = 0; i < dataModel.werte.length; ++i) {
                        var mBarSet = mHorSeries.append(dataModel.category[i], [dataModel.werte[i]])
                    }
                }

                // Item {
                //     id: tooltipItem
                //     visible: false
                //     width: 200
                //     height: 50

                //     Rectangle {
                //         id: tooltipBackground
                //         color: "white"
                //         border.color: "black"
                //         radius: 5
                //         anchors.fill: parent
                //     }
                //     Text {
                //         id: tooltipText
                //         color: "black"
                //         font.bold: true
                //         anchors.centerIn: parent
                //     }
                // }
                // MouseArea {
                //     anchors.fill: parent
                //     onPositionChanged: {
                //         var index = Math.floor((mouse.x - 475) / (((dashboard.width - 105) / 2) / barSeries.count));
                //         if (index >= 0 && index < barSeries.count) {
                //             tooltipText.text = "Kategorie: " + category[index] + "\nWert: " + roundToDecimalPlaces(werte[index], 2) + "€";
                //             tooltipItem.visible = true;
                //             tooltipItem.x = mouse.x;
                //             tooltipItem.y = mouse.y - 80; // Position über dem Balken
                //         } else {
                //             tooltipItem.visible = false;
                //         }
                //     }
                //     onClicked: {
                //         tooltipItem.visible = false; // Tooltip ausblenden bei Klick
                //     }
                // }
            }
        }
        Rectangle
        {
            id: dashboard1
            Layout.preferredWidth: dashboard.width
            Layout.preferredHeight: 70
            Layout.alignment: Qt.AlignCenter

            
            Rectangle {
                id: rectausgaben
                x: 80; y: 0; width: 400; height: 250
                color: '#FF0000'

                Component.onCompleted: {
                    var index = 0;
                    var labelString = addLabels(dataModel.category);
                }

                Label {
                    text: ""
                    color: '#000000'
                    font.pixelSize: 24
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                id: recteinnahmen
                x: 500; y: 0; width: 400; height: 250
                color: '#00FF00'

                Label {
                    text: "Einnahmen"
                    color: '#000000'
                    font.pixelSize: 24
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                id: rectgesamt
                x: 920; y: 0; width: 500; height: 250
                color: '#808080'

                Label {
                    text: "Gesamt"
                    color: '#000000'
                    font.pixelSize: 24
                    anchors.centerIn: parent
                }
            }
        }
    }
    function addLabels(category) {
        for (var i = 0; i < dataModel.werte.length; ++i) {        
            if (dataModel.werte[i] < 0) {           
                var labelString = i + ". " + dataModel.category[i] + ": " + [dataModel.werte[i]]
                console.log("Erzeuge Label:", labelString[1])
            }
        }
        return labelString;
    }

    function roundToDecimalPlaces(value, decimalPlaces) {
        var factor = Math.pow(10, decimalPlaces);
        return Math.round(value * factor) / factor;
    }
}