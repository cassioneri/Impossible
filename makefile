TITLE  = impossible
FILES  = impossible.tex 

PROG   = latex

CC     = gcc
CFLAGS = -O2 -I. -Wall -Wextra -pedantic

DEPS   = common.h
OBJ    = common.o impossible.o p.o s.o

all: pdf impossible p s

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

impossible: impossible.o common.o
	gcc -o $@ $^ $(CFLAGS) -lm

p: p.o common.o
	gcc -o $@ $^ $(CFLAGS) -lm

s: s.o common.o
	gcc -o $@ $^ $(CFLAGS) -lm

# Do not change this
INDEX  = 0

${TITLE}.dvi dvi: ${TITLE}.tex ${FILES}
	{ ${PROG} ${TITLE}.tex ; \
	  if ((${INDEX})) && [ -r ${TITLE}.idx ] ; then \
	    makeindex ${TITLE}.idx ; \
	    REMAKE=1 ; \
	  fi ; \
	  if (($${REMAKE})) ; then \
	    ${PROG} ${TITLE}.tex ; \
	  fi ; \
	}

${TITLE}.ps ps: ${TITLE}.dvi
	dvips -t a4 ${TITLE}.dvi -o

${TITLE}.pdf pdf: ${TITLE}.ps
	ps2pdf ${TITLE}.ps ${TITLE}.pdf

draft: ${TITLE}.dvi
	dvips -t a4 ${TITLE} -o
	pstops -pa4 "4:0L@.707(21cm,0)+1L@.707(21cm,14.85cm),2R@.707(0,29.7cm)+3R@.707(0,14.85cm)" ${TITLE}.ps ${TITLE}_tmp.ps
	mv ${TITLE}_tmp.ps ${TITLE}.ps

book: ${TITLE}.dvi
	dvips -t a4 ${TITLE} -o
	psbook ${TITLE}.ps | pstops -pa4 "4:0L@.707(21cm,0)+1L@.707(21cm,14.85cm),2R@.707(0,29.7cm)+3R@.707(0,14.85cm)" > ${TITLE}_tmp.ps
	mv ${TITLE}_tmp.ps ${TITLE}.ps

bbook: ${TITLE}.dvi
	dvips -t a4 ${TITLE} -o
	psbook -s32 ${TITLE}.ps | pstops -pa4 "4:0L@.707(21cm,0)+1L@.707(21cm,14.85cm),2R@.707(0,29.7cm)+3R@.707(0,14.85cm)" > ${TITLE}_tmp.ps
	mv ${TITLE}_tmp.ps ${TITLE}.ps

index:
	sed -e 's/^INDEX=0/INDEX=1/g' -i makefile
	touch ${TITLE}.tex

noindex:
	sed -e 's/^INDEX=1/INDEX=0/g' -i makefile

clean:
	rm -f ${TITLE}.aux ${TITLE}.bbl ${TITLE}.blg ${TITLE}.fot ${TITLE}.idx ${TITLE}.ilg ${TITLE}.ind ${TITLE}.log ${TITLE}.lof ${TITLE}.toc *.o

cleanall: clean
	rm -f ${TITLE}.dvi ${TITLE}.ps ${TITLE}.pdf impossible p s
