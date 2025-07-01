# character-art-image-maker
An app to generate a character art styled image for a given input image

## Usage

Open the terminal, and run one of the two commands below:

```
char-art-maker.exe <IMG_FILE_NAME>
```

```
char-art-maker.exe <IMG_FILE_NAME> <ROWS> <COLS>
```

The arguments for the number of rows and columns (i.e. <ROWS> and <COLS>) inform the dimensions of the character-art image to be generated.
If not provided (as in the first command shown above), then both are taken to be 50 by default.

## Info

The char art makes use of the typical console character "ramp", which is a series of 10 characters, used to represent increasing levels of brightness:
```
 .:-=+*#%@
```

To calculate brightness (as an int value between 0 and 255) from the RGB parameters, a formula is used (suggested by ChatGPT):
```
Y = 0.2126 R + 0.7152 G + 0.0722 B
```
This follows the ITU BT.709 standard.
[Reference: https://en.wikipedia.org/wiki/Relative_luminance]

Alternatively, I could have also used
```
Y = 0.299 R + 0.587 G + 0.114 B
```
which follows the ITU BT.601 standard.
[Reference: https://stackoverflow.com/questions/596216/formula-to-determine-perceived-brightness-of-rgb-color]

## Example

![monalisa-example](https://github.com/user-attachments/assets/e4ed72e6-bfac-470e-ae4f-2aa071418857)

## Resources

This program makes use of the stb_image.h header only library, as available at: https://github.com/nothings/stb
