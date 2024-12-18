# Set the template type to app (for an application)
TEMPLATE = app

# The target output file name
TARGET = project

# Include the source and header files
SOURCES += main.cpp \
           MatrixCalculator.cpp

HEADERS += MatrixCalculator.h

# Use the Qt Widgets module
QT += widgets

