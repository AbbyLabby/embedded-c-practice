# struct_pointers (STM32)

Practices accessing and modifying struct members via a struct pointer on the STM32 target.

## What it does

Creates a `DataSet_t` struct, obtains a pointer to it (`DataSet_t *pData`), then accesses a member and passes a pointer to it (`uint8_t*`) into an `UpdateValue()` function to modify the value.

Prints the member value before and after modification to verify the pointer-based update.

## Concepts

- Struct pointer syntax (`pData->member`)
- Passing struct member addresses to functions (`(uint8_t*)pData->data1`)
- Pointer-to-member modification
- Practical embedded pattern: modifying peripheral struct register fields via pointer

## Hardware

- **Board:** STM32F4 Discovery (STM32F407VGTx)
- **Debug:** ST-Link / SWD with semihosting
