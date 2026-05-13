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
    ReportDetailsWindow.cpp \
    ReportsTableWidget.cpp \
    RuleEditorDialog.cpp \
    RuleLoader.cpp \
    StandardsManagerWidget.cpp \
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
    ReportDetailsWindow.h \
    ReportsTableWidget.h \
    Rule.h \
    RuleEditorDialog.h \
    RuleLoader.h \
    Stack.h \
    StandardsManagerWidget.h \
    UploadWidget.h \
    Validator.h

FORMS += \
    BatchNameDialog.ui \
    HeaderMappingDialog.ui \
    LoginWindow.ui \
    MainWindow.ui \
    NoteDialog.ui \
    ReportDetailsWindow.ui \
    ReportsTableWidget.ui \
    RuleEditorDialog.ui \
    StandardsManagerWidget.ui \
    UploadWidget.ui
