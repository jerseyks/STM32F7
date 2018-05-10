all:
	mkdir -p Build
upload:
	JLinkExe -Device STM32F765II -speed 4000 -if SWD -autoconnect 1 -CommanderScript ./flash.jlink
clean:
	rm -rf Build