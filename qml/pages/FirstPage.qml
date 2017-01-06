import QtQuick 2.0
import Sailfish.Silica 1.0

import capoeiralyrics 1.0

Page {
    id: page
    property string searchString

    onSearchStringChanged: songs.filter(searchString)
    Component.onCompleted: songs.filter(searchString)

    Loader {
        anchors.fill: parent
        sourceComponent: listViewComponent
    }

    Column {
        id: headerContainer

        width: page.width

        PageHeader {
            title: "Capoeira lyrics"
        }

        SearchField {
            id: searchField
            width: parent.width

            Binding {
                target: page
                property: "searchString"
                value: searchField.text.toLowerCase().trim()
            }
        }
    }

    Component {
        id: listViewComponent
        SilicaListView {
            model: songs

            anchors.fill: parent
            currentIndex: -1 // otherwise currentItem will steal focus
            header:  Item {
                id: header
                width: headerContainer.width
                height: headerContainer.height
                Component.onCompleted: headerContainer.parent = header
            }

            delegate: BackgroundItem {
                id: backgroundItem

                ListView.onAdd: AddAnimation {
                    target: backgroundItem
                }
                ListView.onRemove: RemoveAnimation {
                    target: backgroundItem
                }

                Label {
                    x: searchField.textLeftMargin
                    anchors.verticalCenter: parent.verticalCenter
                    color: searchString.length > 0 ? (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
                                                   : (highlighted ? Theme.highlightColor : Theme.primaryColor)
                    textFormat: Text.StyledText
                    text: Theme.highlightText(title, searchString, Theme.highlightColor)
                }

                onClicked: window.pageStack.push(Qt.resolvedUrl("SecondPage.qml"), {
                                                     songTitle: title,
                                                     songSubtitle: subtitle,
                                                     songText: text,
                                                     songTranslation: translations
                                                 })
            }

            VerticalScrollDecorator {}
        }
    }
    Songs {
        id: songs
    }
}
