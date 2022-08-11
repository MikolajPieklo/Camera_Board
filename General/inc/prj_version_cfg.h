#ifndef GENERAL_INC_PRJ_VERSION_CFG_H
#define GENERAL_INC_PRJ_VERSION_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_PROJECT_NAME        "TEST"

#define DEFAULT_USER_NAME           "none"

#define DEFAULT_BUILD_DATE_YYYY     "0000"  /* Year  (YY)  */
#define DEFAULT_BUILD_DATE_MM       "00"    /* Month (MM)  */
#define DEFAULT_BUILD_DATE_DD       "00"    /* Day   (DD)  */

#define DEFAULT_BUILD_DATE    \
      DEFAULT_BUILD_DATE_YYYY \
      DEFAULT_BUILD_DATE_MM   \
      DEFAULT_BUILD_DATE_DD   \
/* do not remove this line / end of version string */

#define DEFAULT_BUILD_ID            "0"

#define DEFAULT_BUILD_TIME          "00:00:00"

#define DEFAULT_VERSION_NAME        "none"
#define DEFAULT_JOB_NAME            "none"
#define DEFAULT_VARIANT_NAME        "none"
#define DEFAULT_BOARD_REV           0
#define DEFAULT_BOARD_NAME          "none"
/**
 * Project Name
 *
 * Description: information about project name
 * Format     : String
 * Example    : "Test"
 */
#ifdef PROJECT_NAME
#define INFO_PROJECT_NAME   { PROJECT_NAME }
#else
#define INFO_PROJECT_NAME   { DEFAULT_PROJECT_NAME }
#endif

/**
 * USER name
 *
 * Description: information about build user
 * Format     : String
 * Example    : "jzf80q"
 */
#ifdef USER_NAME
#define INFO_USER_NAME    { USER_NAME }
#else
#define INFO_USER_NAME    { DEFAULT_USER_NAME }
#endif

/**
 * Build Time
 *
 * Description: information about build time in format HH:MM:SS
 * Format     : String
 * Example    : "15:23:16"
 */
#ifdef BUILD_TIME
#define INFO_BUILD_TIME     { BUILD_TIME }
#else
#define INFO_BUILD_TIME     { DEFAULT_BUILD_TIME }
#endif

/**
 * Build Date
 *
 * Description: information about build date in format YYYYMMDD
 * Format     : String
 * Example    : "20210817"
 */
#ifdef BUILD_DATE
#define INFO_BUILD_DATE     { BUILD_DATE }
#else
#define INFO_BUILD_DATE     { DEFAULT_BUILD_DATE }
#endif

#ifdef BUILD_ID
#define INFO_BUILD_ID     { BUILD_ID }
#else
#define INFO_BUILD_ID     { DEFAULT_BUILD_ID }
#endif

/**
 * Variant Name
 *
 * Description: build variant name
 * Format     : String
 * Example    : test_max
 */
#ifdef VARIANT_NAME
#define INFO_VARIANT_NAME    { VARIANT_NAME }
#else
#define INFO_VARIANT_NAME    { DEFAULT_VARIANT_NAME }
#endif

/**
 * Board Name
 *
 * Description: information about board name
 * Format     : String
 * Example    : plcx
 */
#ifdef BOARD_NAME
#define INFO_BOARD_NAME    { BOARD_NAME }
#else
#define INFO_BOARD_NAME    { DEFAULT_BOARD_NAME }
#endif

/**
 * Board Revision
 *
 * Description: information about board name revision
 * Format     : Integer
 * Example    : 0
 */
#ifdef BOARD_REV
#define INFO_BOARD_REV    { BOARD_REV }
#else
#define INFO_BOARD_REV    { DEFAULT_BOARD_REV }
#endif

/*===========================================================================*/
#endif /* GENERAL_INC_PRJ_VERSION_CFG_H */
