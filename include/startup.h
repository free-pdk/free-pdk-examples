// The name of the function that sdcc uses for startup changed.
// This macro assigns the correct name to STARTUP_FUNCTION based on the sdcc version.
#if __SDCC_REVISION >= 13762
#define STARTUP_FUNCTION __sdcc_external_startup
#else
#define STARTUP_FUNCTION _sdcc_external_startup
#endif
