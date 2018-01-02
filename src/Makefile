TOPTARGETS := all any x86_64 armv7l clean

SUBDIRS-any := \
  test

SUBDIRS-x86_64 :=  \
  database

SUBDIRS-armv7l := \
  isr \
  play \
  send \
  log

SUBDIRS := \
  $(SUBDIRS-any) \
  $(SUBDIRS-x86_64) \
  $(SUBDIRS-armv7l)

.PHONY: all any x86_64 armv7l \
  $(SUBDIRS-any) $(SUBDIRS-x86_64) $(SUBDIRS-armv7l) \
  clean

any: $(SUBDIRS-any)

x86_64: $(SUBDIRS-x86_64)

armv7l: $(SUBDIRS-armv7l)

$(SUBDIRS):
	$(MAKE) -C $@

