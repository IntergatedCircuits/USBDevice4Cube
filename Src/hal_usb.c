/**
  ******************************************************************************
  * @file    hal_usb.c
  * @author  Benedek Kupper
  * @version 0.1
  * @date    2018-11-03
  * @brief   HAL adapter for USBDevice
  *
  * Copyright (c) 2018 Benedek Kupper
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */
#include "stm32l4xx_hal.h"

#include <xpd_usb.h>
#include <usb_device.h>

void HAL_USB_OTG_FS_MspInit(void* handle)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Enable VDDUSB */
    if (__HAL_RCC_PWR_IS_CLK_DISABLED())
    {
        __HAL_RCC_PWR_CLK_ENABLE();
        HAL_PWREx_EnableVddUSB();
        __HAL_RCC_PWR_CLK_DISABLE();
    }
    else
    {
        HAL_PWREx_EnableVddUSB();
    }

    HAL_NVIC_SetPriority(OTG_FS_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
}

void HAL_USB_OTG_FS_MspDeInit(void* handle)
{
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11 | GPIO_PIN_12);

    /* Disable VDDUSB */
    if (__HAL_RCC_PWR_IS_CLK_DISABLED())
    {
        __HAL_RCC_PWR_CLK_ENABLE();
        HAL_PWREx_DisableVddUSB();
        __HAL_RCC_PWR_CLK_DISABLE();
    }
    else
    {
        HAL_PWREx_DisableVddUSB();
    }

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(OTG_FS_IRQn);
}

void HAL_USBD_Setup(void)
{
    UsbDevice->Callbacks.DepInit = HAL_USB_OTG_FS_MspInit;
    UsbDevice->Callbacks.DepDeinit = HAL_USB_OTG_FS_MspDeInit;
}

void OTG_FS_IRQHandler(void);

void OTG_FS_IRQHandler(void)
{
    USB_vIRQHandler(UsbDevice);
}
