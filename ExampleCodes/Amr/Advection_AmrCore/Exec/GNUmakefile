
PRECISION  = DOUBLE
PROFILE    = FALSE

DEBUG      = TRUE
DEBUG      = FALSE

DIM        = 3
#DIM       = 3

COMP	   = gnu

USE_MPI    = TRUE
USE_OMP    = FALSE 
USE_CUDA   = FALSE

Bpack   := ./Make.package 
Blocs   := . 

USE_ASCENT = TRUE
ASCENT_DIR = $(shell spack location -i ascent)
# Include Ascent headers
CXXFLAGS += -I$(ASCENT_DIR)/include
# Link Ascent libraries
LDFLAGS  += -L$(ASCENT_DIR)/lib -lascent -lconduit


USE_CONDUIT = TRUE
# Locate Conduit installation
CONDUIT_DIR = $(shell spack location -i conduit)
# Include Conduit headers
CXXFLAGS += -I$(CONDUIT_DIR)/include
# Link Conduit libraries
LDFLAGS  += -L$(CONDUIT_DIR)/lib -lconduit -lconduit_relay -lconduit_blueprint


include Make.Adv
