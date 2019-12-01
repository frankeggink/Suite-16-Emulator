# Suite-16-Emulator

This is the Suite16 Emulator for windows (Microsoft Visual Studio solution)


# LATEST VERSION - with HEXLOADER !!!!! #
see: Suite16-emulator_v3 <br/>
The hexloader is limited to loading a program in memory up to $7FFF hex <br/>
because the generated .hex file from TASM doubles the addresses (because we use word addressing) <br/>
$8000 * 2 = $10000 <br/>
hexloader.asm does not take this into account yet <br/>

TODO: <br/>
* create a new helper program that converts the .lst file to a correct .hex file that we can use (divide address by 2) <br/>
* change the hexloader (divide by 2 is not needed anymore!!) <br/>



## Suite-16-Assembler
See: https://github.com/frankeggink/Suite-16-Assember

## Founding father of Suite-16
Suite-16 is being developed by Ken Boak.  <br/>
See his repository at: https://github.com/monsonite/Suite-16  <br/>
And for more info see: https://hackaday.io/project/168025-suite-16  <br/>
