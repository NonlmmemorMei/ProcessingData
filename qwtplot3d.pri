#-------------------------------------------------
#
# QwtPlot3D Library configuration file
#
#-------------------------------------------------

QWTPLOT3D_VER = 0.2.7
MINGW_VER = 4.6

unix {
    INCLUDEPATH += /usr/include/qwtplot3d-qt4
    LIBS    += -L/usr/lib -lqwtplot3d-qt4
    INCLUDEPATH += /usr/include/GL
    LIBS    += -L/usr/lib/i386-linux-gnu -lGLU
}

win32 {
    win32-x-g++ {
        QWTPLOT3D_PATH = /usr/qwtplot3d-win
        GLU_PATH = /usr/glu-win
    } else {
        QWTPLOT3D_PATH = C:/Qt/Qt$${QT_VERSION}/qwtplot3d-$${QWTPLOT3D_VER}
        GLU_PATH = C:/Qt/Qt5.3.2/5.3/mingw482_32/
        GLU_PATH = C:/Qt/Qt$${QT_VERSION}/$${QT_VERSION}/mingw-$${MINGW_VER}
       contains(MINGW_VER,^4\\.\\.(\\.\\d*)?) {
            GLU_PATH = $${GLU_PATH}/i686-w64-mingw32
        }
    }
    CONFIG(debug,debug|release) {
        DEBUG_SFX = d
    } else {
        DEBUG_SFX =
    }
    INCLUDEPATH += $${QWTPLOT3D_PATH}/include
    LIBS    += -L$${QWTPLOT3D_PATH}/lib -lqwtplot$${DEBUG_SFX}3d
    INCLUDEPATH += $${GLU_PATH}/include/GL
    LIBS    += -L$${GLU_PATH}/lib -lglu32
}
