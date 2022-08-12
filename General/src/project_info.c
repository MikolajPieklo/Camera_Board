#include <project_info.h>
#include <project_info_cfg.h>

/**
 * Project Name
 *
 * Description: information about project name
 * Format     : String
 * Example    : "Camera Board"
 */
const uint8_t project_name[] = INFO_PROJECT_NAME;

/**
 * USER name
 *
 * Description: if not RCM build then the name from windows
 *              environment variable USERNAME shall be used
 * Format     : String
 * Example    : "mkpk"
 */
const uint8_t user_name[] = INFO_USER_NAME;

/**
 * Build Time
 *
 * Description: information about build time in format HH:MM:SS
 * Format     : String
 * Example    : "15:23:16"
 */
const uint8_t build_time[] = INFO_BUILD_TIME;

/**
 * Build Date
 *
 * Description: information about build date in format YYYYMMDD
 * Format     : String
 * Example    : "20121126"
 */
const uint8_t build_date[] = INFO_BUILD_DATE;

/**
 * RCM Build ID
 *
 * Description: ID of the build from RCM system
 * Format     : String
 * Example    : "127"
 */
const uint8_t build_id[] = INFO_BUILD_ID;

/**
 * RCM Version Name
 *
 * Description: Version Name from RCM system
 * Format     : String
 * Example    : "LSR_20160101"
 */
const uint8_t variant_name[] = INFO_VARIANT_NAME;

/**
 * Board Name
 *
 * Description: Board Name
 * Format     : String
 * Example    : cb_base
 */
const uint8_t board_name[] = INFO_BOARD_NAME;

/**
 * Board Revision
 *
 * Description: Board Revision
 * Format     : Integer
 * Example    : 0
 */
const uint16_t board_revision = INFO_BOARD_REV;

const uint8_t separator[] = "==================================================";

/**
 *  Returns the pointer to Project Name.
 */
const uint8_t* Get_Project_Name(void)
{
   return (project_name);
}

/**
 *  Returns the pointer to User Name.
 */
const uint8_t* Get_User_Name(void)
{
   return (user_name);
}

/**
 *  Returns the pointer to Build time.
 */
const uint8_t* Get_Build_Time(void)
{
   return (build_time);
}

/**
 *  Returns the pointer to Build date.
 */
const uint8_t* Get_Build_Date(void)
{
   return (build_date);
}

/**
 *  Returns the RCM Build ID.
 */
const uint8_t* Get_Version_Name(void)
{
   return (build_id);
}

/**
 *  Returns Variant Name.
 */
const uint8_t* Get_Variant_Name(void)
{
   return (variant_name);
}

/**
 *  Returns Board Name.
 */
const uint8_t* Get_Board_Name(void)
{
   return (board_name);
}

/**
 *  Returns Board Revision.
 */
uint16_t Get_Board_Revision(void)
{
   return (board_revision);
}

const uint8_t* Get_Separator(void)
{
   return (separator);
}
