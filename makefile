SHELL=/bin/bash
EXENAME=analog
CPPFLAGS=-Wall -Wextra -pedantic -std=c++11
FLAGS=
SRCDIR=src
BINDIR=bin

main: main.o Parser.o #Graph.o Node.o 
	@echo -e "\033[33mCompilation de main\033[0m"
	cd ${BINDIR} && \
	g++ ${CPPFLAGS} ${FLAGS} \
		*.o \
        -o ${EXENAME} \
	&& chmod +x ${EXENAME}

%.o: ${SRCDIR}/%.cpp
	@echo -e "\033[33mCompilation de $@\033[0m"
	if [[ ! -d ${BINDIR} ]]; then mkdir ${BINDIR}; fi
	g++ ${CPPFLAGS} ${FLAGS} -c $< -o ${BINDIR}/$@

clean:
	@if [[ -d ${BINDIR} ]]; then \
		echo -e "\033[33mNettoyage du répertoire de travail\033[0m"; \
		rm -rf ${BINDIR}; \
		echo -e "\033[33mRépertoire de travail nettoyé :)\033[0m"; \
	else \
		echo -e "\033[33mRépertoire de travail inexistant\033[0m"; \
	fi;

help:
	@echo -e "\033[36mRègles make disponibles :\033[0m\n"
	@echo -e "\033[33mmain :\033[0m"
	@echo -e "\tcompile tous les fichiers sources et crée l'exécutable final"
	@echo -e "\tle résultat des compilations est placé dans le sous-répertoire \033[01m${BINDIR}\033[0m\n"
	@echo -e "\033[33m<file>.o :\033[0m"
	@echo -e "\tcompile le fichier source <file>.cpp et crée le fichier objet <file>.o associé"
	@echo -e "\tle fichier source doit se trouver dans le sous-répertoire \033[01m${SRCDIR}\033[0m"
	@echo -e "\tle résultat de la compilation est placé dans le sous-répertoire \033[01m${BINDIR}\033[0m\n"
	@echo -e "\033[33mclean :\033[0m"
	@echo -e "\tsupprime le répertoire \033[01m${BINDIR}\033[0m et tout son contenu\n"
	@echo -e "\033[33mhelp :\033[0m"
	@echo -e "\taffiche ce message d'aide\n"

main.o: ${SRCDIR}/Parser.h #${SRCDIR}/Graph.h ${SRCDIR}/Node.h 
#Catalogue.o: ${SRCDIR}/ListeTrajets.h ${SRCDIR}/Trajet.h
#TrajetCompose.o: ${SRCDIR}/Trajet.h
#TrajetSimple.o: ${SRCDIR}/Trajet.h
