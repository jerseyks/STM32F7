all:
	mkdir -p Build
# Front line command causes the changes in the environment on the next line will be reset, so the command line to start a sub shell, so, so write
# cd /tmp && you-operation-cmds
	cd Build && cmake ..
	cd Build && make -j
	cd Build && cmake ..
upload:
	JLinkExe -Device STM32F765II -speed 4000 -if SWD -autoconnect 1 -CommanderScript ./flash.jlink
clean:
	rm -rf Build