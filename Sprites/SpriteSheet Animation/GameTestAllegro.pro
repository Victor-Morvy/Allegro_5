QT -= gui

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += "V:\Bibliotecas\jsonParserCpp\json\single_include"

INCLUDEPATH += "C:\Users\PICHAU\source\repos\ConsoleApplication1\packages\Allegro.5.2.6\build\native\include"
LIBS += -L"C:\Users\PICHAU\source\repos\ConsoleApplication1\packages\Allegro.5.2.6\build\native\v141\x64\lib"
LIBS += -lallegro -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_primitives -lallegro_acodec \
        -lallegro_audio -lallegro_color -lallegro_image -lallegro_main -lallegro_memfile -lallegro_video\
        -lallegro_monolith-static -lallegro_physfs
#LIBS += -L"C:\Users\PICHAU\source\repos\ConsoleApplication1\packages\Allegro.5.2.6\build\native\v142\x64\bin\allegro-5.2.dll"
