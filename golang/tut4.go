package main

import (
    "fmt"
)

func main() {

    var num1 int = 42
    var num2 int = 666
    var num3 float32 = 3.1415
    var s1 string = "Bob"
    var s2 string = "Jane"
    ch := 'A'
 
    var a = num1 == num2
    var b = num2 > num1
    var c = num1 > num2
    var d = num3 > float32(num2)
    var e = s1 < s2

    fmt.Printf("A: %t \n", a)
    fmt.Printf("B: %t \n", b)
    fmt.Printf("C: %t \n", c)
    fmt.Printf("D: %t \n", d)
    fmt.Printf("E: %t \n", e)
    fmt.Printf("CH is of type %T Value: %d \n", ch, ch)
}
