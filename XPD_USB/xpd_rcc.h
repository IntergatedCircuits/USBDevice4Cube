#ifndef __XPD_RCC_H_
#define __XPD_RCC_H_

#include <xpd_common.h>

#define RCC_POS_USB             1
#define RCC_POS_OTG_FS          2
#define RCC_POS_OTG_HS          3

#if defined(USB)
#define RCC_vClockEnable(A)     __HAL_RCC_USB_CLK_ENABLE()
#define RCC_vClockDisable(A)    __HAL_RCC_USB_CLK_DISABLE()
#elif defined(USB_OTG_HS)
#define RCC_vClockEnable(A)     (((A) == RCC_POS_OTG_FS) ?  \
        __HAL_RCC_USB_OTG_FS_CLK_ENABLE() :                 \
        __HAL_RCC_USB_OTG_HS_CLK_ENABLE())
#define RCC_vClockEnable(A)     (((A) == RCC_POS_OTG_FS) ?  \
        __HAL_RCC_USB_OTG_FS_CLK_DISABLE() :                \
        __HAL_RCC_USB_OTG_HS_CLK_DISABLE())
#elif defined(USB_OTG_FS)
#define RCC_vClockEnable(A)     __HAL_RCC_USB_OTG_FS_CLK_ENABLE()
#define RCC_vClockDisable(A)    __HAL_RCC_USB_OTG_FS_CLK_DISABLE()
#endif
#define RCC_ulClockFreq_Hz(A)   HAL_RCC_GetHCLKFreq()

#endif /* __XPD_RCC_H_ */
