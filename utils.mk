format:
	find . -regex '.*\.\(cpp\|hpp\|c\|h\)' -exec clang-format -style=file -i {} \;

lines:
	cloc . --include-lang="C++","make","C/C++ Header" --exclude-dir=assets
