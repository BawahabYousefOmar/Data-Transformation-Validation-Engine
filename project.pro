QT += core gui widgets

CONFIG += c++17

TARGET = DataEngine
TEMPLATE = app

SOURCES += \
    BatchNameDialog.cpp \
    HeaderMappingDialog.cpp \
    HeaderProcessor.cpp \
    LoginWindow.cpp \
    main.cpp \
    MainWindow.cpp \
    NoteDialog.cpp \
    RecordParser.cpp \
    ReportsTableWidget.cpp \
    RuleLoader.cpp \
    UploadWidget.cpp \
    Validator.cpp

HEADERS += \
    BatchNameDialog.h \
    DynamicArray.h \
    HashMap.h \
    HashSet.h \
    HeaderMappingDialog.h \
    HeaderProcessor.h \
    LoginWindow.h \
    MainWindow.h \
    NoteDialog.h \
    Record.h \
    RecordParser.h \
    ReportsTableWidget.h \
    Rule.h \
    RuleLoader.h \
    Stack.h \
    UploadWidget.h \
    Validator.h

FORMS += \
    BatchNameDialog.ui \
    HeaderMappingDialog.ui \
    LoginWindow.ui \
    MainWindow.ui \
    NoteDialog.ui \
    ReportsTableWidget.ui \
    UploadWidget.ui
