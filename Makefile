targets:
	@echo "Targets:"
	@echo "  bin     - Run on target architecture to compile binaries."
	@echo "  test    - Run test program, stimulates detector hardware."
	@echo "  version - Display software version."
	@echo "  upgrade - Get new version from GitHub."

bin: src
	$(MAKE) -C src

test:
	./bin/cosmic-array-sensor-test

version:
	@echo "os-release:" `cat /etc/os-release | grep PRETTY_NAME | sed s/PRETTY_NAME=// | sed s/\"//g`
	@echo "software:  " `git describe --tags --long`

upgrade:
	@git pull
