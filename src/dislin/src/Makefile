#
#  Some special rules to built the SDL files properly
#

include $(SACBASE)/stdlib/Makefiles/Makefile.Config

ifneq ($(ENABLE_DISLIN),yes)
  EXCLUDE_FILES := page.c header.c $(EXCLUDE_FILES) 
endif

include $(SACBASE)/stdlib/Makefiles/Makefile_template.stdlib


