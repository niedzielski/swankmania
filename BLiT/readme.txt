//------------------------------------------------------------------------
//  Readme.txt
//------------------------------------------------------------------------
This project is configure to get you up and running quickly using 
CodeWarrior with the Freescale M52233DEMO board.

Sample code for the following language:
- C


//------------------------------------------------------------------------
// Memory Maps
//------------------------------------------------------------------------
The Hardware has the following memory map:

# MCF52233 Derivative Memory map definitions from linker command files:
# __IPSBAR, __RAMBAR, __RAMBAR_SIZE, __FLASHBAR, __FLASHBAR_SIZE linker
# symbols must be defined in the linker command file.

# Memory Mapped Registers (IPSBAR= 0x40000000)
   ___IPSBAR         = 0x40000000;

# 32 Kbytes Internal SRAM
   ___RAMBAR         = 0x20000000;
   ___RAMBAR_SIZE    = 0x00008000;

# 256 KByte Internal Flash Memory
   ___FLASHBAR       = 0x00000000;
   ___FLASHBAR_SIZE  = 0x00040000;



//------------------------------------------------------------------------
// Project Structure
//------------------------------------------------------------------------
The project generated contains various files/groups:
- readme.txt: information for this project
- Sources: application source codes
- Support Files: all application startup code, user customizable startup 
  code, derivative and board header files, runtime and libs 
- Linker Command Files: linker command files for the different build 
  targets
- Debugger Files: the initialization and memory configuration files for 
  the hardware debugging. These files are local copies, modifying them will
  not affect other projects.

//------------------------------------------------------------------------
// Build Targets
//------------------------------------------------------------------------
- CONSOLE_RAM:
This project target is setup to load and debug code from RAM.
It should be used during your application development. 
The application outputs to the CodeWarrior's console window. 

This build target is also setup to demonstrate exception capture:
For some of the Protocol plugin allows the use of the Exceptions target
settings panel to capture various exceptions. After the code is 
downloaded, the plugin attempts to overwrite the vector table entries and
install its own handler at locations VBR+0x408-0x40B to capture those 
selected exceptions.

- RAM:
This project target is setup to load and debug code from RAM.
It should be used during your application development. 
This is the very basic project that outputs to the UART. 
You needs to connect a Terminal Program to see the output.

- INTERNAL_FLASH:
This project target is setup to load and debug code in Internal FLASH. 
This is the very basic project that outputs to the UART. User needs 
to connect the terminal to see the output.



===================================================================
WARNING regarding code located in RAM
===================================================================
Many possible ColdFire target processors have an external bus, so 
you can use large external RAM devices for debugging applications 
during development. But some processors do not have an external 
bus, so you must accommodate applications in on-chip memory. 
Although this on-chip RAM accommodates this CodeWarrior project, 
it probably is too small for full development of your application. 
Accordingly, for a processor without external bus, you should locate 
your applications in flash memory. 

//------------------------------------------------------------------------
//  Flashing the code
//------------------------------------------------------------------------
1. Select the appropriate project target and build it
2. Make sure the correct remote connection is selected in the Remote 
   Connection debugger panel
3. In the CodeWarrior IDE menu, select Project > Set Default Project 
   and select your project
4. In the CodeWarrior IDE menu, select Project > Set Default Target 
   and select the project target that has the code you want to flash
5. In the CodeWarrior IDE menu, select Tools > Flash Programmer
6. Go to the flash programmer Target Configuration panel, click Load 
   Settings 
7. Browse to the bin\Plugins\Support\Flash_Programmer\ColdFire folder and
   select the flash settings xml file for your EVB 
8. Check that Use Custom Settings checkbox is not selected
9. Go to the Erase/Blank Check panel, select the All Sectors option and 
   click Erase
10. Go to Program/Verify panel, click Program
11. Your code should now be flashed

//------------------------------------------------------------------------
// Terminal Settings
//------------------------------------------------------------------------
In case the UART is supported, the terminal is using the settings defined 
in M52233DEMO_board.h.

Please check this file in the project.

//------------------------------------------------------------------------
//  Getting Started
//------------------------------------------------------------------------
To build/debug your project, use the CodeWarrior IDE menu Project > Debug 
or press F5. This will launch the debugger. Press again F5 in the 
debugger (or the CodeWarrior IDE menu Project > Run) to start the 
application. The CodeWarrior IDE menu Project > Break stops the 
application.

//------------------------------------------------------------------------
//  Adding your own code
//------------------------------------------------------------------------
Once everything is working as expected, you can begin adding your own code
to the project. Keep in mind that we provide this as an example of how to
get up and running quickly with CodeWarrior. There are certainly other
ways to handle interrupts and set up your linker command file. Feel free
to modify any of the source files provided.

//------------------------------------------------------------------------
//  Additional documentation
//------------------------------------------------------------------------
Read the online documentation provided. In CodeWarrior IDE menu, select
Help > CodeWarrior Help.

//------------------------------------------------------------------------
//  Contacting Freescale
//------------------------------------------------------------------------
For bug reports, technical questions, and suggestions, please use the
forms installed in the Release_Notes folder.
