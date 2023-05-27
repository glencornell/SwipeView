TEMPLATE = subdirs

SUBDIRS =
SUBDIRS += composite-test
SUBDIRS += demo
SUBDIRS += qswipeviewplugin
SUBDIRS += swipeview-test
SUBDIRS += vertical-test

linux {
    SUBDIRS += xdg-app-launcher
}
