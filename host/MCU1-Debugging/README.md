# MCU1-Debugging

Host-side implementation of bubble sort and insertion sort, used to practice debugging skills.

## What it does

1. Fills an integer array with random numbers using `rand()`.
2. Displays the unsorted array.
3. Sorts the array using **bubble sort**.
4. Sorts a second array using **insertion sort**.
5. Displays both sorted results.

Running this on the host (PC) allows setting breakpoints, inspecting memory, and stepping through the sorting logic in the STM32CubeIDE debugger — the same code is later deployed to the STM32 target in `MCU1-SortingsDebug`.

## Concepts

- Bubble sort algorithm
- Insertion sort algorithm
- Swap function using pointers
- `rand()` for array initialization
- Debugging workflow: breakpoints, watch expressions, memory view

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
