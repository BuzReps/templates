BUILD_PRESET := debug
TARGET_NAME := MyTarget

BUILD_DIR := ./build_$(BUILD_PRESET)
INSTALL_DIR := ./install_$(BUILD_PRESET)
TARGET_PATH := $(INSTALL_DIR)/bin/$(TARGET_NAME)

configure:
	cmake --preset $(BUILD_PRESET)
	rm -f compile_commands.json
	ln -s -r $(BUILD_DIR)/compile_commands.json .

build: configure
	cmake --build $(BUILD_DIR) && cmake --install $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(INSTALL_DIR)

rerun:
	$(TARGET_PATH)

run: build rerun

redebug:
	seergdb $(TARGET_PATH)

debug: build redebug

.PHONY: configure build clean rerun run redebug debug

