/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

import capoeiralyrics 1.0

Page {
    id: page
    property string searchString
    //property bool keepSearchFieldFocus

    onSearchStringChanged: listModel.update()
    Component.onCompleted: listModel.update()

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
            model: listModel
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
                    text: Theme.highlightText(model.text, searchString, Theme.highlightColor)
                }

                onClicked: window.pageStack.push(Qt.resolvedUrl("SecondPage.qml"), {
                                                     songTitle: song.getTitle(model.index),
                                                     songSubtitle: song.getSubtitle(model.index),
                                                     songText: song.getText(model.index)
                                                 })
            }

            VerticalScrollDecorator {}

            /*Component.onCompleted: {
                if (keepSearchFieldFocus) {
                    searchField.forceActiveFocus()
                }
                keepSearchFieldFocus = false
            }*/
        }
    }

    Songs {
        id: song
    }

    ListModel {
        id: listModel

        property var countries: []
        Component.onCompleted: {
            for (var i = 0; i < song.getSize(); i++)
                countries.push([song.getTitle(i)] + "_" + i);
        }


        function update() {
            var filteredCountries = countries.filter(function (country) { return country.toLowerCase().indexOf(searchString) !== -1 })

            var country
            var found
            var i

            // helper objects that can be quickly accessed
            var filteredCountryObject = new Object
            for (i = 0; i < filteredCountries.length; ++i) {
                filteredCountryObject[filteredCountries[i]] = true
            }
            var existingCountryObject = new Object
            for (i = 0; i < count; ++i) {
                country = get(i).text
                existingCountryObject[country] = true
            }

            // remove items no longer in filtered set
            i = 0
            while (i < count) {
                country = get(i).text
                found = filteredCountryObject.hasOwnProperty(country)
                if (!found) {
                    remove(i)
                } else {
                    i++
                }
            }

            // add new items
            for (i = 0; i < filteredCountries.length; ++i) {
                country = filteredCountries[i]
                found = existingCountryObject.hasOwnProperty(country)
                if (!found) {
                    // for simplicity, just adding to end instead of corresponding position in original list
                    var c = country.split("_");
                    append({ "text": c[0], "index": c[1]})
                }
            }
        }
    }

}
