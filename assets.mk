ASSETS_DIR = ../assets

assets:
	@echo Generating Assets...
	@echo
	@xxd -i -a $(ASSETS_DIR)/background.png > $(ASSETS_DIR)/background.h
	@xxd -i -a $(ASSETS_DIR)/logo.png > $(ASSETS_DIR)/logo.h
	@xxd -i -a $(ASSETS_DIR)/toon-around.ttf > $(ASSETS_DIR)/toon-around.h
	@xxd -i -a $(ASSETS_DIR)/dpad.png > $(ASSETS_DIR)/dpad.h
	@xxd -i -a $(ASSETS_DIR)/drag.png > $(ASSETS_DIR)/drag.h

clean-assets:
	@rm -rf $(ASSETS_DIR)/*.h
