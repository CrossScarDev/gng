ASSETS_DIR = ../assets

assets:
	xxd -i -a $(ASSETS_DIR)/background.png > $(ASSETS_DIR)/background.h
	xxd -i -a $(ASSETS_DIR)/logo.png > $(ASSETS_DIR)/logo.h
	xxd -i -a $(ASSETS_DIR)/toon-around.ttf > $(ASSETS_DIR)/toon-around.h

clean-assets:
	@rm -fr $(ASSETS_DIR)/*.h