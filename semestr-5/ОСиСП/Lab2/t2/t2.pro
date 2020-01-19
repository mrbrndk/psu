TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c

QMAKE_CFLAGS += -lpthread -g -Wall -Werror -std=gnu99
QMAKE_LFLAGS += -pthread
