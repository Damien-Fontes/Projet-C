tar:
	$(MAKE) -C compression clean
	tar -zcf "$(CURDIR).tar.gz" compression/* arbre/* codage/* fichier/* makefile