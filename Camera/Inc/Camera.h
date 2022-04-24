/**
* @file Camera.h
* @brief Header file of the camera.
*
* @author Mikolaj Pieklo
* @date 24.04.2022
*/

#ifndef CAMERA_INC_CAMERA_H_
#define CAMERA_INC_CAMERA_H_

/**
 * @brief Initialize GPIO of the camera.
 * @return void
 */
void Camera_Init(void);

/**
 * @brief Reset of the camera.
 * @return void
 */
void Camera_Reset(void);

/**
 * @brief Start of the camera.
 * @return void
 */
void Camera_Start(void);

/**
 * @brief Stop of the camera.
 * @return void
 */
void Camera_Stop(void);

#endif /* CAMERA_INC_CAMERA_H_ */

