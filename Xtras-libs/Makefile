all: Xtra-libs

Xtra-libs:
	sh Install-Xtras.sh
	

clean:
	rm -rf Tiny3d 
	rm -rf ps3soundlib

install: all
	mkdir -p /usr/local/ps3dev/portlibs/ppu/modules
	cp -rv ps3soundlib/libs/spu_soundmodule/lib/spu_soundmodule.bin.h ps3soundlib/libs/spu_soundmodule/spu_soundmodule.bin.a ps3soundlib/libs/spu_soundmodule/spu_soundmodule.elf /usr/local/ps3dev/portlibs/ppu/modules/ 
	cp -rv ps3soundlib/libs/spu_soundlib/spu_soundlib.h /usr/local/ps3dev/portlibs/ppu/include/ 
	cp -rv ps3soundlib/libs/libmodplay/gcmodplay.h ps3soundlib/libs/audioplayerlib/audioplayer.h /usr/local/ps3dev/portlibs/ppu/include/ 
	cp -frv ps3soundlib/libs/libmodplay/modplay.h /usr/local/ps3dev/portlibs/ppu/include/ 
	cp -frv ps3soundlib/libs/audioplayerlib/libaudioplayer.a ps3soundlib/libs/audioplayerlib/liboggplayer.a ps3soundlib/libs/libmodplay/libmod.a ps3soundlib/libs/spu_soundlib/libspu_sound.a /usr/local/ps3dev/portlibs/ppu/lib/