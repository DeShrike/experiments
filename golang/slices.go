package main

import (
	"encoding/json"
	"fmt"
)

type people []struct {
	Name string `json:"name"`
	Age float64 `json:"aga,omitempty"`
	Email string `json:"-"`
	Money float32 `json:"money,string"`
}

type response struct {
	Items people `json:"items"`
}

func main() {

	// slice zero value = nil

	p := people {
		{ Name: "John", Age: 10.9, Email: "john@home.com", Money: 3.12 },
		{ Name: "Steve", Age: 11.8, Email: "Steve@home.com", Money: 666 },
		{ Name: "Bob", Age: 12.7, Email: "bob@home.com", Money: 2.12 },
	}

	bs1, _ := json.Marshal(response{ Items: p })
	bs2, _ := json.Marshal(response{ })	// Items = nill
	bs3, _ := json.Marshal(response{ Items: people(nil) })	// Items = nil
	bs4, _ := json.Marshal(response{ Items: people{} }) // Items = empty

	fmt.Printf( "%s\n%s\n%s\n%s\n", string(bs1), string(bs2), string(bs3), string(bs4) )
}
