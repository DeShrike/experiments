package main

import (
	"strconv"
	"syscall/js"
)

func add2(i []js.Value) {

	str1 := i[0].String()
	str2 := i[1].String()
	str3 := i[2].String()

	value1 := js.Global().Get("document").Call("getElementById", str1).Get("value").String()
	value2 := js.Global().Get("document").Call("getElementById", str2).Get("value").String()

	int1, _ := strconv.Atoi(value1)
	int2, _ := strconv.Atoi(value2)

	var result = js.ValueOf(int1 + int2)
	js.Global().Set("output", result)

	js.Global().Get("document").Call("getElementById", str3).Set("value", result)

    println(result.String())
}

func add(i []js.Value) {


	var arg1 = i[0].Int()
	var arg2 = i[1].Int()

	var result = js.ValueOf(arg1 + arg2)
	js.Global().Set("output", result)

    println(result.String())

    // js.Global().Set("output", js.ValueOf(i[0].Int()+i[1].Int()))
    // println(js.ValueOf(i[0].Int() + i[1].Int()).String())
}

func subtract(i []js.Value) {
	var arg1 = i[0].Int()
	var arg2 = i[1].Int()

	var result = js.ValueOf(arg1 - arg2)
	js.Global().Set("output", result)

    println(result.String())

    // js.Global().Set("output", js.ValueOf(i[0].Int()-i[1].Int()))
    // println(js.ValueOf(i[0].Int() - i[1].Int()).String())
}

func registerCallbacks() {
    js.Global().Set("add", js.NewCallback(add))
    js.Global().Set("subtract", js.NewCallback(subtract))
    js.Global().Set("add2", js.NewCallback(add2))
}

func main() {
    c := make(chan struct{}, 0)
    println("WASM Go Initialized")

    // register functions
    registerCallbacks()
    <-c
}
