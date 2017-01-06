import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: songPage
    property alias songTitle: title.title
    property alias songSubtitle: subtitle.text
    property alias songText: lyrics.text
    property alias songTranslation: translations.text

    SilicaFlickable {
        anchors.fill: parent
        contentWidth: parent.width
        contentHeight: col.height + Theme.paddingLarge

        VerticalScrollDecorator {}

        Column {
            id: col
            x: Theme.horizontalPageMargin
            width: parent.width - 2*Theme.horizontalPageMargin
            height: childrenRect.height

            PageHeader {
                id: title
            }
            SectionHeader {
                id: subtitle
            }
            Label {
                id: lyrics
                wrapMode: Text.WordWrap
                anchors {
                    left: parent.left
                    right: parent.right
                }
            }
            Label {
                id: translations
                color: Theme.secondaryColor
                wrapMode: Text.WordWrap
                anchors {
                    left: parent.left
                    right: parent.right
                }
            }
        }
    }
}
