import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 6.7
import QtPositioning 6.7

Rectangle {
    width: 800
    height: 600
    color: "#f9f9f9"

    // Plugin OSM
    Plugin {
        id: osmPlugin
        name: "osm"
    }

    // Définition de la carte
    Map {
        id: myMap
        anchors.fill: parent
        plugin: osmPlugin
        center: QtPositioning.coordinate(36.8065, 10.1815) // Tunis
        zoomLevel: 13

        // Affichage des marqueurs
        MapItemView {
            model: markerModel // Modèle de marqueur défini dans C++
            delegate: MapQuickItem {
                id: markerItem
                coordinate: model.coordinate
                anchorPoint: Qt.point(image.width / 2, image.height)
                sourceItem: Image {
                    id: image
                    source: "qrc:/img/pngegg.png"
                    width: 32
                    height: 32
                }
            }

            Component.onCompleted: {
                console.log("Carte chargée, forçage du modèle...")
                markerModel.loadFromJson()
            }
        }

        // Gestion du mouvement de la carte avec la souris
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            property var lastMousePos

            onPressed: (mouse) => {
                lastMousePos = Qt.point(mouse.x, mouse.y)
            }

            onPositionChanged: (mouse) => {
                var dx = mouse.x - lastMousePos.x
                var dy = mouse.y - lastMousePos.y
                myMap.pan(-dx, -dy)
                lastMousePos = Qt.point(mouse.x, mouse.y)
            }
        }

        // Gestion du zoom avec la molette sedeplacer dans la carte
        WheelHandler {
            id: zoomHandler
            target: myMap
            property real step: 0.5

            onWheel: (event) => {
                myMap.zoomLevel += event.angleDelta.y > 0 ? step : -step
                event.accepted = true
            }
        }

        // Rechargement des marqueurs au démarrage
        Component.onCompleted: {
            markerModel.loadFromJson()
            console.log("🔁 loadFromJson() forcé côté QML.")
        }

        // Connexion avec mainWindow pour l'ajout de marqueurs via signal
        Connections {
            target: mainWindow
            function onPositionTrouvee(lat, lon) {
                if (!isNaN(lat) && !isNaN(lon)) {
                    let coord = QtPositioning.coordinate(lat, lon)
                    myMap.center = coord
                    myMap.zoomLevel = 16  // Zoom plus proche
                    markerModel.addMarker(coord)
                    console.log("📍 Carte centrée sur :", lat, lon)
                } else {
                    console.warn("❌ Coordonnées invalides reçues :", lat, lon)
                }
            }
        }


        // Champ de texte pour saisir une localisation
        TextField {
            id: locationInput
            placeholderText: "Entrez une localisation"
            width: parent.width * 0.8

            onEditingFinished: {
                mainWindow.searchLocation(locationInput.text)
            }
        }
    }
}
