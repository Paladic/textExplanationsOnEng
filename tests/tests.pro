include(../textExplanationsOnEng/textExplanationsOnEng.pri)

QT = core \
    testlib \
    qml \
    xml

SOURCES += \
    main.cpp \
    test_expressiontonodes.cpp \
    test_getexplanation.cpp \
    test_getexplanationinen.cpp \
    test_iscustomtypewithfileds.cpp \
    test_isfunction.cpp \
    test_isidentifier.cpp \
    test_removeconsecutiveduplicates.cpp \
    test_toexplanation.cpp \
    test_isreducibleunaryselfinverse.cpp

HEADERS += \
    test_expressiontonodes.h \
    test_getexplanation.h \
    test_getexplanationinen.h \
    test_iscustomtypewithfileds.h \
    test_isfunction.h \
    test_isidentifier.h \
    test_removeconsecutiveduplicates.h \
    test_toexplanation.h \
    test_isreducibleunaryselfinverse.h

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS += -fprofile-arcs -ftest-coverage
