package main

import (
    "bufio"
    "fmt"
    "net/http"

       )

func main() {
    rsp, err := http.Get("http://gobyexample.com")
        if err != nil {
        panic(err)
    
        }
    defer rsp.Body.Close()

    fmt.Println("status:", rsp.Status)

    scanner := bufio.NewScanner(rsp.Body)
    for i := 0; scanner.Scan() && i < 10; i++ {
        fmt.Println(scanner.Text())
    
    }
    if err := scanner.Err(); err != nil {
        panic(err)
    
    }

}

