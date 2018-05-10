all:
	mkdir -p Build
# 前一行命令导致环境的变化在下一行会被reset,所以,一行命令启动一个sub shell ,所以,这么写cd /tmp && you-operation-cmds
	cd Build && cmake ..
	cd Build && make -j
	cd Build && cmake ..
upload:
	JLinkExe -Device STM32F765II -speed 4000 -if SWD -autoconnect 1 -CommanderScript ./flash.jlink
clean:
	rm -rf Build