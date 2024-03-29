RCC_DIR = ../../build
OBJECTS_DIR = ../../build
MOC_DIR = ../../build
UI_DIR = ../../build

CONFIG -= debug_and_release

contains(TEMPLATE,lib){
    contains(CONFIG,plugin){
        unix:DESTDIR=../../bin/plugins/
        win32{
            DLLDESTDIR = ../../bin/plugins/
            DESTDIR = ../../lib
        }
    }
}else{
    DESTDIR = ../../bin
}

INCLUDEPATH += \
    ../../include

MY_LIBDIR = ../../lib
