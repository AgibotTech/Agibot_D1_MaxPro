# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = source
BUILDDIR      = build

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

# Use cn as alias of Simplified Chinese
html-cn: html-zh_CN
	:

# language is in Locale style
# output html path is in Language Tag style
html-%:
	make -e 'HTML_OUTPUT_ALT=1' -e 'SPHINXOPTS=$(SPHINXOPTS) -D language="$*"' -e 'BUILDDIR=$(BUILDDIR)/html/$(shell echo $* |tr '_[:upper:]' '-[:lower:]')/dev' html

html-intl: html-en html-cn
	echo "build intl $^"

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
