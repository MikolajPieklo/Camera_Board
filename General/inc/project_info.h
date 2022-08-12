#ifndef PROJECT_INFO_H
#define PROJECT_INFO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 *  Returns the pointer to Project Name.
 *  @return  pointer to project_name[]
 */
const uint8_t* Get_Project_Name(void);

/**
 *  Returns the pointer to User Name.
 *  @return  pointer to user_name[]
 */
const uint8_t* Get_User_Name(void);

/**
 *  Returns the pointer to Build time.
 *  @return  pointer to build_time[]
 */
const uint8_t* Get_Build_Time(void);

/**
 *  Returns the pointer to Build date.
 *  @return  pointer to build_date[]
 */
const uint8_t* Get_Build_Date(void);

/**
 *  Returns the pointer to RCM Version Name.
 *  @return  pointer to version_name[]
 */
const uint8_t* Get_Version_Name(void);

/**
 *  Returns Variant Name.
 *  @return  pointer to variant_name[]
 */
const uint8_t* Get_Variant_Name(void);

/**
 *  Returns Board Name.
 *  @return  pointer to board_name[]
 */
const uint8_t* Get_Board_Name(void);

/**
 *  Returns Board Revision.
 *  @return  Board revision
 */
uint16_t Get_Board_Revision(void);

const uint8_t* Get_Separator(void);

#endif /* PROJECT_INFO_H */
