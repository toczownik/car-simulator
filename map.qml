import QtQuick 2.0
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Window 2.12

Window {
    height: 600
    width: 600
    visible: true
    title: qsTr("GPS SCREEN")

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75)
        zoomLevel: 20
        MapCircle {
            color: "red"
            center: QtPositioning.coordinate(59.91, 10.75)
            radius: 10
        }
    }
}
