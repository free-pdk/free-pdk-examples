ifeq ($(DEVICE), PFS154)
	ARCH = pdk14
else ifeq ($(DEVICE), PFS172)
	ARCH = pdk14
else ifeq ($(DEVICE), PFS173)
	ARCH = pdk15
else ifeq ($(DEVICE), PMS150C)
	ARCH = pdk13
else ifeq ($(DEVICE), PMS15A)
	ARCH = pdk13
else ifeq ($(DEVICE), PMS152)
	ARCH = pdk14
else ifeq ($(DEVICE), PMS154C)
	ARCH = pdk14
else ifeq ($(DEVICE), PMS171B)
	ARCH = pdk14
endif
