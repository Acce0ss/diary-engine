TEMPLATE = subdirs

SUBDIRS += \
   src \
   laskenta \
   test

laskenta.depends = src
test.depends = src
