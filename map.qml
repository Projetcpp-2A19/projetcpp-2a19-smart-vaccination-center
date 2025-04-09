import QtQuick 2.15
import QtLocation 6.7
import QtPositioning 6.7


Rectangle {
    width: 800
    height: 600

    // Plugin pour OpenStreetMap
    Plugin {
        id: osmPlugin
        name: "osm"  // Utilise le plugin OpenStreetMap
    }

    Map {
        id: myMap
        anchors.fill: parent
        plugin: osmPlugin
        center: QtPositioning.coordinate(36.8065, 10.1815) // Position initiale
        zoomLevel: 14

        // Repeater pour afficher les marqueurs
        MapItemView {
                    model: markerModel
                    delegate: MapQuickItem {
                        id: markerItem
                        coordinate: model.coordinate // Utilise "coordinate" au lieu de "map"
                        anchorPoint: Qt.point(icon.width / 2, icon.height)
                        sourceItem: Image {
                            id: icon
                            source: "qrc:/img/pngegg.png"
                            width: 32
                            height: 32
                        }
                    }
        }


        // Zoom avec la molette de la souris
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.AllButtons

            onWheel: function(event) {
                if (event.angleDelta.y > 0) {
                    myMap.zoomLevel += 1;
                } else {
                    myMap.zoomLevel -= 1;
                }
            }
        }

        // Déplacement de la carte avec la souris
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            property var lastCenter: myMap.center
            property var lastMousePos: Qt.point(0, 0)
            property real speedFactor: 0.3

            onPressed: (mouse) => {
                lastCenter = myMap.center;
                lastMousePos = Qt.point(mouse.x, mouse.y);
            }

            onPositionChanged: (mouse) => {
                var deltaX = lastMousePos.x - mouse.x;
                var deltaY = lastMousePos.y - mouse.y;

                var metersPerPixel = 156543.03 * Math.cos(myMap.center.latitude * Math.PI / 180) / Math.pow(2, myMap.zoomLevel);
                var deltaLat = (deltaY * metersPerPixel / 111320) * speedFactor;
                var deltaLon = (deltaX * metersPerPixel / (111320 * Math.cos(myMap.center.latitude * Math.PI / 180))) * speedFactor;

                myMap.center.latitude = lastCenter.latitude + deltaLat;
                myMap.center.longitude = lastCenter.longitude + deltaLon;
            }
        }
    }

    // Timer pour vérifier le nombre de marqueurs
    Timer {
        interval: 2000
        running: true
        repeat: false
        onTriggered: {
            console.log("📢 Nombre total de marqueurs dans markerModel:", markerModel.rowCount());
            for (var i = 0; i < markerModel.rowCount(); i++) {
                var marker = markerModel.data(markerModel.index(i, 0), markerModel.CoordinateRole);
                if (marker) {
                    console.log("📍 Marqueur", i, "-> Latitude:", marker.latitude, "Longitude:", marker.longitude);
                } else {
                    console.log("📍 Aucun marqueur trouvé à l'index", i);
                }
            }
        }
    }

    // Connexion au signal C++ pour ajouter un marqueur
    Connections {
        target: mainWindow
        function onAjouterLaboratoireEPINGLE(lat, lon) {
            console.log("✅ Signal reçu pour ajouter un laboratoire épinglé");
            console.log("📍 Latitude :", lat, ", Longitude :", lon);

            // Vérification des coordonnées avant ajout
            if (!isNaN(lat) && !isNaN(lon) && lat !== 0 && lon !== 0) {
                var exists = false;
                // Vérifie si le marqueur existe déjà
                for (var i = 0; i < markerModel.rowCount(); i++) {
                    var marker = markerModel.data(markerModel.index(i, 0), markerModel.CoordinateRole);
                    if (marker && marker.latitude === lat && marker.longitude === lon) {
                        exists = true;
                        break;
                    }
                }

                if (!exists) {
                    // Ajoute le marqueur au modèle
                    markerModel.addMarker(QtPositioning.coordinate(lat, lon));
                    console.log("📍 Marqueur ajouté — Latitude :", lat, ", Longitude :", lon);
                } else {
                    console.log("📍 Ce marqueur existe déjà — Latitude :", lat, ", Longitude :", lon);
                }
            } else {
                console.warn("⚠️ Coordonnées invalides reçues : ", lat, lon);
            }
        }
    }
}
