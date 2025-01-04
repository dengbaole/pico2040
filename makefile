

BUILD_DIR = build
PICO_DIR = ./pico

.PHONY: clean default pico rebuild assets

default: pico

assets:
	@echo Create Assets
	./utils_bin/p2a-win-amd64.exe -q 0 -c rgb565 -in ./assets/UI -out $(PICO_DIR)/assets

pico:
	cmake . -G Ninja -B$(BUILD_DIR) -S.
	ninja -C $(BUILD_DIR)

clean:
	@if [ -d "./$(BUILD_DIR)" ]; then rm ./$(BUILD_DIR) -r; fi

rebuild: clean pico

format:
	powershell ./format.ps1
