package main

import (
	"encoding/json"
	"fmt"
)

type human struct {
	name string
	age int
}

func (h *human) setName(n string) {
	h.name = n
}

func (h *human) setAge(a int) {
	h.age = a
}

type student = human

func info(h human) {
	fmt.Printf( "Hi my name is %s and I'm %d", h.name, h.age )
}

func main() {

}
