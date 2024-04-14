all:
	make -C linux
	# make -C windows
	make -C wiiu
	make -C macos
	make -C switch
	make -C web
	make -C android

clean:
	make -C linux clean
	make -C windows clean
	make -C wiiu clean
	make -C macos clean
	make -C switch clean
	make -C web clean
	make -C android clean

include ./utils.mk
