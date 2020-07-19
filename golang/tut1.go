package main

import "fmt"

func main() {
    var thename string = "Bob"
    var city string
    // var age uint8
    // var a uint16
    // var b uint32
    // var c uint64
    // var d int8
    // var e int16
    // var ee int32
    // var eee rune
    // var f int64
    // var g int
    // var h byte
    // var i uintptr
    // var j uint

    // var k float32
    // var l float64

    // var m complex64
    // var n complex128

    var o bool = false




    city = "Roeselare"

    fmt.Println("Hello world !")
    fmt.Println(thename)
    fmt.Println(city)
    fmt.Println(o)

    var x = 12345 // implicit type
    var y = 3.141592
    z := 42

    fmt.Println("X:", x)
    fmt.Printf("%T\n", x)
    fmt.Printf("%T\n", y)
    fmt.Printf("%T\n", z)
    fmt.Printf("%T  %t %% \n", o, o)

    var num uint64
    num = num - 1
    fmt.Printf("Num: %v \n", num)

    var xxx string = fmt.Sprintf("Num = %v", num)
    fmt.Println(xxx)

    var vvv int = 1234
    fmt.Printf("%b %o %d %x %X %09d \n", vvv, vvv, vvv, vvv, vvv, vvv)
    
    var fff float32 = 3.141592654
    fmt.Printf("%e  %f  %F  %g %.2f (%12f) \n", fff, fff, fff, fff, fff, fff)

    var sss string = "Hello all"
    fmt.Printf("%s  %q  \n", sss, sss)

    fmt.Printf("(%20s) (%-20s)  \n", sss, sss)
}
