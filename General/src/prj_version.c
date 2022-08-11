
#include "prj_version.h"
#include "prj_version_cfg.h"

/**
 * Project Name
 *
 * Description: information about project name
 * Format     : String
 * Example    : "MIB_STD" or "MIB_HS"
 */
const uint8_t ver_project_name[] = INFO_PROJECT_NAME;

/**
 * USER name
 *
 * Description: if not RCM build then the name from windows
 *              environment variable USERNAME shall be used
 * Format     : String
 * Example    : "jzf80q"
 */
const uint8_t ver_user_name[] = INFO_USER_NAME;

/**
 * Build Time
 *
 * Description: information about build time in format HH:MM:SS
 * Format     : String
 * Example    : "15:23:16"
 */
const uint8_t ver_build_time[] = INFO_BUILD_TIME;

/**
 * Build Date
 *
 * Description: information about build date in format YYYYMMDD
 * Format     : String
 * Example    : "20121126"
 */
const uint8_t ver_build_date[] = INFO_BUILD_DATE;

/**
 * RCM Build ID
 *
 * Description: ID of the build from RCM system
 * Format     : String
 * Example    : "127"
 */
const uint8_t ver_build_id[] = INFO_BUILD_ID;

/**
 * RCM Version Name
 *
 * Description: Version Name from RCM system
 * Format     : String
 * Example    : "VIP_20160101"
 */
const uint8_t ver_variant_name[] = INFO_VARIANT_NAME;

/**
 * Board Name
 *
 * Description: Board Name
 * Format     : String
 * Example    : dms_tex
 */
const uint8_t ver_board_name[] = INFO_BOARD_NAME;

/**
 * Board Revision
 *
 * Description: Board Revision
 * Format     : Integer
 * Example    : 0
 */
const uint16_t ver_board_revision = INFO_BOARD_REV;

const uint8_t separator[] = "==================================================";

/**
 *  Returns the pointer to Project Name.
 */
const uint8_t* Ver_Get_Project_Name(void)
{
   return (ver_project_name);
}

/**
 *  Returns the pointer to User Name.
 */
const uint8_t* Ver_Get_User_Name(void)
{
   return (ver_user_name);
}

/**
 *  Returns the pointer to Build time.
 */
const uint8_t* Ver_Get_Build_Time(void)
{
   return (ver_build_time);
}

/**
 *  Returns the pointer to Build date.
 */
const uint8_t* Ver_Get_Build_Date(void)
{
   return (ver_build_date);
}

/**
 *  Returns the RCM Build ID.
 */
const uint8_t* Ver_Get_Version_Name(void)
{
   return (ver_build_id);
}

/**
 *  Returns Variant Name.
 */
const uint8_t* Ver_Get_Variant_Name(void)
{
   return (ver_variant_name);
}

/**
 *  Returns Board Name.
 */
const uint8_t* Ver_Get_Board_Name(void)
{
   return (ver_board_name);
}

/**
 *  Returns Board Revision.
 */
uint16_t Ver_Get_Board_Revision(void)
{
   return (ver_board_revision);
}

const uint8_t* Ver_Get_Separator(void)
{
   return separator;
}

