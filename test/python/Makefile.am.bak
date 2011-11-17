## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src 

python_foobardocdir = ${prefix}/doc/python_foobar
python_foobardoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(python_foobardoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(python_foobardocdir)
