#ifndef GENERAL_INC_PRJ_VERSION_H
#define GENERAL_INC_PRJ_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 *  Returns the pointer to Project Name.
 *
 *  @return  pointer to ver_project_name[]
 *
 */
const uint8_t* Ver_Get_Project_Name(void);

/**
 *  Returns the pointer to User Name.
 *
 *  @return  pointer to ver_user_name[]
 *
 */
const uint8_t* Ver_Get_User_Name(void);

/**
 *  Returns the pointer to Build time.
 *
 *  @return  pointer to ver_build_time[]
 *
 */
const uint8_t* Ver_Get_Build_Time(void);

/**
 *  Returns the pointer to Build date.
 *
 *  @return  pointer to ver_build_date[]
 *
 */
const uint8_t* Ver_Get_Build_Date(void);

/**
 *  Returns the pointer to RCM Version Name.
 *
 *  @return  pointer to ver_version_name[]
 *
 */
const uint8_t* Ver_Get_Version_Name(void);

/**
 *  Returns Variant Name.
 *
 *   @return  pointer to ver_variant_name[]
 */
const uint8_t* Ver_Get_Variant_Name(void);

/**
 *  Returns Board Name.
 *
 *  @return  pointer to ver_board_name[]
 */
const uint8_t* Ver_Get_Board_Name(void);

/**
 *  Returns Board Revision.
 *
 *   @return  Board revision
 */
uint16_t Ver_Get_Board_Revision(void);

const uint8_t* Ver_Get_Separator(void);

#endif                          /* PRJ_VERSION_H */
