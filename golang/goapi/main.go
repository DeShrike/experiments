package main

import (
   "net/http"
   "github.com/gin-gonic/gin"
   "errors"
)

type book struct {
   ID       string `json:"id"`
   Title    string `json:"title"`
   Author   string `json:"author"`
   Quantity int    `json:"quantity"`
}

var books = []book {
   { ID: "1", Title: "Ubik", Author: "Phikip K. Dick", Quantity: 2 },
   { ID: "2", Title: "Foundation", Author: "Isaac Asimov", Quantity: 4 },
}

func getBooks(c *gin.Context) {
   c.IndentedJSON(http.StatusOK, books)
}

func createBook(c *gin.Context) {
   var newBook book

   if err := c.BindJSON(&newBook); err != nil {
      return
   }

   books = append(books, newBook)
   c.IndentedJSON(http.StatusCreated, newBook)
}

func getBookById(id string) (*book, error) {
   for i, b := range books {
      if b.ID == id {
         return &books[i], nil
      }
   }

   return nil, errors.New("Book not found")
}

func bookById(c *gin.Context) {
   id := c.Param("id")
   book, err := getBookById(id)

   if err != nil {
      c.IndentedJSON(http.StatusNotFound, gin.H{"message": "Book not found"})
      return
   }

   c.IndentedJSON(http.StatusOK, book)
}

func checkoutBook(c *gin.Context) {
   id, ok := c.GetQuery("id")

   if ok == false {
      c.IndentedJSON(http.StatusBadRequest, gin.H{"message": "Missing id query parameter"})
      return
   }

   book, err := getBookById(id)

   if err != nil {
      c.IndentedJSON(http.StatusNotFound, gin.H{"message": "Book not found"})
      return
   }

   if book.Quantity <= 0 {
      c.IndentedJSON(http.StatusBadRequest, gin.H{"message": "Book not available"})
      return
   }

   book.Quantity -= 1
   c.IndentedJSON(http.StatusOK, book)
}

func returnBook(c *gin.Context) {
   id, ok := c.GetQuery("id")

   if ok == false {
      c.IndentedJSON(http.StatusBadRequest, gin.H{"message": "Missing id query parameter"})
      return
   }

   book, err := getBookById(id)

   if err != nil {
      c.IndentedJSON(http.StatusNotFound, gin.H{"message": "Book not found"})
      return
   }

   book.Quantity += 1
   c.IndentedJSON(http.StatusOK, book)
}

func main() {
   router := gin.Default()

   router.GET("/books", getBooks)
   router.POST("/books", createBook)
   router.GET("/books/:id", bookById)
   router.PATCH("/checkout", checkoutBook)
   router.PATCH("/return", returnBook)

   router.Run("localhost:8080")
}
