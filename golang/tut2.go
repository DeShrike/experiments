package main

import (
    "fmt"
    "bufio"
    "os"
    "strconv"
)

func main() {

    fmt.Printf("Type the year you were born: ")
    scanner := bufio.NewScanner(os.Stdin)
    scanner.Scan()
    input := scanner.Text()
    year, err := strconv.ParseInt(input, 10, 64)

    fmt.Printf("You typed: %q \n", input)
    fmt.Printf("Year: %d \n", year)
    fmt.Printf("Error ? : %T", err)
}
