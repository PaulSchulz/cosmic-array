targets:
	@echo "Targets:"
	@echo "  post    - Power-On Self Test"
	@echo "  start   - Start the cosmic array detector."
	@echo "  stop    - Stop the cosmic array detector."
	@echo "  mute    - Mute the audio output."
	@echo "  unmute  - Unmute the audio outoput."
	@echo "  bin     - Run on target architecture to compile binaries."
	@echo "  test    - Run test program, stimulates detector hardware."
	@echo "  version - Display software version."
	@echo "  upgrade - Get new version from GitHub."

post:
	@echo "post: To be implemented."

start:
	@echo "start: To be implemented."

stop:
	@echo "stop: To be implemented."

mute:
	@sudo amixer -c 0 set PCM mute

unmute:
	@sudo amixer -c 0 set PCM playback 70% unmute

bin: src
	$(MAKE) -C src

test:
	./bin/cosmic-array-sensor-test

version:
	@echo "os-release:" `cat /etc/os-release | grep PRETTY_NAME | sed s/PRETTY_NAME=// | sed s/\"//g`
	@echo "software:  " `git describe --tags --long`

upgrade:
	@git pull
