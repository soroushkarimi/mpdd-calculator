# MPDD Calculator

MPDD Calculator is a command line calculator program for my Microprocessor and Digital Design class.
When using unary operators the second operand will be ignored.
For binary operators double will be cast to int.

## How to Compile

```bash
gcc index.c argtable.c
```

## Usage

```bash
./a.out [-v] [--help] [--version] [--catalog] [-o myfile] [--operator=<char[]>] [--operand1=<double>] [--operand2=<double>]
```

## Example

### Input Command
```bash
./a.out --operand1=24 --operator="sqrt" --operand2=5.0  -o results.txt -v
```

### Output
```bash
operator:        sqrt
operand 1:       24.000000
operand 2:       5.000000 (IGNORED)
result:          4.898979
result saved to: results.txt
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)