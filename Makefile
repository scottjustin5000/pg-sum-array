EXTENSION = sum_array        # the extensions name
DATA = sum_array--0.0.1.sql  # script files to install
REGRESS = sum_array_test     # our test script file (without extension)
MODULES = sum_array

# postgres build stuff
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)