#-------------------------------------------------
#
# Project created by QtCreator 2014-04-14T13:01:15
#
#-------------------------------------------------

QT       += core gui

TARGET = test7
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    circuit/circuit.cpp \
    circuit/device/VSRC_DEVICE.cpp \
    circuit/device/RES_DEVICE.cpp \
    circuit/device/MOS_DEVICE.cpp \
    circuit/device/ISRC_DEVICE.cpp \
    circuit/device/IND_DEVICE.cpp \
    circuit/device/DIODE_DEVICE.cpp \
    circuit/device/CONT_VC_DEVICE.cpp \
    circuit/device/CONT_CC_DEVICE.cpp \
    circuit/device/CAP_DEVICE.cpp \
    circuit/device/model/model_vsrc.cpp \
    circuit/device/model/model_vcvs.cpp \
    circuit/device/model/model_vccs.cpp \
    circuit/device/model/model_res_linear.cpp \
    circuit/device/model/model_pmos.cpp \
    circuit/device/model/model_nmos.cpp \
    circuit/device/model/model_isrc.cpp \
    circuit/device/model/model_ind.cpp \
    circuit/device/model/model_diode.cpp \
    circuit/device/model/model_ccvs.cpp \
    circuit/device/model/model_cccs.cpp \
    circuit/device/model/model_cap.cpp \
    circuit/device/model/default_model.cpp \
    SpScanner.cpp \
    SpParser.cpp \
    MyClass.cpp \
    Qwtpic.cpp \
    plot.cpp

HEADERS  += mainwindow.h \
    circuit/mySolver.h \
    circuit/circuit.h \
    circuit/device/VSRC_DEVICE.h \
    circuit/device/RES_DEVICE.h \
    circuit/device/MOS_DEVICE.h \
    circuit/device/ISRC_DEVICE.h \
    circuit/device/IND_DEVICE.h \
    circuit/device/DIODE_DEVICE.h \
    circuit/device/CONT_VC_DEVICE.h \
    circuit/device/CONT_CC_DEVICE.h \
    circuit/device/CAP_DEVICE.h \
    circuit/device/model/model_vsrc.h \
    circuit/device/model/model_vcvs.h \
    circuit/device/model/model_vccs.h \
    circuit/device/model/model_res_linear.h \
    circuit/device/model/model_pmos.h \
    circuit/device/model/model_nmos.h \
    circuit/device/model/model_isrc.h \
    circuit/device/model/model_ind.h \
    circuit/device/model/model_diode.h \
    circuit/device/model/model_ccvs.h \
    circuit/device/model/model_cccs.h \
    circuit/device/model/model_cap.h \
    circuit/device/model/default_model.h \
    circuit/device/model/element/element_vsrc.h \
    circuit/device/model/element/element_vcvs.h \
    circuit/device/model/element/element_vccs.h \
    circuit/device/model/element/element_res.h \
    circuit/device/model/element/element_pmos.h \
    circuit/device/model/element/element_nmos.h \
    circuit/device/model/element/element_isrc.h \
    circuit/device/model/element/element_ind.h \
    circuit/device/model/element/element_diode.h \
    circuit/device/model/element/element_ccvs.h \
    circuit/device/model/element/element_cccs.h \
    circuit/device/model/element/element_cap.h \
    circuit/device/model/element/element.h \
    stack.hh \
    SpParser.ll \
    SpParser.hpp \
    position.hh \
    MyClass.h \
    location.hh \
    Qwtpic.h \
    plot.h \
    pixmaps.h \
    complexnumber.h

OTHER_FILES += \
    SpParser.yy \
    sdi.pro.user \
    sdi.pro \
    ../qwt-6.1.0/qwtfunctions.pri \
    ../qwt-6.1.0/qwtconfig.pri \
    ../qwt-6.1.0/qwtbuild.pri

RESOURCES += \
    sdi.qrc \
    sdi.qrc

DEFINES    += QT_DLL QWT_DLL

CONFIG(debug,debug|release):LIBS += -L"/home/taesunp/Desktop/qwt-6.1.0/lib/" -lqwtd

          else:LIBS += -L"/home/taesunp/Desktop/qwt-6.1.0/lib/" -lqwt

INCLUDEPATH+= /home/taesunp/Desktop/qwt-6.1.0/src

