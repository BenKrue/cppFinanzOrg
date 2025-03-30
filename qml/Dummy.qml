import QtQuick 2.15
import QtQuick.Controls 2.15
import QtCharts 2.15

Rectangle
{
    property alias dummyWidth: dummy.width
    property alias dummyHeight: dummy.height
    property alias dummyColor: dummy.color
    property alias dummyView: dummy.opacity
    property alias dummyPosX: dummy.x
    property alias dummyPosY: dummy.y

    Rectangle
    {
        id: dummy

    }
}