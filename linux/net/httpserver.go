package main

import (
    "fmt"
    "net/http"
    "time"

       )

func hello(w http.ResponseWriter, req *http.Request) {
    ctx := req.Context()
    fmt.Println("Server: hello handle started")
    defer fmt.Println("Server: hello handler ended")

    select {
    case <-time.After(10 * time.Second):
        fmt.Fprintf(w, "Hello\n")
    case <-ctx.Done():
        err := ctx.Err()
        fmt.Println("Server-Error:", err)
        internalError := http.StatusInternalServerError
        http.Error(w, err.Error(), internalError)
    
    }

}

func main() {
    http.HandleFunc("/hello", hello)
    http.ListenAndServe(":8090", nil)

}
