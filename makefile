all:
	make -C build/csg
	mkdir -p build/src/articles build/dest/articles
	build/csg/bin/csg build/src build/dest
	cp -frv build/dest/articles/ .

