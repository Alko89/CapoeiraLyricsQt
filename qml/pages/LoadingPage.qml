import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge

        VerticalScrollDecorator {}

        Column {
            id: column
            spacing: Theme.paddingLarge
            width: parent.width

            PageHeader { title: "Downloading lyrics..." }

            SectionHeader { text: "Progress bar" }
            ProgressBar {
                id: progressBar
                width: parent.width
                maximumValue: 1619
                valueText: value
                label: "Progress"
                Timer {
                    interval: 100
                    repeat: true
                    onTriggered: progressBar.value = (progressBar.value + 1) % 1619
                    running: Qt.application.active
                }
            }
        }
    }
}
