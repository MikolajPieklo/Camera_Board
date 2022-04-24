/**
* @file DMA_hal.h
* @brief Header file of the dma hal driver.
*
* @author Mikolaj Pieklo
* @date 24.04.2022
*/

#ifndef INC_DMA_HAL_H_
#define INC_DMA_HAL_H_

/**
 * @brief Initialize DMA.
 * @return void
 */
void DMA_Init(void);

/**
 * @brief Enable stream for DMA.
 * @return void
 */
void DMA_EnableStream(void);

/**
 * @brief Disable stream for DMA.
 * @return void
 */
void DMA_DisableStream(void);

#endif /* INC_DMA_HAL_H_ */
