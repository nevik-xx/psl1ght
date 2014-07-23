PREFIX		:= ppu-

include $(PSL1GHT_INTERNAL)/rules/base.mk

FSELF		:= $(PSL1GHT)/bin/fself.py
SFO			:= $(PSL1GHT)/bin/sfo.py
PS3LOADAPP	:= $(PSL1GHT)/bin/ps3load
SFOXML		:= $(PSL1GHT)/bin/sfo.xml
ICON0		:= $(PSL1GHT)/bin/ICON0.PNG
PKG			:= $(PSL1GHT)/bin/pkg.py
SPRX		:= $(PSL1GHT)/bin/sprxlinker
VPCOMP		:= $(PSL1GHT)/bin/vpcomp

CFLAGS		:= -g \
			   -I$(PSL1GHT_INTERNAL)/include -I$(PS3DEV)/host/ppu/include
CXXFLAGS	:= $(CFLAGS)
LDFLAGS		:= -B$(PSL1GHT)/lib -B$(PS3DEV)/host/ppu/lib -llv2 -lpsl1ght

%.self: %.elf
	@$(STRIP) $< -o $(BUILDDIR)/$(notdir $<)
	@$(SPRX) $(BUILDDIR)/$(notdir $<)
	@$(FSELF) $(BUILDDIR)/$(notdir $<) $@

%.vcg.h: %.vcg
	@echo "[VPCOMP] $(notdir $<)"
	@$(VPCOMP) $< $(notdir $(BUILDDIR)/$(basename $<).rvp)
	@$(RAW2H)  $(BUILDDIR)/$(notdir $(basename $<).rvp) $(BUILDDIR)/$(notdir $<).h $(BUILDDIR)/$(notdir $<).S $(notdir $(basename $<)_bin)
	@$(AS) -x assembler-with-cpp $(ASFLAGS) -c $(BUILDDIR)/$(notdir $<).S -o $(BUILDDIR)/$(notdir $<).o


