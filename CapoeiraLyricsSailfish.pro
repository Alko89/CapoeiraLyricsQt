# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = CapoeiraLyricsSailfish

CONFIG += sailfishapp

SOURCES += src/CapoeiraLyricsSailfish.cpp \
    src/csongs.cpp \
    src/csong.cpp

OTHER_FILES += qml/CapoeiraLyricsSailfish.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/CapoeiraLyricsSailfish.changes.in \
    rpm/CapoeiraLyricsSailfish.spec \
    rpm/CapoeiraLyricsSailfish.yaml \
    translations/*.ts \
    CapoeiraLyricsSailfish.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

HEADERS += \
    src/csongs.h \
    src/csong.h
