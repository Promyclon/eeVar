# eeVar
eeVar lets to define, use, read and write variables stored in AVR's EEPROM memory and configure the AVR device using data stored in EEPROM
## Variables
### Simple EEPROM variable
```C
EEPROM_VAR(var_type, var_name)
```
Defines EEPROM stored variable of type `var_type`, named `var_name` giving it a a value to be strored in EEPROM. This variable should be initialized using `EEPROM_READ()` before use.
#### Example:
```C
EEPROM_VAR(uint8_t, ledBrightness) = 127;

main()
{
  EEPROM_READ(ledBrightness);
  setPWM(ledBrightness);
}
```
### Autoimatic EEPROM variable
```C
EEPROM_AUTO_VAR(var_type, var_name)
```
Defines EEPROM stored variable of type `var_type`, named `var_name` with a value strored in EEPROM. This value will be automaticaly read into `var_name' in RAM in `.init8` section just before the main() function starts execution. Then, the definition alone is enough to get pre-initialized variable ready to use as soon as the program starts.
#### Example:
```C
EEPROM_AUTO_VAR(uint8_t, ledBrightness) = 127;

main()
{
  setPWM(ledBrightness);
}
```
### Read value
```C
EEPROM_READ(x)
```
Reads value of variable from EEPROM to RAM memory. This must be a variable defined with `EEPROM_VAR` or 'EEPROM_AUTO_VAR` macros.
#### Example:
```C
EEPROM_VAR(uint8_t, ledBrightness) = 127;

main()
{
  EEPROM_READ(ledBrightness);
  setPWM(ledBrightness);
}
```
### Store value
```C
EEPROM_WRITE(x)
```
Reads value of variable from EEPROM to RAM memory. This must be a variable defined with `EEPROM_VAR` or `EEPROM_AUTO_VAR` macros.
#### Example:
```C
EEPROM_AUTO_VAR(uint8_t, ledBrightness) = 127;

main()
{
  int newLedBrightness = checkButtons(ledBrightness);
  setPWM(ledBrightness);
  if (newLedBrightness != ledBrightness)
  {
    ledBrightness= newLedBrightness;
    EEPORM_WRITE(ledBrightness); // EEPORM_WRITE(newLedBrightness) wouldn't work
  }
}
```
