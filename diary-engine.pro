TEMPLATE = subdirs

SUBDIRS += \
   src \
   test \
    diary-cli

test.depends = src
