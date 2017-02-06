QT += qml quick
CONFIG += c++11

INCLUDEPATH += 3rdparty/libnoise
INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/main.cpp

HEADERS += \
    $$PWD/3rdparty/libnoise/libnoise/noisegen.h \
    $$PWD/3rdparty/libnoise/libnoise/exception.h \
    $$PWD/3rdparty/libnoise/libnoise/basictypes.h \
    $$PWD/3rdparty/libnoise/libnoise/interp.h \
    $$PWD/3rdparty/libnoise/libnoise/vectortable.h \
    $$PWD/3rdparty/libnoise/libnoise/module/modulebase.h \
    $$PWD/3rdparty/libnoise/libnoise/module/perlin.h

SOURCES += \
    $$PWD/3rdparty/libnoise/libnoise/noisegen.cpp \
    $$PWD/3rdparty/libnoise/libnoise/module/modulebase.cpp \
    $$PWD/3rdparty/libnoise/libnoise/module/perlin.cpp

RESOURCES += \
    $$PWD/qml.qrc \

OTHER_FILES += \
    *.qml
