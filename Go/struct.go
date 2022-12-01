package main

import (
	"fmt"
	"time"
)

type Person struct {
	name     string
	email    string
	birthday time.Time
}

func main() {
	andrew := Person{name: "Andrew", email: "andrew@test.com", birthday: time.Now()}
	str := fmt.Sprintf("name %s\nemail: %s\birthday: %d", andrew.name, andrew.email, andrew.birthday)
	fmt.Println(str)
}
