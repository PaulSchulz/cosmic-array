.PHONY: targets bin test

targets:
	@echo "Targets:"
	@echo "  bin - Run on target architecture to compile binaries."
	@echo "  test - Run test program, stimulates detector hardware."

bin: src
	$(MAKE) -C src

test:
	./bin/cosmic-array-sensor-test
