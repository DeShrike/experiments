package main

import (
    "fmt"
)

// Slices

func main() {

    fmt.Println("Pointers & References")

    var str string = "TheName"
    addr := &str
    fmt.Printf("Type of str is %T, value = %s \n", str, str)
    fmt.Printf("Type of addr is %T, value = %X \n", addr, addr)

    fmt.Printf("Value=%s \n", str)
    // addr++
    // *addr[2] = "X"
    fmt.Printf("Value=%s \n", str)
}
