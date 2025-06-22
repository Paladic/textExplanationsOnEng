TEMPLATE = subdirs

SUBDIRS += \
    tests \
    textExplanationsOnEng

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32 {
    WDEPLOY = "C:/Qt/6.7.2/mingw_64/bin/windeployqt.exe"

    # Путь к exe файлу в build директории
    EXECUTABLE_PATH = $$shell_path($$OUT_PWD/$$TARGET.exe)

    # Добавим post-build команду
    QMAKE_POST_LINK += $$quote($$WDEPLOY $$EXECUTABLE_PATH) $$escape_expand(\n\t)
}
