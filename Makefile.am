# Automake options: Set the mode to "foreign" to relax strict GNU standards
AUTOMAKE_OPTIONS = foreign

# Main program configuration
bin_PROGRAMS = trigonometry
trigonometry_SOURCES = main.cpp MyTrigFunction.cpp MyTrigFunction.h

# Test programs configuration
# "check_PROGRAMS" lists the test binaries to build for `make check`
check_PROGRAMS = test_funcA
test_funcA_SOURCES = tests/test_funcA.cpp MyTrigFunction.cpp MyTrigFunction.h

# Declare additional test programs in TESTS for `make check`
TESTS = test_funcA

# Data files to include in the distribution
# "nobase" preserves directory structure in the distribution
nobase_dist_pkgdata_DATA = data/data.txt

# Install additional metadata for Debian packaging
dist_pkgdata_DATA = README.md
